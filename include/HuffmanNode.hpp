//
// Created by Leighton on 25-5-21.
//

#ifndef HUFFMANNODE_HPP
#define HUFFMANNODE_HPP
#include <memory>

//二叉树结点，存放数据，父指针以及左右指针

//泛型一般被设定为char字符型
template<typename T>
struct HuffmanNode {
    T value;                //结点的具体字符
    int weight;             //结点的权重

    /*
     * 引入智能指针解决内存问题
     * 左右指针均为共享智能指针，单一结点对象可以被多个指针指向共享
     * 父结点指针被设定为弱引用以避免循环引用
     */

    std::shared_ptr<HuffmanNode<T>> left;
    std::shared_ptr<HuffmanNode<T>> right;
    std::weak_ptr<HuffmanNode<T>> parent;

    //两种构造函数，叶子结点包含具体值，一般结点权重是子结点的和而不含值
    HuffmanNode(T data, int weight): value(data), weight(weight) {}
    explicit HuffmanNode(int weight): value(T()), weight(weight) {}
};

#endif //HUFFMANNODE_HPP
