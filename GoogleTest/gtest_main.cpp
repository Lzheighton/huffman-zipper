#include "HuffmanDecoder.hpp"
#include "gtest/gtest.h"
#include "gtest/internal/gtest-port.h"
#include "HuffmanEncoder.hpp"

//参数：测试套件，测试命名
TEST(HuffmanTree, InitializeObject) {
    HuffmanEncoder tree;
}

TEST(HuffmanTreeTest, PrivateAccess) {
    HuffmanEncoder encoder;
    //tree.readFile("D:/ClionProjects/Huffman-zipper/test.txt");
    //tree.analyseWeight();

    //auto ptr = tree.pq_min.top();

    //EQ需要类型匹配'1'和1，字符型和整型
    //EXPECT_EQ(ptr->value, '1');
    //EXPECT_EQ(ptr->weight, 3);

    encoder.buildHuffmanTree("D:/ClionProjects/Huffman-zipper/test.txt");
    auto rootPtr = encoder.root;
    // EXPECT_EQ(rootPtr->value, '1');
    // EXPECT_EQ(rootPtr->weight, 3);

    encoder.generateHuffmanCode(rootPtr);
    std::cout << std::endl;
    for (const auto& pair : encoder.HuffmanCodes) {
        const std::string& code = pair.second;
        std::cout << pair.first << "->" << code << std::endl;
    }

    encoder.CompressFile();
    for (const auto& byte : encoder.compressedBuffer) {
        std::cout << (int)byte << std::endl;
    }

    encoder.writeCompressedFile("D:/ClionProjects/Huffman-zipper/target.txt");
}

TEST(HuffmanDecoderTest, PrivateAccess) {
    HuffmanDecoder decoder;
    decoder.readFile("D:/ClionProjects/Huffman-zipper/target.txt");
    for (const auto& pair : decoder.HuffmanCodes) {
        std::cout << pair.first << "->" << pair.second << std::endl;
    }
    decoder.DecompressFile();
    std::cout << decoder.decompressedResult << std::endl;
    std::cout << decoder.decompressedResult[0] << std::endl;

    decoder.writeDeCompressedFile("D:/ClionProjects/Huffman-zipper/test.txt");
}

GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}