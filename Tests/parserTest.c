#include "unity_fixture.h"
#include "Core/Inc/parser.h"

TEST_GROUP(parser);

extern PARSER_STATE_T state;



// Unity requires these two functions, even if they are empty
TEST_SETUP(parser) 
{
    state = PARSER_LOOKING_FOR_START;
}

TEST_TEAR_DOWN(parser) 
{

}

TEST(parser, LookForLenByteAfterReceivingHeadByte)
{
    uint8_t random = 'm';
    TEST_ASSERT_NULL(Parser_AddByte(random));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START, state);
    TEST_ASSERT_NULL(Parser_AddByte(RX_DATA_HEAD_BYTE));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_LEN, state);
}

TEST(parser, ParserResetIfInvalidLen)
{
    Parser_AddByte(RX_DATA_HEAD_BYTE);
    Parser_AddByte('Z');
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START, state);
}

TEST(parser, LookForIdAfterLenByte)
{
    Parser_AddByte(RX_DATA_HEAD_BYTE);
    TEST_ASSERT_NULL(Parser_AddByte(4));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_ID, state);
}