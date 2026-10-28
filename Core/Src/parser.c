#include "Parser.h"
#include <stddef.h>
#include <stdint.h>

#ifndef TEST_PARSER
#define STATIC static
#else
#define STATIC
#endif

#define PARSER_BUFFER_LENGTH_MAX (13)

STATIC PARSER_STATE_T state = PARSER_LOOKING_FOR_START;

uint8_t *Parser_AddByte(uint8_t NewByte)
{
    static uint8_t *fail;
    if(NewByte == 0x5A)
    {
        state = PARSER_LOOKING_FOR_LEN;
        return NULL;
    } 
    return fail;
} 