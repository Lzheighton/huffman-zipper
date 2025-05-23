#pragma once
#ifndef HUFFMANTREE_HPP
#define HUFFMANTREE_HPP
#include <queue>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <stdexcept>

#include <iostream>
#include "HuffmanNode.hpp"

//定义最小堆，比较节点权重
template<typename T>
struct compareNodes {
    bool operator()(const HuffmanNode<T>* a, const HuffmanNode<T>* b) const {
        return a->weight > b->weight;
    }
};

//基于优先队列实现的Huffman树
template<typename T>
class HuffmanTree {
private:
    //文件流读取的char字符，生命周期伴随整个Huffman树对象（调用栈）
    std::vector<char> rawData;
    //存放huffman结点，以vector为容器的最小优先队列（堆）
    //! priority_queue是容器适配器，容器和适配器的元素类型需相同（存放指针）
    std::priority_queue<HuffmanNode<char>*, std::vector<HuffmanNode<char>*>, compareNodes<char>> pq_min;
    //建成Huffman树后指向根节点
    HuffmanNode<char> *root = nullptr;
    //转换后的Huffman编码对照表
    std::unordered_map<char, std::string> HuffmanCodes;
    //实现完整压缩过程友类
    friend class HuffmanCompressor;

    //*测试友类，提供private数据访问权限（Gtest命名约定）
    friend class HuffmanTreeTest_PrivateAccess_Test;

    //内存释放辅助函数
    void destroyTree(HuffmanNode<char>* node) {
        if (!node) return;

        //* 调试输出，内存检查，防止双重释放
        std::cout << "Attempting to delete node at address: " << static_cast<void*>(node) << std::endl;

        if (node->right) destroyTree(node->right);
        if (node->left) destroyTree(node->left);
        delete node;
        node = nullptr;
    }
public:
    HuffmanTree() = default;
    ~HuffmanTree() {
        destroyTree(root);
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

        //* 调试输出
        std::cout << this->rawData.size() << " bytes read" << std::endl;
        for (char & it : rawData) {
            std::cout << it << " ";
        }

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
            //优先队列存放HuffmanNode指针，运行栈开辟
            auto* neoNode = new HuffmanNode<char>(it.first, it.second);
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
            auto* neoNode = new HuffmanNode<char>(neoWeight);
            neoNode->left = nodeA;
            neoNode->right = nodeB;
            nodeA->parent = neoNode;
            nodeB->parent = neoNode;
            this->pq_min.push(neoNode);
        }

        auto rootPtr = pq_min.top();
        pq_min.pop();
        this->root = rootPtr;
    }

    //通过Huffman树进行压缩，生成Huffman编码表（哈希表）
    void generateHuffmanCode(HuffmanNode<T>* ptr) {
        if (!ptr) return;
        //叶子节点，生成编码
        if (!ptr->left && !ptr->right) {
            HuffmanNode<T>* current = ptr;
            HuffmanNode<T>* parent = ptr->parent;

            //临时编码缓冲区
            std::string cd;
            while (parent) {
                if (current == parent->left) {
                    cd.insert(0, "0");
                }else {
                    cd.insert(0, "1");
                }
                current = parent;
                parent = parent->parent;
            }

            //缓冲区拷贝至哈希表
            this->HuffmanCodes[ptr->value] = cd;
        }
        generateHuffmanCode(ptr->left);
        generateHuffmanCode(ptr->right);
    }
};

#endif //HUFFMANTREE_HPP