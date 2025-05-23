//
// Created by Leighton on 25-5-22.
//

#ifndef HUFFMANCOMPRESSOR_HPP
#define HUFFMANCOMPRESSOR_HPP
#include <vector>
#include <string>
#include <cstddef>
#include "HuffmanTree.hpp"

//Huffman树提供完整编码表，Compressor生成完整的压缩缓冲区
template<typename T>
class HuffmanCompressor {
private:
    std::vector<std::byte> compressedBuffer;
    std::byte currentByte{0};
    int bitPosition = 0;
public:
    void addBit(bool bit) {
        if (bit) {
            currentByte |= static_cast<std::byte>(1 << (7 - bitPosition));
        }
        bitPosition++;

        //byte已满，拷贝至缓冲区
        if (bitPosition == 8) {
            compressedBuffer.push_back(currentByte);
            currentByte = std::byte{0};
            bitPosition = 0;
        }
    }

    //压缩整个rawData，写入缓冲区compressedBuffer
    void CompressFile(HuffmanTree<T>& HT) {
        for (char c : HT.rawData) {
            std::string HuffmanCode = HT.HuffmanCodes[c];
            for (const char code : HuffmanCode) {
                addBit(code == '1');
            }
        }

        //编码收尾过程，处理可能的不完整字节
        if (bitPosition > 0) {
            compressedBuffer.push_back(currentByte);
        }
    }
};

#endif //HUFFMANCOMPRESSOR_HPP
