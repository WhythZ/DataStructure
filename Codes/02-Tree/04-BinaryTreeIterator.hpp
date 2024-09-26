#ifndef _BINARY_TREE_ITERATOR_HPP_
#define _BINARY_TREE_ITERATOR_HPP_

#include <iostream>

//X是二叉树指针，如BinaryTreeNode<T>*
template <typename X>
class BinaryTreeIterator
{
public:
    void TraversalPreOrder(X);   //
    void TraversalInOrder(X);    //
    void TraversalPostOrder(X);  //
};

template <typename X>
void BinaryTreeIterator<X>::TraversalPreOrder(X _node)
{
    //防止无限循环
    if (_node == nullptr)
        return;
    //打印顺序：自己--左子--右子
    std::cout << "<" << _node->GetNodeData() << ">";
    TraversalPreOrder(_node->GetLeftChildPtr());
    TraversalPreOrder(_node->GetRightChildPtr());
}

template <typename X>
void BinaryTreeIterator<X>::TraversalInOrder(X _node)
{
    //防止无限循环
    if (_node == nullptr)
        return;
    //打印顺序：左子--自己--右子
    TraversalInOrder(_node->GetLeftChildPtr());
    std::cout << "<" << _node->GetNodeData() << ">";
    TraversalInOrder(_node->GetRightChildPtr());
}

template <typename X>
void BinaryTreeIterator<X>::TraversalPostOrder(X _node)
{
    //防止无限循环
    if (_node == nullptr)
        return;
    //打印顺序：左子--右子--自己
    TraversalPreOrder(_node->GetLeftChildPtr());
    TraversalPreOrder(_node->GetRightChildPtr());
    std::cout << "<" << _node->GetNodeData() << ">";
}

namespace Test_Binary_Tree_Iterator
{
    void MainTest()
    {
        std::cout << "--------------------------------------------------\n";

        //初始化一个二叉树
        BinaryTreeNode<int> btn(111);
        BinaryTreeNode<int> temp1(222);
        BinaryTreeNode<int> temp2(555);
        btn.SetLeftChild(&temp1);
        btn.SetRightChild(333);
        btn.GetLeftChildPtr()->SetLeftChild(444);
        btn.GetRightChildPtr()->SetRightChild(&temp2);
        btn.GetLeftChildPtr()->SetRightChild(&btn);
        std::cout << "**Print btn\n"; btn.PrintTree();
        //-[111]
        //        -L[222]
        //                -L[444]
        //                -R[111]
        //                        -L[222]
        //                                -L[444]
        //                                -R[ ]
        //                        -R[333]
        //                                -L[ ]
        //                                -R[555]
        //        -R[333]
        //                -L[ ]
        //                -R[555]
        
        //初始化一个BinaryTreeNode<int>*类型二叉树的迭代器
        BinaryTreeIterator<BinaryTreeNode<int>*> itr;

        //PreOrder遍历，效果与深度优先遍历一致
        itr.TraversalPreOrder(&btn);
        std::cout << "\n";
        //<111><222><444><111><222><444><333><555><333><555>

        //InOrder遍历，
        itr.TraversalInOrder(&btn);
        std::cout << "\n";
        //<444><222><444><222><111><333><555><111><333><555>

        //PostOrder遍历
        itr.TraversalPostOrder(&btn);
        std::cout << "\n";
        //<222><444><111><222><444><333><555><333><555><111>

        std::cout << "--------------------------------------------------\n";
    }
}

#endif