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
- `writeCompressedFile()`：将元数据和buffer写入文件流，完成压缩

# 解压过程

- `readHeader()`：从文件读取元数据（直接按照元数据模型size读取）
- `readHuffmanCode()`：读取Huffman码表（字符，编码长度，编码字符串）
- `readCompressedData()`：读取压缩后的数据（读取过程未分块，使用了窄式转换，可能存在些许问题）
- `readFile()`：从文件流读取数据，保存至缓冲区（二进制读取）
- `decompresseFile()`：解码文件，保存至result字符串缓冲区
- `writeDecompressedFile()`：将字符串缓冲区写入文件流（覆写），完成解压