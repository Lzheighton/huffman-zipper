cmake_minimum_required(VERSION 3.31)
project(Huffman_zipper)

set(CMAKE_CXX_STANDARD 17)

add_executable(Huffman_zipper src/main.cpp
        include/HuffmanTree.hpp
        include/HuffmanNode.hpp
        include/HuffmanCompressor.hpp)

INCLUDE_DIRECTORIES(include)

#GoogleTest单元测试
add_subdirectory(GoogleTest)