#ifndef _BI_TREE_ITERATOR_HPP_
#define _BI_TREE_ITERATOR_HPP_

#include <iostream>

//X是二叉树指针，如BiTreeNode<T>*
template <typename X>
class BiTreeIterator
{
public:
    void TraversalPreOrder(X);   //前序遍历，自己--左子--右子
    void TraversalInOrder(X);    //中序遍历，左子--自己--右子
    void TraversalPostOrder(X);  //后序遍历，左子--右子--自己
};

template <typename X>
void BiTreeIterator<X>::TraversalPreOrder(X _node)
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
void BiTreeIterator<X>::TraversalInOrder(X _node)
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
void BiTreeIterator<X>::TraversalPostOrder(X _node)
{
    //防止无限循环
    if (_node == nullptr)
        return;
    //打印顺序：左子--右子--自己
    TraversalPostOrder(_node->GetLeftChildPtr());
    TraversalPostOrder(_node->GetRightChildPtr());
    std::cout << "<" << _node->GetNodeData() << ">";
}

namespace Test_Bi_Tree_Iterator
{
    void MainTest()
    {
        std::cout << "--------------------------------------------------\n";

        //初始化一个二叉树
        BiTreeNode<int> btn(111);
        btn.SetLeftChild(222);
        btn.SetRightChild(333);
        btn.GetLeftChildPtr()->SetLeftChild(444);
        btn.GetLeftChildPtr()->SetRightChild(555);
        btn.GetRightChildPtr()->SetLeftChild(666);
        btn.GetRightChildPtr()->SetRightChild(777);
        btn.GetLeftChildPtr()->GetLeftChildPtr()->SetLeftChild(888);
        btn.GetRightChildPtr()->GetLeftChildPtr()->SetLeftChild(999);
        std::cout << "**Print btn\n"; btn.PrintTree();
        //-[111]
        //        -L[222]
        //                -L[444]
        //                        -L[888]
        //                        -R[ ]
        //                -R[555]
        //        -R[333]
        //                -L[666]
        //                        -L[999]
        //                        -R[ ]
        //                -R[777]

        //初始化一个BiTreeNode<int>*类型二叉树的迭代器
        BiTreeIterator<BiTreeNode<int>*> itr;

        //PreOrder遍历，效果与深度优先遍历一致
        itr.TraversalPreOrder(&btn);
        std::cout << "\n";
        //<111><222><444><888><555><333><666><999><777>

        //InOrder遍历
        itr.TraversalInOrder(&btn);
        std::cout << "\n";
        //<888><444><222><555><111><999><666><333><777>

        //PostOrder遍历
        itr.TraversalPostOrder(&btn);
        std::cout << "\n";
        //<888><444><555><222><999><666><777><333><111>

        std::cout << "--------------------------------------------------\n";
    }
}

#endif