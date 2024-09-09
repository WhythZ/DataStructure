#ifndef _TREE_NODE_HPP_
#define _TREE_NODE_HPP_

#include <iostream>
//引入单向链表进行子节点的存储
#include "../01-LinearList/02-SingleLinkedList.hpp"

//最基本的树节点结构，存储其父子两层节点的指针，以及存储在该节点数据
template <typename T>
class TreeNode
{
private:
    T nodeData;                       //该节点存储的数据
    TreeNode<T>* parentNode;          //该节点的父节点指针
    SingleLinkedList childList;       //该节点的子节点

public:
    //构造函数，初始化节点存储的数据以及该节点的父节点指针
    TreeNode(const T & = T(), TreeNode<T>* = nullptr);

    T GetNodeData() const;            //获取该树节点存储的数据值
    bool IsRoot() const;              //该节点是否是根节点（树的发端）
    bool IsLeaf() const;              //该节点是否是叶节点（树的末端）
    int GetDepth() const;             //获取以该节点为根节点的树的深度
    int GetDegree() const;            //获取该节点的度（字节点个数）
    TreeNode<T>* GetParent() const;   //获取指向父节点的指针
    TreeNode<T>* GetChild(int) const; //以索引获取指向某子节点的指针

    void AddChild(const T&);          //添加子节点
    void AttachTo(TreeNode<T>*);      //为此节点变更父节点
    void Detach();                    //解除与父节点的链接
};

template <typename T>
TreeNode<T>::TreeNode(const T & _data = T(), TreeNode<T> * _node = nullptr)
{
    nodeData = _data;
    parentNode = _node;
}

template <typename T>
T TreeNode<T>::GetNodeData() const
{
    return nodeValue;
}

template <typename T>
bool TreeNode<T>::IsRoot() const
{
    return (parentNode == nullptr);
}

template <typename T>
bool TreeNode<T>::IsLeaf() const
{
    return (GetDegree() == 0);
}

template <typename T>
int TreeNode<T>::GetDepth() const
{

}

template <typename T>
int TreeNode<T>::GetDegree() const
{
    return childList.GetLength();
}

template <typename T>
TreeNode<T>* TreeNode<T>::GetParent() const
{
    return parentNode;
}

template <typename T>
TreeNode<T>* TreeNode<T>::GetChild(int _idx) const
{
    
}

namespace Test_Tree_Node
{
    void MainTest()
    {
        std::cout << "--------------------------------------------------" << "\n";

        //测试

        std::cout << "--------------------------------------------------" << "\n";
    }
}

#endif