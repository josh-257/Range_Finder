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

uint8_t *Parser_AddByte(uint8_t NewByte)
{
    
    switch (state)
    {
    case PARSER_LOOKING_FOR_START:
        if(NewByte == RX_DATA_HEAD_BYTE)
        {
            state = PARSER_LOOKING_FOR_LEN;
            return NULL;
        } 
        break;
    case PARSER_LOOKING_FOR_LEN:
        if(NewByte >= 4 && NewByte <= 12)
        {
            state = PARSER_LOOKING_FOR_ID;
            return NULL;
        }
        else
        {
            state = PARSER_LOOKING_FOR_START;
            return NULL;
        }
        break;
    
    default:
        break;
    }
    return NULL;
} 