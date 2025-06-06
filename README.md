# 功能

✔️​基于Huffman树生成不等长编码压缩文件

✔️​通过元数据内码表解压缩文件

✔️对文件进行SHA256校验（openssl库）

## 元数据模型

- MagicNumber：文件开头的特殊字节，用于识别文件类型
- Huffman码表的大小
- 源文件大小（待完成功能：压缩前与压缩后的校验）
- 压缩后文件大小
- （可能新增的功能）：源文件的SHA256，用于校验
- 数据填充信息：最后一个字节的压缩数据可能不完整，包含一些无意义的填充位置

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

# RAII与智能指针

## 对象生命周期

全局对象：程序启动时分配，程序结束时销毁

局部对象：进入语句块时创建，离开语句块时被销毁

局部static对象：在第一次使用时分配，程序结束时被销毁

动态分配对象：通过`new`运算符创建（返回一个指向该对象的指针），`delete`销毁（显式销毁）

## 🤖智能指针

`std::<memeory>`标准库提供了智能指针类型来管理动态对象，智能指针的行为类似常规指针，但其负责自动释放所指向的对象

### `std::unique_ptr`

独占所有权

同一时间内，只有一个`std::unique_ptr`可以指向一个给定的对象，拥有堆所指对象的独占所有权

当`std::unique_ptr`被销毁（例如离开块级作用域）时，自动销毁对应的内存对象

不能被复制，但可以通过`std::move`转移所有权（至另一个`std::unique_ptr`)

不涉及引用计数，通常**与原始指针具有相同的性能开销**

### `std::shared_ptr`

多个智能指针共享一个内存对象

内存对象带有引用计数，记录指向其的指针数量

每销毁一个智能指针对象，导致引用计数自减，直到0，销毁该对象

构造：`make_shared<T>`创建，或是通过拷贝或赋值另一个`shared_ptr`来创建

内部实现：该类内的引用计数包含两个指针成员，一个是所管理的数据的地址，另一个是控制块的地址，不同的智能指针需要共享相同的内存对象，因而引用计数的存储在堆上

`shared_ptr`维护两个指针，因而大小是`unique_ptr`的两倍

### `std::weak_ptr`

弱引用，用于避免循环引用，调用`weak_ptr.lock()`可以找到指向该目标对象的一个`shared_ptr`进行指针转换

本项目中，Huffman结点的父结点指针使用了弱引用，以防止循环引用产生的内存泄漏（循环引用下引用计数不会降为0，对象不会自动销毁）

# 📄文件流`std::<fstream>`

所有的流（控制台IO流iostream，文件IO流fstream）都以stream类作为基础，流缓冲就是内存空间

stream类重载了`<<`和`>>`作为插入器和析取器

## 成员函数：`open()`

函数原型：`void open(const char* filename, int mode, int access);`

打开的文件路径+打开模式+打开文件属性

|   模式常用值    |               打开方式                |
| :-------------: | :-----------------------------------: |
|    ios::app     |         以追加的方式打开文件          |
|    ios::ate     | 文件打开后定位到末尾（app包含该模式） |
|   ios::binary   |  以二进制方式打开文件，不做任何转码   |
|     ios::in     | 文件以输入方式打开（文件输入到内存）  |
|    ios::out     | 文件以输出方式打开（内存输出到文件）  |
|  ios::nocreate  |   不创建文件，文件不存在则打开失败    |
| ios::norepleace |    不覆盖文件，文件存在则打开失败     |
|   ios::trunc    |               覆写文件                |

可以通过管道符连接多个属性：`ios::binary|ios::in`组合模式

两种对象默认带有`in/out`模式，只需要文件路径

## 关闭文件`ifs/ofs.close()`

## 读写文件

一般的文本文件：通过插入器和析取器

二进制文件：

- `put()`：向流写入一个字符

- `get()`：三种函数原型：

    `ifstream& get(char& ch)`：从流中读取一个字符，结果保存在引用ch中（文件流末尾则返回空字符）``

    `ifstream& get()`：从流中返回一个字符，到达文件末尾则返回EOF

    `ifstream &get(char *buf,int num,char delim='\n')`：固定为char类型指针，将字符读入该数组，直到读取了num个字符或是到达了由delim指定的结束字符

读写二进制数据块：

两个成员函数：`read(unsigned char *buf,int num)` 　`write(const unsigned char *buf,int num)`

1. 读取num个字符至buf指向的缓存，若在未读取到num个字符就到达了文件末尾，可使用`gcount()`返回实际读取字符数

2. 从buf指向的缓存取num个字符写入文件中，const unsigned char需要强制类型转换`reinterpret_cast`

辅助函数：`ifs/ofs.eof()`检查是否到达文件尾，到达返回非零值，没到达返回0（返回整型）

