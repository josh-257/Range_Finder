#include "Parser.h"
#include <stddef.h>
#include <stdint.h>
#include <ctype.h>

#ifndef TEST_PARSER
#define STATIC static
#else
#define STATIC
#endif

STATIC PARSER_STATE_T state = PARSER_LOOKING_FOR_START;

void Parser_RXByte(uint8_t NewByte)
{
    
    switch (state)
    {
    case PARSER_LOOKING_FOR_START:
        if(NewByte == RX_DATA_HEAD_BYTE)
        {
            state = PARSER_LOOKING_FOR_LEN;
            return;
        } 
        break;
    case PARSER_LOOKING_FOR_LEN:
        if(NewByte >= 4 && NewByte <= 12)
        {
            state = PARSER_LOOKING_FOR_ID;
            return;
        }
        else
        {
            state = PARSER_LOOKING_FOR_START;
            return;
        }
        break;
    
    default:
        break;
    }
    return;
} 