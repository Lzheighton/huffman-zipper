#ifndef MODEL_HPP
#define MODEL_HPP
#include <cstdint>

//元数据模型
struct HuffmanHeader {
    char magicNum[2] = {'Y', 'G'};    //魔数，作为文件类型标识符
    uint16_t tableSize{};             //码表大小
    uint64_t originalSize{};          //原始文件大小，用于校验
    uint64_t compressedSize{};        //压缩后的文件大小
    uint8_t paddingBits{};            //最后一个字节的多余位
    char originalExt[32]{};             //定长数组，存储文件原本扩展名
};

#endif //MODEL_HPP
