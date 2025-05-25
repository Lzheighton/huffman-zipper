#include "HuffmanEncoder.hpp"

int main() {
    HuffmanEncoder<int> tree;
    tree.readFile("D:/ClionProjects/Huffman-zipper/test.txt");

    return 0;
}