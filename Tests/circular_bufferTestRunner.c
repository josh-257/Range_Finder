#include "unity_fixture.h"

TEST_GROUP_RUNNER(circular_buffer)
{
    RUN_TEST_CASE(circular_buffer, AllSetToZero);
    RUN_TEST_CASE(circular_buffer, PutOneByte);
    RUN_TEST_CASE(circular_buffer, GetOneByte);
    RUN_TEST_CASE(circular_buffer, PutAndGetMultipleBytes);
    RUN_TEST_CASE(circular_buffer, IsEmpty);
    RUN_TEST_CASE(circular_buffer, IsFull);
    RUN_TEST_CASE(circular_buffer, PutReturnsFalseIfBufferFull);
    RUN_TEST_CASE(circular_buffer, GetReturnsFalseIfBufferEmpty);
    RUN_TEST_CASE(circular_buffer, HeadAndTailIndexesWrapToZero);
    RUN_TEST_CASE(circular_buffer, WrapAroundPreservesDataOrder);
    RUN_TEST_CASE(circular_buffer, ReturnTrueIfBufferHalfFull);
    RUN_TEST_CASE(circular_buffer, HalfFullBoundaryAtEveryOffset);
}