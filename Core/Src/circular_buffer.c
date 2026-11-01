#include "circular_buffer.h"
#include <string.h>

struct Circular_Buffer{
    volatile uint32_t head;
    volatile uint32_t tail;
    Item buffer[BUFF_SIZE];
};

static struct Circular_Buffer instance;

static uint32_t CircularBuffer_Count(circBuff c)
{
    return (c->tail + BUFF_SIZE - c->head) % BUFF_SIZE;
}

circBuff CircularBuffer_Init(void)
{
    circBuff c = &instance;
    c->head = 0;
    c->tail = 0;
    memset(c->buffer, 0, BUFF_SIZE * sizeof(Item));
    return c;
}

bool CircularBuffer_Put(circBuff c, Item data)
{
    if(CircularBuffer_IsFull(c))
    {
        return false;
    }
    c->buffer[c->tail] = data;
    c->tail = (c->tail + 1) % BUFF_SIZE;
    return true;
} 

bool CircularBuffer_Get(circBuff c, Item *data)
{
    if(CircularBuffer_IsEmpty(c))
    {
        return false;
    }
    *data = c->buffer[c->head];
    c->head = (c->head + 1) % BUFF_SIZE;
    return true;
}

bool CircularBuffer_IsEmpty(circBuff c)
{
    return c->head == c->tail;
}

bool CircularBuffer_IsFull(circBuff c)
{
    uint32_t tail_next = (c->tail + 1) % BUFF_SIZE;
    return tail_next == c->head;
}

bool CircularBuffer_IsHalfFull(circBuff c)
{
    return CircularBuffer_Count(c) >= BUFF_SIZE / 2;
}



//For testing
uint32_t getHead(circBuff c)
{
    return c->head;
}

uint32_t getTail(circBuff c)
{
    return c->tail;
}

Item *getBuff(circBuff c)
{
    return c->buffer;
}

