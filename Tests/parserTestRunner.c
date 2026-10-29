#include "unity_fixture.h"

TEST_GROUP_RUNNER(parser)
{
    RUN_TEST_CASE(parser, ParserResetIfInvalidHeadByte);
    RUN_TEST_CASE(parser, LookForDataAfterValidHeadByte);
    RUN_TEST_CASE(parser, LookForCheckSumAfterData);
    RUN_TEST_CASE(parser, SplitMessageAfterSuccesfulTransmission);
    RUN_TEST_CASE(parser, GoodFrameDecodesAfterBadFrame);
    RUN_TEST_CASE(parser, TwoFramesBackToBackBothDecode);
    RUN_TEST_CASE(parser, BadChecksumLeavesMessageUnchanged);
    RUN_TEST_CASE(parser, ZeroChecksumIsRejectedWhenSumIsNotZero);
    RUN_TEST_CASE(parser, ChecksumAboveFFIsTruncatedTo8Bits);
    RUN_TEST_CASE(parser, HeaderByteInsidePayloadDoesNotDisturbFrame);
    RUN_TEST_CASE(parser, HighBytesAreDecodedLittleEndian);
}