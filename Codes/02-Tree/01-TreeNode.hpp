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
    T nodeData;                              //该节点存储的数据
    TreeNode<T>* parentNode;                 //该节点的父节点指针
    SingleLinkedList<TreeNode<T>> childList; //该节点的子节点

public:
    //构造函数，初始化节点存储的数据以及该节点的父节点指针
    TreeNode(const T & = T(), TreeNode<T>* = nullptr);

    T GetNodeData() const;                   //获取该树节点存储的数据值
    bool IsRoot() const;                     //该节点是否是根节点（树的发端）
    bool IsLeaf() const;                     //该节点是否是叶节点（树的末端）
    // int GetDepth() const;                    //获取以该节点为根节点的树的深度
    // int GetSize() const;                     //获取以该节点及其所有后代的个数
    int GetDegree() const;                   //获取该节点的度，即子节点个数
    TreeNode<T>* GetParentPtr() const;       //获取指向父节点的指针
    TreeNode<T>* GetChildPtr(int) const;     //以索引获取指向某子节点的指针
    void PrintSelf() const;                  //打印该节点自身及其父子（调试用）

    void AddChild(TreeNode<T>*);             //以传入节点的方式添加子节点
    void AddChild(T);                        //以传入新元素的方式添加子节点
    void DelChild(int);                      //通过索引删除子节点
    void DelChild(TreeNode<T>*);             //通过地址删除子节点
    void AttachTo(TreeNode<T>*);             //为此节点变更父节点
    void Detach();                           //解除自身与父节点的链接
};

template <typename T>
TreeNode<T>::TreeNode(const T & _data, TreeNode<T> * _node)
{
    nodeData = _data;
    parentNode = _node;
}

template <typename T>
T TreeNode<T>::GetNodeData() const
{
    return nodeData;
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

// template <typename T>
// int TreeNode<T>::GetDepth() const
// {
    
// }

// template <typename T>
// int TreeNode<T>::GetSize() const
// {
    
// }

template <typename T>
int TreeNode<T>::GetDegree() const
{
    return childList.GetLength();
}

template <typename T>
TreeNode<T>* TreeNode<T>::GetParentPtr() const
{
    return parentNode;
}

template <typename T>
TreeNode<T>* TreeNode<T>::GetChildPtr(int _idx) const
{
    if (_idx < 0 || _idx >= GetDegree())
        throw std::invalid_argument("ERROR: Invalid Child Index Calling {TreeNode<T>* TreeNode<T>::GetChildPtr(int _idx) const}");
    return childList.GetElemPtr(_idx);
}

template <typename T>
void TreeNode<T>::PrintSelf() const
{
    if (parentNode == nullptr)
        std::cout << "NULLPTR\n";
    else
        std::cout << "{" << parentNode->GetNodeData() << "}\n";
    std::cout << "|\n";
    std::cout << "{" << this->GetNodeData() << "}\n";
    for (int i = 0; i < childList.GetLength(); i++)
    {
        std::cout << "|\t";
    }
    std::cout << "\n";
    if (!IsLeaf())
    {
        for (int i = 0; i < childList.GetLength(); i++)
        {
            std::cout << "{" << childList.GetElemPtr(i)->GetNodeData() << "}\t";
        }
        std::cout << "\n";
    }
}

template <typename T>
void TreeNode<T>::AddChild(TreeNode<T>* _node)
{
    _node->AttachTo(this);
}

template <typename T>
void TreeNode<T>::AddChild(T _obj)
{
    //将传入的值在堆区包装成节点类后添加为子节点，其堆区内存会被单向链表类的析构函数销毁
    AddChild(new TreeNode<T>(_obj, nullptr));
}

template <typename T>
void TreeNode<T>::DelChild(int _idx)
{
    childList.GetElemPtr(_idx)->Detach();
}

template <typename T>
void TreeNode<T>::DelChild(TreeNode<T>* _node)
{
    _node->Detach();
}

template <typename T>
void TreeNode<T>::AttachTo(TreeNode<T>* _node)
{
    //只有根节点才能被附加到别的节点上作为子节点
    if (IsRoot())
    {
        //需要维护的两个成员：一个是自身的父节点，一个是父节点的子节点列表
        parentNode = _node;
        _node->childList.PushBack(*this);
    }
    else
        throw std::invalid_argument("ERROR: Unable To Attach Internal TreeNode To Another");
}

template <typename T>
void TreeNode<T>::Detach()
{
    if (IsRoot())
        return;

    //需要维护的两个成员：一个是父节点的子节点列表，一个是自身的父节点
    parentNode->childList.Erase(parentNode->childList.Find(this));
    parentNode = nullptr;
}

namespace Test_Tree_Node
{
    void MainTest()
    {
        std::cout << "--------------------------------------------------" << "\n";

        //测试初始化
        TreeNode<int> tree(999);
        tree.PrintSelf();
        // NULLPTR
        // |
        // {999}

        //测试两种新增子节点的方式
        tree.AddChild(111); std::cout << "**AddChild(111)\n";
        tree.AddChild(222); std::cout << "**AddChild(222)\n";
        tree.PrintSelf();
        // NULLPTR
        // |
        // {999}
        // |       |
        // {111}   {222}

        TreeNode<int> node222(333);
        TreeNode<int> node333(444);
        tree.AddChild(&node222); std::cout << "**AddChild(node333)\n";
        tree.AddChild(&node333); std::cout << "**AddChild(node444)\n";
        tree.PrintSelf();
        // NULLPTR
        // |
        // {999}
        // |       |       |       |
        // {111}   {222}   {333}   {444}
        
        //测试两种删除子节点的方式
        tree.DelChild(0); std::cout << "**DelChild(0)\n";
        tree.PrintSelf();
        // NULLPTR
        // |
        // {999}
        // |       |       |
        // {222}   {333}   {444}

        std::cout << "--------------------------------------------------" << "\n";
    }
}

#endif