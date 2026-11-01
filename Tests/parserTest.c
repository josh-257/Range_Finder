#include "unity_fixture.h"
#include "Core/Inc/parser.h"


#define DIMENSION_OF(a) (sizeof(a)/sizeof(a[0]))

TEST_GROUP(parser);

extern Parser_State_t Parserstate;
Msg_Data_t msgTest;

static Return_Status_t sendMessage(uint8_t *msg, uint8_t len)
{
    int i;
    for(i = 0; i < len-1; i++)
    {
        Parser_AddByte(&msgTest, msg[i]);
    }
    return Parser_AddByte(&msgTest, msg[i]);
}

// Unity requires these two functions, even if they are empty
TEST_SETUP(parser) 
{
    Parserstate = PARSER_LOOKING_FOR_START;
}

TEST_TEAR_DOWN(parser) 
{
    Parser_Reset();
}

TEST(parser, ParserResetIfInvalidHeadByte)
{
    Parser_AddByte(&msgTest, RX_DATA_HEAD_BYTE);
    Parser_AddByte(&msgTest, 'Z');
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START, Parserstate);

    Parser_AddByte(&msgTest, 'Z');
    Parser_AddByte(&msgTest, RX_DATA_HEAD_BYTE);
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_START, Parserstate);
}

TEST(parser, LookForDataAfterValidHeadByte)
{
    Parser_AddByte(&msgTest, RX_DATA_HEAD_BYTE);
    Parser_AddByte(&msgTest, RX_DATA_HEAD_BYTE);
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_DATA, Parserstate);
}

TEST(parser, LookForCheckSumAfterData)
{
    uint8_t msg[] = {0x59, 0x59, 0x04, 0x04, 0x02, 0x02, 0x05, 0x05};
    sendMessage(msg, DIMENSION_OF(msg));
    TEST_ASSERT_EQUAL(PARSER_LOOKING_FOR_CHECKSUM, Parserstate);
}

TEST(parser, SplitMessageAfterSuccesfulTransmission)
{
    uint8_t msg[] = {0x59, 0x59, 0x04, 0x04, 0x02, 0x02, 0x05, 0x05, 0xC8};
    sendMessage(msg, DIMENSION_OF(msg));
    TEST_ASSERT_EQUAL_HEX16(0x0404, msgTest.dist);
    TEST_ASSERT_EQUAL_HEX16(0x0202, msgTest.amps);
    TEST_ASSERT_EQUAL_HEX16(0x0505, msgTest.temp);
}

TEST(parser, GoodFrameDecodesAfterBadFrame)
{
    uint8_t bad[]  = {0x59,0x59,0x04,0x04,0x02,0x02,0x05,0x05,0x00};
    uint8_t good[] = {0x59,0x59,0x64,0x00,0x90,0x01,0xC8,0x08,0x77};
    sendMessage(bad, DIMENSION_OF(bad));
    sendMessage(good, DIMENSION_OF(good));
    TEST_ASSERT_EQUAL_HEX16(100, msgTest.dist);
}

TEST(parser, TwoFramesBackToBackBothDecode)
{
    uint8_t a[] = {0x59,0x59,0x64,0x00,0x90,0x01,0xC8,0x08,0x77}; 
    uint8_t b[] = {0x59,0x59,0x59,0x00,0x90,0x01,0xC8,0x08,0x6C};  
    sendMessage(a, DIMENSION_OF(a));
    TEST_ASSERT_EQUAL_HEX16(100, msgTest.dist);
    sendMessage(b, DIMENSION_OF(b));
    TEST_ASSERT_EQUAL_HEX16(89, msgTest.dist);
}

TEST(parser, BadChecksumLeavesMessageUnchanged)
{
    msgTest.dist = 0xAAAA; msgTest.amps = 0xBBBB; msgTest.temp = 0xCCCC;
    uint8_t msg[] = {0x59,0x59,0x64,0x00,0x90,0x01,0xC8,0x08,0x78}; // 0x77 is correct
    sendMessage(msg, DIMENSION_OF(msg));
    TEST_ASSERT_EQUAL_HEX16(0xAAAA, msgTest.dist);
    TEST_ASSERT_EQUAL_HEX16(0xBBBB, msgTest.amps);
    TEST_ASSERT_EQUAL_HEX16(0xCCCC, msgTest.temp);
}

TEST(parser, ZeroChecksumIsRejectedWhenSumIsNotZero)
{
    uint8_t msg[] = {0x59,0x59,0x04,0x04,0x02,0x02,0x05,0x05,0x00};
    msgTest.dist = 0xAAAA;
    sendMessage(msg, DIMENSION_OF(msg));
    TEST_ASSERT_EQUAL_HEX16(0xAAAA, msgTest.dist);
}

TEST(parser, ChecksumAboveFFIsTruncatedTo8Bits)
{
    uint8_t msg[] = {0x59,0x59,0x64,0x00,0x90,0x01,0xC8,0x08,0x77};
    sendMessage(msg, DIMENSION_OF(msg));
    TEST_ASSERT_EQUAL_HEX16(100, msgTest.dist);
    TEST_ASSERT_EQUAL_HEX16(400, msgTest.amps);
    TEST_ASSERT_EQUAL_HEX16(0x08C8, msgTest.temp);
}

TEST(parser, HeaderByteInsidePayloadDoesNotDisturbFrame)
{
    uint8_t msg[] = {0x59,0x59,0x59,0x00,0x90,0x01,0xC8,0x08,0x6C};
    sendMessage(msg, DIMENSION_OF(msg));
    TEST_ASSERT_EQUAL_HEX16(89, msgTest.dist);
}

TEST(parser, HighBytesAreDecodedLittleEndian)
{
    uint8_t msg[] = {0x59,0x59,0x23,0x01,0x90,0x01,0xC8,0x08,0x37};
    sendMessage(msg, DIMENSION_OF(msg));
    TEST_ASSERT_EQUAL_HEX16(0x0123, msgTest.dist);
}

TEST(parser, ReturnErrorIfCheckSumIncorrect)
{
    uint8_t msg[] = {0x59,0x59,0x64,0x00,0x90,0x01,0xC8,0x08,0x78}; // 0x77 is correct
    
    TEST_ASSERT_EQUAL(PARSER_CHECKSUM_ERROR, sendMessage(msg, DIMENSION_OF(msg)));
}
