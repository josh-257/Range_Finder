#include "circular_buffer.h"
#include <string.h>

struct Circular_Buffer{
    uint32_t head;
    uint32_t tail;
    Item buffer[BUFF_SIZE];
};

static struct Circular_Buffer instance;

circBuff CircularBuffer_Init(void)
{
    circBuff c = &instance;
    c->head = 0;
    c->tail = 0;
    memset(c->buffer, 0, BUFF_SIZE);
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

