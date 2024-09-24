#ifndef _BINARY_TREE_NODE_HPP_
#define _BINARY_TREE_NODE_HPP_

#include <iostream>
//引入树节点类
#include "../02-Tree/01-TreeNode.hpp"

//包装一个TreeNode<T>对象，对外构成一个二叉树节点类（使用继承要重写好多，太麻烦了）
template <typename T>
class BinaryTreeNode
{
protected:
    TreeNode<T>* coreNode;                            //作为内核节点，其子节点受到约束
    BinaryTreeNode<T>* leftSubNode;                   //左子节点指针
    BinaryTreeNode<T>* rightSubNode;                  //右子节点指针
    
public:
    BinaryTreeNode(const T & = T());                  //构造函数，初始化节点存储的数据
    
    T GetNodeData() const;                            //获取该树节点存储的数据值
    bool IsRoot() const;                              //该节点是否是根节点（树的发端）
    bool IsLeaf() const;                              //该节点是否是叶节点（树的末端）
    int GetSize() const;                              //获取以该节点及其所有后代的个数
    int GetDepth() const;                             //获取以该节点为根节点的树的深度
    int GetDegree() const;                            //获取该节点的度，即子节点个数
    TreeNode<T>* GetCoreNode() const;                 //获取内核节点指针
    BinaryTreeNode<T>* GetParentPtr() const;          //获取指向父节点的指针
    BinaryTreeNode<T>* GetLeftSubNodePtr() const;     //获取左节点指针
    BinaryTreeNode<T>* GetRightSubNodePtr() const;    //获取右节点指针
    void PrintTree() const;                           //完整打印以该节点为根节点的树

    // void SetLeftSubNode(T);                           //以值形式设置左子节点
    // void SetLeftSubNode(BinaryTreeNode<T>*);          //以节点指针形式设置左子节点/树
    // void SetRightSubNode(T);                          //以值形式设置右子节点
    // void SetRightSubNode(BinaryTreeNode<T>*);         //以节点指针形式设置右子节点/树

// protected:
    // void PrintTree(int) const;                        //依据传入深度打印出基于相应层级的树
};

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T& _data)
{
    //在堆区初始化一个TreeNode<T>对象
    coreNode = new TreeNode<T>(_data);
    //初始化为指向空指针
    leftSubNode = nullptr;
    rightSubNode = nullptr;
}

template <typename T>
T BinaryTreeNode<T>::GetNodeData() const
{
    return coreNode->GetNodeData();
}

template <typename T>
bool BinaryTreeNode<T>::IsRoot() const
{
    return coreNode->IsRoot();
}

template <typename T>
bool BinaryTreeNode<T>::IsLeaf() const
{
    return coreNode->IsLeaf();
}

template <typename T>
int BinaryTreeNode<T>::GetSize() const
{
    return coreNode->GetSize();
}

template <typename T>
int BinaryTreeNode<T>::GetDepth() const
{
    return coreNode->GetDepth();
}

template <typename T>
int BinaryTreeNode<T>::GetDegree() const
{
    return coreNode->GetDegree();
}

template <typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::GetParentPtr() const
{
    // return coreNode->GetParentPtr();
}

template <typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::GetLeftSubNodePtr() const
{
    return leftSubNode;
}

template <typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::GetRightSubNodePtr() const
{
    return rightSubNode;
}

// template <typename T>
// void BinaryTreeNode<T>::PrintTree() const
// {
//     this->PrintTree(0);
// }

// template <typename T>
// void BinaryTreeNode<T>::SetLeftSubNode(T _obj)
// {
//     if (leftSubNode == nullptr)
//     {
//         //通过基类的方法将传入节点添加到childList中去
//         this->AddChild(_obj);
//         //由于AddChild使用深拷贝，而不是直接将传入节点当作子节点，所以此处要将指针指向childList中的新节点，而非传入节点
//         leftSubNode = this->childList.GetBackPtr();

//         //返回1表示添加成功
//         return 1;
//     }
//     else
//     {
//         //否则说明以及有了左子节点，返回0表示添加失败
//         return 0;
//     }
// }

// template <typename T>
// void BinaryTreeNode<T>::SetLeftSubNode(BinaryTreeNode<T>* _obj)
// {
    
// }

// template <typename T>
// void BinaryTreeNode<T>::SetRightSubNode(T _obj)
// {
//     if (rightSubNode == nullptr)
//     {
//         //通过基类的方法将传入节点添加到childList中去
//         this->AddChild(_obj);
//         //由于AddChild使用深拷贝，而不是直接将传入节点当作子节点，所以此处要将指针指向childList中的新节点，而非传入节点
//         rightSubNode = this->childList.GetBackPtr();

//         //返回1表示添加成功
//         return 1;
//     }
//     else
//     {
//         //否则说明以及有了右子节点，返回0表示添加失败
//         return 0;
//     }
// }

// template <typename T>
// void BinaryTreeNode<T>::SetRightSubNode(BinaryTreeNode<T>* _obj)
// {

// }

// template <typename T>
// void BinaryTreeNode<T>::PrintTree(int _depth) const
// {
//     //根据传入的深度参数，得知当前节点处于多深，打印时需要在前面垫上相应的深度
//     for (int i = 0; i < _depth; i++)
//     {
//         std::cout << "\t";
//     }

//     //打印节点本身
//     std::cout << "-[" << this->GetNodeData() << "]\n";

//     //如果有后代，就以深度优先遍历所有后代
//     if (!this->IsLeaf())
//     {
//         if (leftSubNode != nullptr)
//             leftSubNode->PrintTree(_depth + 1);
//         else
//             std::cout << "-[]\n";

//         if (rightSubNode != nullptr)
//             rightSubNode->PrintTree(_depth + 1);
//         else
//             std::cout << "-[]\n";
//     }
// }

namespace Test_Binary_Tree_Node
{
    void TestBasicFunctions()
    {
        BinaryTreeNode<int> binTree(111);
        std::cout << binTree.GetNodeData() << "\n";
    }

    void TestPrinting()
    {
        
    }

    void MainTest()
    {
        std::cout << "--------------------------------------------------\n";

        std::cout << "--------------------TestArea01--------------------\n";
        TestBasicFunctions();
        std::cout << "--------------------TestArea02--------------------\n";
        TestPrinting();

        std::cout << "--------------------------------------------------\n";
    }
}

#endif