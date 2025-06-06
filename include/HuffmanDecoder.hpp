#pragma once
#ifndef HUFFMANDECODER_HPP
#define HUFFMANDECODER_HPP
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

#include "models.hpp"

//解压缩类，与压缩类镜像对称
class HuffmanDecoder {
private:
    //元数据模型
    HuffmanHeader header;
    //解码后的码表
    std::unordered_map<std::string, unsigned char> HuffmanCodes;
    //从元数据中转换得到的扩展名与当前压缩文件名
    std::string fileExt;
    std::string fileName;
    //从文件流读取的压缩后数据以及完成解码后的源数据
    std::vector<std::byte> compressedData;
    std::vector<unsigned char> decompressedResult;

    //读取元数据
    void readHeader(std::ifstream& ifs) {
        ifs.read(reinterpret_cast<char*>(&this->header), sizeof(this->header));
        if (ifs.bad()) {
            throw std::runtime_error("Error while reading header");
        }
    }

    //读取码表
    void readHuffmanCodes(std::ifstream& ifs) {
        this->HuffmanCodes.clear();

        for (uint16_t i = 0; i < header.tableSize; ++i) {
            //顺序读取字符，编码长度，编码后的字符串
            unsigned char character;
            ifs.read(reinterpret_cast<char*>(&character), 1);

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

    //从文件流读入原始文件
    void readFile(const std::string& filePath) {
        this->compressedData.clear();
        //二进制读取，不做任何解码
        std::ifstream ifs(filePath, std::ios::in | std::ios::binary);

        if (!ifs.is_open()) {
            throw std::runtime_error("Could not open file");
        }

        try {
            readHeader(ifs);

            if (header.magicNum[0] != 'Y' || header.magicNum[1] != 'G') {
                throw std::runtime_error("Invalid type of file");
            }

            this->fileExt = std::string(header.originalExt);

            readHuffmanCodes(ifs);
            readCompressedData(ifs);
        }catch (std::exception& e) {
            throw std::runtime_error(e.what());
        }

        std::filesystem::path path(filePath);
        this->fileName = path.stem().string();

        ifs.close();
    }

    //解码
    void DecompressFile() {
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
                    this->decompressedResult.push_back(it->second);
                    deCompressBuffer.clear();
                }
                ++processedBits;
            }
            if (processedBits >= totalBits) break;
        }
    }

    //写入文件
    void writeDeCompressedFile(const std::string& filePath) {
        std::ofstream ofs(filePath + "\\" + this->fileName + this->fileExt, std::ios::out | std::ios::binary);

        if (!ofs.is_open()) {
            throw std::runtime_error("Could not open file");
        }

        ofs.write(reinterpret_cast<const char*>(this->decompressedResult.data()),
                this->decompressedResult.size());

        ofs.close();
    }

public:
    HuffmanDecoder() = default;
    ~HuffmanDecoder() = default;

    void decode(const std::string& inputFilePath, const std::string& outputPath) {
        this->readFile(inputFilePath);
        this->DecompressFile();
        this->writeDeCompressedFile(outputPath);
    }
};

#endif //HUFFMANDECODER_HPP
