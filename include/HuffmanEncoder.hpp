#pragma once
#ifndef HUFFMANTREE_HPP
#define HUFFMANTREE_HPP
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <stdexcept>

#include "utils.hpp"
#include "models.hpp"
#include "HuffmanNode.hpp"

//定义最小堆，比较节点权重
struct compareNodes {
    bool operator()(const std::shared_ptr<HuffmanNode<char>>& a, const std::shared_ptr<HuffmanNode<char>>& b) const {
        return a->weight > b->weight;
    }
};

//基于优先队列实现的Huffman树
class HuffmanEncoder {
private:
    //文件流读取的char字符，生命周期伴随整个Huffman树对象（调用栈）
    std::vector<char> rawData;

    //存放huffman结点，以vector为容器的最小优先队列（堆）
    //! priority_queue是容器适配器，容器和适配器的元素类型需相同（存放指针）
    std::priority_queue<std::shared_ptr<HuffmanNode<char>>, std::vector<std::shared_ptr<HuffmanNode<char>>>, compareNodes> pq_min;
    //建成Huffman树后指向根节点
    std::shared_ptr<HuffmanNode<char>> root = nullptr;

    //转换后的Huffman编码对照表
    std::unordered_map<char, std::string> HuffmanCodes;

    //转换后的缓冲区
    std::vector<std::byte> compressedBuffer;
    //压缩辅助共享参数
    std::byte currentByte {0};
    int bitPosition = 0;

    //记忆文件名，文件名与扩展名
    std::string fileName;
    std::string fileType;

    //*测试友类，提供private数据访问权限（Gtest命名约定）
    friend class HuffmanTreeTest_PrivateAccess_Test;

    //压缩辅助函数
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

    //从文件流读入原始文件
    void readFile(const std::string& filePath, std::streamsize chunk_size = 4096) {
        this->rawData.clear();
        std::ifstream ifs(filePath, std::ios::in);

        if (!ifs.is_open()) {
            throw std::runtime_error("Could not open file");
        }

        //按块读取
        std::vector<char> chunk(chunk_size);

        //以char形式读取，传入rawData
        while (ifs.read(chunk.data(), chunk_size) || ifs.gcount() > 0) {
            for (std::streamsize i = 0; i < ifs.gcount(); ++i) {
                this->rawData.push_back(chunk[i]);
            }
        }

        if (ifs.bad()) {
            throw std::runtime_error("File could not be read");
        }

        //C++ 17 filesystem，获取文件名
        std::filesystem::path path(filePath);
        this->fileType = path.extension().string();
        this->fileName = path.stem().string();
        //* 调试输出
        // std::cout << this->rawData.size() << " bytes read" << std::endl;

        // for (char & it : rawData) {
        //     std::cout << it << " ";
        // }

        ifs.close();
    }

    //分析rawData中字符权重，写入优先队列
    void analyseWeight() {
        //局部变量map，用于存储字符-权重键值对
        std::map<char, int> weightMap;
        if (rawData.empty()) {
            throw std::runtime_error("rawData is empty");
        }
        for (const char & it : this->rawData) {
            ++weightMap[it];
        }
        for (const auto & it : weightMap) {
            //std::make_shared创建智能指针对象
            auto neoNode = std::make_shared<HuffmanNode<char>>(it.first, it.second);
            this->pq_min.push(neoNode);
        }
    }

    //建立Huffman树
    void buildHuffmanTree(const std::string& filePath) {
        this->readFile(filePath);
        this->analyseWeight();

        while (pq_min.size() > 1) {
            auto nodeA = pq_min.top();
            pq_min.pop();
            auto nodeB = pq_min.top();
            pq_min.pop();

            int neoWeight = nodeA->weight + nodeB->weight;
            auto neoNode = std::make_shared<HuffmanNode<char>>(neoWeight);
            neoNode->left = nodeA;
            neoNode->right = nodeB;
            //父结点指针使用弱引用，不会增加引用计数
            nodeA->parent = neoNode;
            nodeB->parent = neoNode;
            this->pq_min.push(neoNode);
        }

        if (!this->pq_min.empty()) {
            this->root = this->pq_min.top();
            this->pq_min.pop();
        }
    }

    //通过Huffman树进行压缩，生成Huffman编码表（哈希表）
    void generateHuffmanCode(std::shared_ptr<HuffmanNode<char>>& ptr) {
        if (!ptr) return;
        //叶子节点，生成编码
        if (!ptr->left && !ptr->right) {
            auto current = ptr;

            //通过lock()获取parent若引用的一个shared_ptr
            auto parent = ptr->parent.lock();

            //临时编码缓冲区
            std::string cd;

            //检查是否到达根结点（根节点parent为空指针）
            while (parent) {
                if (current == parent->left) {
                    cd.push_back('0');
                }else {
                    cd.push_back('1');
                }
                current = parent;
                parent = parent->parent.lock();
            }

            //- 优化:先使用push_back完成编码再进行反转
            reverse(cd.begin(), cd.end());

            //缓冲区拷贝至哈希表
            this->HuffmanCodes[ptr->value] = cd;
        }
        generateHuffmanCode(ptr->left);
        generateHuffmanCode(ptr->right);
    }

    //根据码表生成压缩缓冲区
    void CompressFile() {
        for (char c : this->rawData) {
            std::string HuffmanCode = this->HuffmanCodes[c];
            for (const char code : HuffmanCode) {
                addBit(code == '1');
            }
        }

        //编码收尾，处理可能的不完整字节，写入缓冲区
        if (bitPosition > 0) {
            compressedBuffer.push_back(currentByte);
        }
    }

    //将元数据和buffer写入文件
    void writeCompressedFile(const std::string& filePath) {
        //二进制读取，新建文件，后缀名.huf
        std::ofstream ofs(filePath + "\\" + this->fileName + ".huf", std::ios::binary);
        if (!ofs.is_open()) throw std::runtime_error("Could not open file");

        try {
            auto HuffmanMap = hashMapToMap(this->HuffmanCodes);

            HuffmanHeader header = {};
            header.tableSize = HuffmanMap.size();
            header.originalSize = this->rawData.size();
            header.compressedSize = this->compressedBuffer.size();
            header.paddingBits = (8 - this->bitPosition) % 8;

            ofs.write(reinterpret_cast<const char*>(&header), sizeof(header));

            for (const auto & it : HuffmanMap) {
                //依次写入字符，编码长度，具体编码字符串
                ofs.write(&it.first, 1);

                uint8_t codeLength = it.second.length();
                ofs.write(reinterpret_cast<const char*>(&codeLength), 1);

                //类型转换为CStr再写入
                ofs.write(reinterpret_cast<const char*>(it.second.c_str()), codeLength);
            }

            char extBuffer[32];
            strcpy_s(extBuffer, fileType.c_str());

            ofs.write(extBuffer, 32);

            ofs.write(reinterpret_cast<const char*>(compressedBuffer.data()), compressedBuffer.size());
        }catch (std::exception & e) {
            ofs.close();
            throw std::runtime_error(e.what());
        }
        ofs.close();
    }

public:
    HuffmanEncoder() = default;
    ~HuffmanEncoder() = default;

    //整合接口函数
    void encode(const std::string& inputFilePath, const std::string& outputPath){
        this->buildHuffmanTree(inputFilePath);
        this->generateHuffmanCode(this->root);
        this->CompressFile();
        this->writeCompressedFile(outputPath);
    }
};

#endif //HUFFMANTREE_HPP