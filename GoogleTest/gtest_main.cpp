#include "gtest/gtest.h"
#include "gtest/internal/gtest-port.h"
#include "HuffmanTree.hpp"

//参数：测试套件，测试命名
TEST(HuffmanTree, InitializeObject) {
    HuffmanTree<int> tree;
}

TEST(HuffmanTreeTest, PrivateAccess) {
    HuffmanTree<int> tree;
    //tree.readFile("D:/ClionProjects/Huffman-zipper/test.txt");
    //tree.analyseWeight();

    //auto ptr = tree.pq_min.top();

    //EQ需要类型匹配'1'和1，字符型和整型
    //EXPECT_EQ(ptr->value, '1');
    //EXPECT_EQ(ptr->weight, 3);

    tree.buildHuffmanTree("D:/ClionProjects/Huffman-zipper/test.txt");
    auto rootPtr = tree.root;
    // EXPECT_EQ(rootPtr->value, '1');
    // EXPECT_EQ(rootPtr->weight, 3);

    tree.generateHuffmanCode(rootPtr);
    std::cout << std::endl;
    for (const auto& pair : tree.HuffmanCodes) {
        const std::string& code = pair.second;
        std::cout << pair.first << "->" << code << std::endl;
    }

    tree.CompressFile();
    for (const auto& byte : tree.compressedBuffer) {
        std::cout << (int)byte << std::endl;
    }
}

GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}