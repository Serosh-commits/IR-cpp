cmake_minimum_required(VERSION 3.14)
project(Lexicon VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/Core/Tokenizer.cpp
    src/Core/EditDistance.cpp
    src/Index/InvertedIndex.cpp
    src/Index/KGramIndex.cpp
    src/Index/QueryProcessor.cpp
)

# Core Library
add_library(LexiconCore ${SOURCES})

# Example Executable
add_executable(lexicon_cli examples/main.cpp)
target_link_libraries(lexicon_cli PRIVATE LexiconCore)

# Tests
enable_testing()
add_executable(test_boolean tests/test_boolean.cpp)
target_link_libraries(test_boolean PRIVATE LexiconCore)
add_test(NAME BooleanRetrievalTest COMMAND test_boolean)

add_executable(test_tolerant tests/test_tolerant.cpp)
target_link_libraries(test_tolerant PRIVATE LexiconCore)
add_test(NAME TolerantRetrievalTest COMMAND test_tolerant)
