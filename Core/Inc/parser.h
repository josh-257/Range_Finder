#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

typedef enum _PARSER_STATE_T{
    PARSER_LOOKING_FOR_START = 0,
    PARSER_LOOKING_FOR_LEN,
    PARSER_LOOKING_FOR_ID,
    PARSER_LOOKING_FOR_DATA,
    PARSER_LOOKING_FOR_CHECKSUM
}PARSER_STATE_T;

uint8_t* Parser_AddByte(uint8_t NewByte);

#endif