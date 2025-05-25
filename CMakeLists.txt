cmake_minimum_required(VERSION 3.31)
project(Huffman_zipper)

set(CMAKE_CXX_STANDARD 17)

add_executable(Huffman_zipper src/main.cpp
        include/HuffmanEncoder.hpp
        include/HuffmanNode.hpp
        include/utils.hpp
        include/models.hpp
        include/HuffmanDecoder.hpp
)

INCLUDE_DIRECTORIES(include)

#GoogleTest单元测试
add_subdirectory(GoogleTest)