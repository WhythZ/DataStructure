#ifndef _BINARY_TREE_NODE_HPP_
#define _BINARY_TREE_NODE_HPP_

#include <iostream>

//二叉树节点类
template <typename T>
class BinaryTreeNode
{
protected:
    T nodeData;                                              //该节点存储的数据
    BinaryTreeNode<T>* parentNode;                           //该节点的父节点指针
    BinaryTreeNode<T>* leftChild;                            //该节点的左子节点（树）指针
    BinaryTreeNode<T>* rightChild;                           //该节点的右子节点（树）指针

public:
    BinaryTreeNode(const T& = T());                          //构造函数，初始化节点存储的数据
    ~BinaryTreeNode();                                       //析构函数，此类没有子节点链表帮我们析构
    BinaryTreeNode<T>& operator=(const BinaryTreeNode<T>&);  //运算符=的重载，实现深拷贝
    BinaryTreeNode(const BinaryTreeNode<T>&);                //拷贝构造，实现深拷贝

    T GetNodeData() const;                                   //获取该树节点存储的数据值
    bool IsRoot() const;                                     //该节点是否是根节点（树的发端）
    bool HasLeftChild() const;                               //该节点是否有左子节点
    bool HasRightChild() const;                              //该节点是否有右子节点
    bool IsLeaf() const;                                     //该节点是否是叶节点（树的末端）
    // int GetSize() const;                                     //获取以该节点及其所有后代的个数
    // int GetDepth() const;                                    //获取以该节点为根节点的树的深度
    int GetDegree() const;                                   //获取该节点的度，即子节点个数
    BinaryTreeNode<T>* GetParentPtr() const;                 //获取指向父节点的指针
    BinaryTreeNode<T>* GetLeftChildPtr() const;              //获取指向左子节点（树）的指针
    BinaryTreeNode<T>* GetRightChildPtr() const;             //获取指向右子节点（树）的指针
    // void PrintTree() const;                                  //完整打印以该节点为根节点的树

    void SetLeftChild(BinaryTreeNode<T>*);                   //以传入节点的方式设置左子节点（会覆盖）
    void SetLeftChild(T);                                    //以传入新元素的方式设置左子节点（会覆盖）
    void SetRightChild(BinaryTreeNode<T>*);                  //以传入节点的方式设置右子节点（会覆盖）
    void SetRightChild(T);                                   //以传入新元素的方式设置右子节点（会覆盖）
    void DelLeftChild();                                     //删除左子节点
    void DelRightChild();                                    //删除右子节点

protected:
    // void PrintTree(int) const;                               //依据传入深度打印出基于相应层级的树
};

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T & _data)
{
    nodeData = _data;
    //初始化父节点、左右子树的指针为空指针，只有在AddChild或DelChild的时候才会对这三者产生修改
    parentNode = nullptr;
    leftChild = nullptr;
    rightChild = nullptr;
}

template <typename T>
BinaryTreeNode<T>::~BinaryTreeNode()
{
    //先析构子节点，再析构自身
    DelLeftChild();
    DelRightChild();
}

template <typename T>
BinaryTreeNode<T>& BinaryTreeNode<T>::operator=(const BinaryTreeNode<T>& _obj)
{
    //防止自我赋值
    if (this == &_obj)
        return *this;

    //清除当前的子节点
    while (this->GetDegree() > 0)
    {
        DelLeftChild();
        DelRightChild();
    }

    //拷贝节点数据
    this->nodeData = _obj.GetNodeData();
    //不要拷贝等号右侧对象的父节点，也不要清空this的父节点，保持原有的就好
    // this->parentNode = nullptr;

    //复制传入节点的子节点
    BinaryTreeNode<T>* _left = _obj.GetLeftChildPtr();
    BinaryTreeNode<T>* _right = _obj.GetRightChildPtr();
    //如果是叶节点，那么就可以直接复制（注意不要用接收指针的SetXXChild函数重载版本，因其使用了赋值运算符的重载，会循环引用）
    if (_left->IsLeaf())
        SetLeftChild(_left->GetNodeData());
    //否则递归调用赋值运算符的重载（注意使用的是解引用，不然就是对指针的操作了）
    else
        *leftChild = *_left;
    //同样的操作对右子节点进行
    if (_right->IsLeaf())
        SetLeftChild(_left->GetNodeData());
    else
        *rightChild = *_right;

    //返回自身引用
    return *this;
}

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode<T>& _obj)
{
    //直接使用赋值运算符的重载
    *this = _obj;
}

template <typename T>
T BinaryTreeNode<T>::GetNodeData() const
{
    return nodeData;
}

template <typename T>
bool BinaryTreeNode<T>::IsRoot() const
{
    return (parentNode == nullptr);
}

template <typename T>
bool BinaryTreeNode<T>::HasLeftChild() const
{
    return (leftChild != nullptr);
}

template <typename T>
bool BinaryTreeNode<T>::HasRightChild() const
{
    return (rightChild != nullptr);
}

template <typename T>
bool BinaryTreeNode<T>::IsLeaf() const
{
    return (GetDegree() == 0);
}

// template <typename T>
// int BinaryTreeNode<T>::GetSize() const
// {
//     //将自身算进去
//     int _counter = 1;
//     //如果有子节点，那就需要加上子节点的节点数
//     if (!IsLeaf())
//     {
//         //遍历子节点，加上每个子节点的所拥节点数（递归思想）
//         for (int i = 0; i < GetDegree(); i++)
//         {
//             _counter += GetChildPtr(i)->GetSize();
//         }
//     }
//     return _counter;
// }

// template <typename T>
// int BinaryTreeNode<T>::GetDepth() const
// {
//     //计数器
//     int _counter = 0;
//     //若是叶节点，那么返回深度为0
//     if (IsLeaf())
//         return _counter;
//     else
//     {
//         //否则不是叶节点，那么就说明还有下一层，故给计数器递增
//         _counter++;
//         //用于存储子结点中最大的深度
//         int _maxDepth = 0;
//         //迭代器，用于遍历子节点
//         TreeNode<T>* _itr;
//         for (int i = 0; i < GetDegree(); i++)
//         {
//             _itr = GetChildPtr(i);
//             //递归的思想
//             _maxDepth = std::max(_maxDepth, _itr->GetDepth());
//         }
//         //给计数器加上子结点中的最大深度
//         _counter += _maxDepth;
//         return _counter;
//     }
// }

template <typename T>
int BinaryTreeNode<T>::GetDegree() const
{
    int _counter = 0;
    if (HasLeftChild())
        _counter++;
    if (HasRightChild())
        _counter++;
    return _counter;
}

template <typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::GetParentPtr() const
{
    return parentNode;
}

template <typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::GetLeftChildPtr() const
{
    return leftChild;
}

template <typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::GetRightChildPtr() const
{
    return rightChild;
}

// template <typename T>
// void BinaryTreeNode<T>::PrintTree() const
// {
//     //传入的初始深度为零，表示打印以此节点为根节点的整个树
//     this->PrintTree(0);
// }

template <typename T>
void BinaryTreeNode<T>::SetLeftChild(BinaryTreeNode<T>* _node)
{
    //将传入节点通过（赋值运算符已经过深拷贝重载）深拷贝到新的内存
    BinaryTreeNode<T> _new = *_node;

    if (!HasLeftChild())
    {
        //赋值运算符拷贝给左子节点（注意解引用获取leftChild的引用）
        *leftChild = _new;
    }
    else
    {
        delete leftChild;
        *leftChild = _new;
    }
}

template <typename T>
void BinaryTreeNode<T>::SetLeftChild(T _obj)
{
    //若无此位置的子节点，则直接新建，否则还要销毁原本位置上的节点
    if (!HasLeftChild())
    {
        //在堆区新建子节点
        BinaryTreeNode<T>* _new = new BinaryTreeNode<T>(_obj);
        //对子节点进行维护
        leftChild = _new;
        //注意对父节点进行维护
        leftChild->GetParentPtr() = this;
    }
    else
    {
        DelLeftChild();
        SetLeftChild(_obj);
    }
}

template <typename T>
void BinaryTreeNode<T>::SetRightChild(BinaryTreeNode<T>* _node)
{
    //将传入节点通过（赋值运算符已经过深拷贝重载）深拷贝到新的内存
    BinaryTreeNode<T> _new = *_node;

    if (!HasRightChild())
    {
        //赋值运算符拷贝给左子节点（注意解引用获取rightChild的引用）
        *rightChild = _new;
    }
    else
    {
        delete rightChild;
        *rightChild = _new;
    }
}

template <typename T>
void BinaryTreeNode<T>::SetRightChild(T _obj)
{
    //若无此位置的子节点，则直接新建，否则还要销毁原本位置上的节点
    if (!HasRightChild())
    {
        //在堆区新建子节点
        BinaryTreeNode<T>* _new = new BinaryTreeNode<T>(_obj);
        //对子节点进行维护
        rightChild = _new;
        //注意对父节点进行维护
        rightChild->GetParentPtr() = this;
    }
    else
    {
        DelRightChild();
        SetRightChild(_obj);
    }
}

template <typename T>
void BinaryTreeNode<T>::DelLeftChild()
{
    delete leftChild;
}

template <typename T>
void BinaryTreeNode<T>::DelRightChild()
{
    delete rightChild;
}

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
//     if (!IsLeaf())
//     {
//         //用于遍历子节点的迭代器
//         TreeNode<T>* _itr;
//         //最外层的循环，遍历第一层后代节点
//         for (int i = 0; i < this->GetDegree(); i++)
//         {
//             //更新迭代器指向
//             _itr = this->GetChildPtr(i);
//             //递归的方式进行打印，让子节点在下一层深度打印
//             _itr->PrintTree(_depth + 1);
//         }
//     }
// }

namespace Test_Binary_Tree_Node
{
    void TestBasicFunctions()
    {

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