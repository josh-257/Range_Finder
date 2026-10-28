/*Code that will run inside the main loop
seperated out for testing purposes*/

#include "circular_buffer.h"
#include <stdlib.h>


//ISR
void USART1_IRQHandler(void)
{
    CircularBuffer_Put()
}

uint8_t getRandNum(void)
{
    return rand() % 256;
}