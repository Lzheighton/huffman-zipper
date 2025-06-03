cmake_minimum_required(VERSION 3.31)
project(Huffman_zipper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH  "C:/Qt/6.9.0/msvc2022_64")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Svg SvgWidgets)
find_package(OpenSSL REQUIRED)

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
        Qt6::Svg
        Qt6::SvgWidgets
)

target_link_directories(Huffman_zipper PRIVATE ${OPENSSL_CRYPTO_LIBRARY})
target_include_directories(Huffman_zipper PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_libraries(Huffman_zipper PRIVATE OpenSSL::SSL OpenSSL::Crypto)

## 使用相对路径收集文件
#file(GLOB LOADING_IMAGES
#        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
#        "resources/loading/*.png")
#
## 添加资源
#qt_add_resources(Huffman_zipper "animations"
#        PREFIX "/"
#        FILES ${LOADING_IMAGES}
#)

file(GLOB LOADING_SVG
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "resources/DoubleRing.svg")

qt_add_resources(Huffman_zipper "svg_resources"
        FILES ${LOADING_SVG}
)

target_sources(Huffman_zipper PRIVATE resources/resources.rc)
set_property(SOURCE resources/resources.rc PROPERTY CMAKE_RC_INPUT_FORMAT RESOURCE)
set_target_properties(Huffman_zipper PROPERTIES WIN32_EXECUTABLE TRUE)

#GoogleTest单元测试
add_subdirectory(GoogleTest)