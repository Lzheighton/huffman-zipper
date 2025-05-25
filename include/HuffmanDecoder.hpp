#ifndef HUFFMANDECODER_HPP
#define HUFFMANDECODER_HPP
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "models.hpp"

//解压缩类，与压缩类镜像对称
class HuffmanDecoder {
private:
    //元数据模型
    HuffmanHeader header;
    //解码后的码表
    std::unordered_map<std::string, char> HuffmanCodes;
    //从文件流读取的压缩后数据以及完成解码后的源数据
    std::vector<std::byte> compressedData;
    std::string decompressedResult;

    //读取元数据
    void readHeader(std::ifstream& ifs) {
        ifs.read(reinterpret_cast<char*>(&header), sizeof(header));
        if (ifs.bad()) {
            throw std::runtime_error("Error while reading header");
        }
    }

    //读取码表
    void readHuffmanCodes(std::ifstream& ifs) {
        this->HuffmanCodes.clear();

        for (uint16_t i = 0; i < header.tableSize; ++i) {
            //顺序读取字符，编码长度，编码后的字符串
            char character;
            ifs.read(&character, 1);

            uint8_t codeLength;
            ifs.read(reinterpret_cast<char*>(&codeLength), 1);

            std::string str(codeLength, '\0');
            ifs.read(&str[0], codeLength);

            this->HuffmanCodes[str] = character;

            if (ifs.bad()) {
                throw std::runtime_error("Error while reading huffman code table");
            }
        }
    }

    //读取压缩后数据
    void readCompressedData(std::ifstream& ifs) {
        //! 根据元数据设定大小，减少内存开销
        compressedData.resize(header.compressedSize);
        ifs.read(reinterpret_cast<char*>(compressedData.data()), static_cast<std::streamsize>(header.compressedSize));
        if (ifs.bad()) {
            throw std::runtime_error("Error while reading compressed data");
        }
    }

    //*测试友类
    friend class HuffmanDecoderTest_PrivateAccess_Test;
public:
    HuffmanDecoder() = default;
    ~HuffmanDecoder() = default;

    //从文件流读入原始文件
    void readFile(const std::string& filePath) {
        this->compressedData.clear();
        //二进制读取，不做任何解码
        std::ifstream ifs(filePath, std::ios::binary);

        if (!ifs.is_open()) {
            throw std::runtime_error("Could not open file");
        }

        try {
            readHeader(ifs);

            if (header.magicNum[0] != 'Y' || header.magicNum[1] != 'G') {
                throw std::runtime_error("Invalid type of file");
            }

            readHuffmanCodes(ifs);
            readCompressedData(ifs);
        }catch (std::exception& e) {
            std::cout << "文件读取失败：" << e.what() << std::endl;
        }

        ifs.close();
    }

    //解码
    void DeCompressFile() {
        this->decompressedResult.clear();
        //std::string.reserve() 预留容量空间
        //! 不可使用resize()，会使用空字符填充空间，导致输出带空白字符
        this->decompressedResult.reserve(header.originalSize);

        std::string deCompressBuffer;
        size_t totalBits = header.compressedSize * 8 - header.paddingBits;
        size_t processedBits = 0;

        for (const auto& byte : compressedData) {
            for (int i = 7; i >= 0; --i) {
                if (processedBits >= totalBits) break;

                bool bitValue = static_cast<bool>(byte & std::byte{static_cast<unsigned char>(1 << i)});
                deCompressBuffer += (bitValue ? "1" : "0");

                //! 不定长编码，检查码表操作在for循环内
                auto it = HuffmanCodes.find(deCompressBuffer);
                if (it != HuffmanCodes.end()) {
                    this->decompressedResult += it->second;
                    deCompressBuffer.clear();
                }
                ++processedBits;
            }
            if (processedBits >= totalBits) break;
        }
    }

    //写入文件
    void writeDeCompressedFile(const std::string& filePath) {
        std::ofstream ofs(filePath, std::ios::out | std::ios::trunc);
        if (!ofs.is_open()) {
            throw std::runtime_error("Could not open file");
        }
        ofs << decompressedResult;
        ofs.close();
    }
};

#endif //HUFFMANDECODER_HPP
