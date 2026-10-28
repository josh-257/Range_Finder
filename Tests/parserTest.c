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
    Parser_RXByte(random);
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START, state);
    Parser_RXByte(RX_DATA_HEAD_BYTE);
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_LEN, state);
}

TEST(parser, ParserResetIfInvalidLen)
{
    Parser_RXByte(RX_DATA_HEAD_BYTE);
    Parser_RXByte('Z');
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START, state);
}

TEST(parser, LookForIdAfterLenByte)
{
    Parser_RXByte(RX_DATA_HEAD_BYTE);
    Parser_RXByte(4);
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_ID, state);
}

TEST(parser, ParserResetIfInvalidId)
{

}

TEST(parser, LookForDataAfterValidIdByte)
{

}