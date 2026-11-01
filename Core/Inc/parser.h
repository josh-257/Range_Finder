#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

#define RX_DATA_HEAD_BYTE 0x59
#define MAX_DATA_LEN 6

typedef enum _Parser_State_t{
    PARSER_LOOKING_FOR_START = 0,
    PARSER_LOOKING_FOR_DATA,
    PARSER_LOOKING_FOR_CHECKSUM
}Parser_State_t;

typedef enum Return_Status_t{
    PARSER_DATA_FRAME_READY,
    PARSER_IN_PROGRESS, 
    PARSER_CHECKSUM_ERROR
}Return_Status_t;

enum DATA_TYPE_INDEX{
    DIST_L_INDEX, 
    DIST_H_INDEX, 
    AMP_L_INDEX, 
    AMP_H_INDEX, 
    TEMP_L_INDEX, 
    TEMP_H_INDEX
};

typedef struct{
    uint16_t dist;
    uint16_t amps;
    uint16_t temp;
}Msg_Data_t;

Return_Status_t Parser_AddByte(Msg_Data_t *msg, volatile uint8_t NewByte);
void Parser_Reset(void);

#endif
