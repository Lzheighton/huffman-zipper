# Huffman压缩后的文件结构

## 元数据

- HuffmanCodes Huffman码表，二进制编码与原始符号对应关系
- 数据填充信息：最后一个字节的压缩数据可能不完整，包含一些无意义的填充位置
- 原始文件大小/符号数量：md5值，用于解压完成后的完整性校验/解压缩预分配内存
- MagicNumber：文件开头的特殊字节，用于识别文件类型

## 压缩后的源文件

# 压缩过程

- `buildHuffmanTree()`：建立Huffman树
- `generateHuffmanCode()`：生成Huffman码表，哈希表
- `CompressFile()`：按照码表对rawData进行压缩，生成编码至buffer
- `writeCompressedFile()`：将元数据和buffer写入文件，完成压缩

# 解压过程

还没写🧐