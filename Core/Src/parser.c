#include "Parser.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifndef TEST_PARSER
#define STATIC static
#else
#define STATIC
#endif

STATIC Parser_State_t Parserstate = PARSER_LOOKING_FOR_START;
STATIC uint8_t dataIndex;
STATIC uint8_t headByteCount;
STATIC uint8_t checkSum;

STATIC uint8_t parserBuffer[MAX_DATA_LEN];

static void Parser_SplitRXMessage(Msg_Data_t *msg);

Return_Status_t Parser_RXByte(Msg_Data_t *msg, uint8_t NewByte)
{
    switch (Parserstate)
    {
    case PARSER_LOOKING_FOR_START:
        if(NewByte == RX_DATA_HEAD_BYTE)
        {
            if(headByteCount >= 1)
            {
                headByteCount = 0;
                Parserstate = PARSER_LOOKING_FOR_DATA;
                checkSum = RX_DATA_HEAD_BYTE + RX_DATA_HEAD_BYTE;
            }
            else
            {
                headByteCount++;
            }
        }
        else
        {
            Parser_Reset();
        }   
        break;
    case PARSER_LOOKING_FOR_DATA:
        parserBuffer[dataIndex++] = NewByte;
        checkSum += NewByte;
        if(dataIndex >= MAX_DATA_LEN)
        {
            Parserstate = PARSER_LOOKING_FOR_CHECKSUM;
        }
        break;
    case PARSER_LOOKING_FOR_CHECKSUM:
        if(NewByte == checkSum)
        {
            Parser_SplitRXMessage(msg);
            Parser_Reset();
            return PARSER_DATA_FRAME_READY;
        }
        Parser_Reset();
        return PARSER_CHECKSUM_ERROR;
    }
    return PARSER_IN_PROGRESS;
} 

void Parser_Reset(void)
{
    dataIndex = 0;
    headByteCount = 0;
    checkSum = 0;
    Parserstate = PARSER_LOOKING_FOR_START;
}

static void Parser_SplitRXMessage(Msg_Data_t *msg)
{
    msg->dist = (parserBuffer[DIST_L_INDEX]) | (parserBuffer[DIST_H_INDEX] << 8);
    msg->amps = (parserBuffer[AMP_L_INDEX]) | (parserBuffer[AMP_H_INDEX] << 8);
    msg->temp = (parserBuffer[TEMP_L_INDEX]) | (parserBuffer[TEMP_H_INDEX] << 8);
}