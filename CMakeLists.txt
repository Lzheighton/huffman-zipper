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
        include/mainwindow.h
        src/mainwindow.cpp
        ui/mainwindow.ui
        ui/ui_mainwindow.h
        include/WorkerThread.hpp
)

add_compile_options(
        /utf-8                   # 指定 UTF-8 编码
        /Zc:__cplusplus          # 返回实际C++标准值，而不是MSVC默认C++98，Qt需要标准检查
        /permissive-             # 启动严格C++标准检查，禁用非标准扩展
        /W3                      # 警告级别3，警告未初始化变量，函数返回值被忽略，可能的数据丢失，未使用的变量
        /wd4819                  # 禁用编码警告
)

target_link_libraries(Huffman_zipper PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

#GoogleTest单元测试
add_subdirectory(GoogleTest)