#定义子测试项目名称
project(Google_tests)

add_subdirectory(lib/googletest-1.17.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run ../include/HuffmanCompressor.hpp
        ../include/HuffmanNode.hpp ../include/HuffmanTree.hpp
        gtest_main.cpp
)

target_link_libraries(Google_Tests_run gtest gtest_main)