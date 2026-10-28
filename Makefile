#Compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -DTEST_CIRCULAR_BUFFER -DTEST_PARSER

# Paths (Relative to the project root folder)
INC_FLAGS = -ITests/Unity -ICore/Inc -ITests -I.

#Source files grouping
UNITY_FILES = Tests/Unity/unity.c Tests/Unity/unity_fixture.c

#Production code file
SRC_FILES = Core/Src/circular_buffer.c Core/Src/parser.c

#Test runner
TEST_FILES = Tests/circular_bufferTest.c Tests/circular_bufferTestRunner.c Tests/all_tests.c Tests/parserTest.c Tests/parserTestRunner.c

#Executable
TARGET = run_tests.exe

#Build
all: $(TARGET)
	./$(TARGET)

$(TARGET): $(UNITY_FILES) $(SRC_FILES) $(TEST_FILES)
	$(CC) $(CFLAGS) $(INC_FLAGS) $^ -o $@

clean:
	rm -f $(TARGET) *.o