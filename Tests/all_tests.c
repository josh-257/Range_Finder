#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(circular_buffer);
    RUN_TEST_GROUP(parser);
}

int main(int argc, const char *argv[])
{
    return UnityMain(argc,  argv, RunAllTests);
}