//
// Created by Leighton on 25-5-21.
//

#ifndef HUFFMANNODE_HPP
#define HUFFMANNODE_HPP

//二叉树结点，存放数据，父指针以及左右指针

//泛型一般被设定为char字符型
template<typename T>
struct HuffmanNode {
    T value;                //结点的具体字符
    int weight;             //结点的权重
    HuffmanNode<T>* left;   //父指针和左右指针
    HuffmanNode<T>* right;
    HuffmanNode<T>* parent;

    //两种构造函数，叶子结点包含具体值，一般结点权重是子结点的和而不含值
    HuffmanNode(T data, int weight): value(data), weight(weight), left(nullptr), right(nullptr), parent(nullptr) {}
    explicit HuffmanNode(int weight): value(T()), weight(weight), left(nullptr), right(nullptr), parent(nullptr) {}
};

#endif //HUFFMANNODE_HPP
