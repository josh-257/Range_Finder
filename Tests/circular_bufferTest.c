#include "unity_fixture.h"
#include "Core/Inc/circular_buffer.h"

TEST_GROUP(circular_buffer);

circBuff circBuffTest;

// Unity requires these two functions, even if they are empty
TEST_SETUP(circular_buffer) 
{
    circBuffTest = CircularBuffer_Init();
}

TEST_TEAR_DOWN(circular_buffer) 
{

}

TEST(circular_buffer, AllSetToZero)
{
    TEST_ASSERT_EQUAL(0, getHead(circBuffTest));
    TEST_ASSERT_EQUAL(0, getTail(circBuffTest));
    Item *buffer = getBuff(circBuffTest);
    for(int i = 0; i < BUFF_SIZE; i++)
    {
        TEST_ASSERT_EQUAL(0, buffer[i]);
    }
}

TEST(circular_buffer, PutOneByte)
{
    TEST_ASSERT_TRUE(CircularBuffer_Put(circBuffTest, 'A'));
    Item *buffer = getBuff(circBuffTest);
    TEST_ASSERT_EQUAL('A', buffer[getHead(circBuffTest)]);
}

TEST(circular_buffer, GetOneByte)
{
    Item data_read;
    TEST_ASSERT_TRUE(CircularBuffer_Put(circBuffTest, 'A'));
    TEST_ASSERT_TRUE(CircularBuffer_Get(circBuffTest, &data_read));
    TEST_ASSERT_EQUAL('A', data_read);
}

TEST(circular_buffer, PutAndGetMultipleBytes)
{
    Item data_read[12];
    Item msg[12] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
    for(int i = 0; i < 12; i++)
    {
        TEST_ASSERT_TRUE(CircularBuffer_Put(circBuffTest, msg[i]));
    }
    for(int i = 0; i < 12; i++)
    {
        TEST_ASSERT_TRUE(CircularBuffer_Get(circBuffTest, &data_read[i]));
    }
    TEST_ASSERT_EQUAL_UINT8_ARRAY(msg, data_read, 12);
}

TEST(circular_buffer, IsEmpty)
{
    TEST_ASSERT_TRUE(CircularBuffer_IsEmpty(circBuffTest));
    CircularBuffer_Put(circBuffTest, 1);
    TEST_ASSERT_FALSE(CircularBuffer_IsEmpty(circBuffTest));
}

TEST(circular_buffer, IsFull)
{
    TEST_ASSERT_FALSE(CircularBuffer_IsFull(circBuffTest));
    for(int i = 0; i < BUFF_SIZE-1; i++)
    {
        CircularBuffer_Put(circBuffTest, 1);
    }
    TEST_ASSERT_TRUE(CircularBuffer_IsFull(circBuffTest));
}

TEST(circular_buffer, PutReturnsFalseIfBufferFull)
{
    for(int i = 0; i < BUFF_SIZE-1; i++)
    {
        TEST_ASSERT_TRUE(CircularBuffer_Put(circBuffTest, 1));
    }
    TEST_ASSERT_FALSE(CircularBuffer_Put(circBuffTest, 1));
}

TEST(circular_buffer, GetReturnsFalseIfBufferEmpty)
{
    Item dummy;
    TEST_ASSERT_FALSE(CircularBuffer_Get(circBuffTest, &dummy));
}

TEST(circular_buffer, HeadAndTailIndexesWrapToZero)
{
    Item dummy;
    for(int i = 0; i < BUFF_SIZE; i++)
    {
        CircularBuffer_Put(circBuffTest, 1);
        CircularBuffer_Get(circBuffTest, &dummy);
    }
    TEST_ASSERT_EQUAL(0, getHead(circBuffTest));
    TEST_ASSERT_EQUAL(0, getTail(circBuffTest));
}

TEST(circular_buffer, WrapAroundPreservesDataOrder)
{
    Item out;
    
    for (int i = 0; i < BUFF_SIZE - 1; i++)
    {
        TEST_ASSERT_TRUE(CircularBuffer_Put(circBuffTest, i));
    }

    for (int i = 0; i < BUFF_SIZE / 2; i++)
    {
        TEST_ASSERT_TRUE(CircularBuffer_Get(circBuffTest, &out));
        TEST_ASSERT_EQUAL_UINT8(i, out);
    }
    for (int i = 0; i < BUFF_SIZE / 2; i++)
    {
        TEST_ASSERT_TRUE(CircularBuffer_Put(circBuffTest, 100 + i));
    }
    
    for (int i = BUFF_SIZE / 2; i < BUFF_SIZE - 1; i++)
    {
        TEST_ASSERT_TRUE(CircularBuffer_Get(circBuffTest, &out));
        TEST_ASSERT_EQUAL_UINT8(i, out);
    }
    for (int i = 0; i < BUFF_SIZE / 2; i++)
    {
        TEST_ASSERT_TRUE(CircularBuffer_Get(circBuffTest, &out));
        TEST_ASSERT_EQUAL_UINT8(100 + i, out);
    }
    TEST_ASSERT_TRUE(CircularBuffer_IsEmpty(circBuffTest));
}
