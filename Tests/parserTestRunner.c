#include "unity_fixture.h"

TEST_GROUP_RUNNER(parser)
{
    RUN_TEST_CASE(parser, LookForLenByteAfterReceivingHeadByte);
    RUN_TEST_CASE(parser, LookForIdAfterLenByte);
    RUN_TEST_CASE(parser, ParserResetIfInvalidLen);
}