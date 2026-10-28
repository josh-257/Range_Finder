#include "unity_fixture.h"
#include "Core/Inc/parser.h"

TEST_GROUP(parser);

extern PARSER_STATE_T state;



// Unity requires these two functions, even if they are empty
TEST_SETUP(parser) 
{
    
}

TEST_TEAR_DOWN(parser) 
{

}

TEST(parser, LookForLenByteAfterReceivingHeadByte)
{
    state = PARSER_LOOKING_FOR_START;

    TEST_ASSERT_NULL(Parser_AddByte(0x5A));

    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_LEN, state);

}