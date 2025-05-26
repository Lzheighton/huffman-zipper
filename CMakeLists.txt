cmake_minimum_required(VERSION 3.31)
project(Huffman_zipper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH  "C:/Qt/6.9.0/msvc2022_64")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_AUTOMOC ON) #自动处理Qt的元对象编译器
set(CMAKE_AUTORCC ON) #自动处理资源文件
set(CMAKE_AUTOUIC ON) #自动处理UI文件

INCLUDE_DIRECTORIES(include ui)

qt_add_executable(Huffman_zipper src/main.cpp
        include/HuffmanEncoder.hpp
        include/HuffmanNode.hpp
        include/utils.hpp
        include/models.hpp
        include/HuffmanDecoder.hpp
        ui/mainwindow.cpp
        ui/mainwindow.h
        ui/mainwindow.ui
        ui/ui_mainwindow.h
)

target_link_libraries(Huffman_zipper PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

#GoogleTest单元测试
add_subdirectory(GoogleTest)