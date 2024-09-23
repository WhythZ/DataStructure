#ifndef _BINARY_TREE_NODE_HPP_
#define _BINARY_TREE_NODE_HPP_

#include <iostream>
//引入基类树节点类
#include "../02-Tree/01-TreeNode.hpp"

template <typename T>
class BinaryTreeNode :public TreeNode<T>
{
private:
    BinaryTreeNode<T>* leftSubNode;                 //左子节点指针
    BinaryTreeNode<T>* rightSubNode;                //右子节点指针
    
public:
    BinaryTreeNode<T>* GetLeftSubNodePtr() const;   //获取左子节点（即左子树的根节点）
    BinaryTreeNode<T>* GetRightSubNodePtr() const;  //获取右子节点（即右子树的根节点）

    void AddLeftSubNode(BinaryTreeNode<T>*);        //以节点指针形式添加左子节点（树）
    void AddLeftSubNode(T);                         //以值形式添加左子节点
    void AddRightSubNode(BinaryTreeNode<T>*);       //以节点指针形式添加右子节点（树）
    void AddRightSubNode(T);                        //以值形式添加右子节点
};

namespace Test_Binary_Tree_Node
{
    void MainTest()
    {
        std::cout << "--------------------------------------------------\n";

        //测试

        std::cout << "--------------------------------------------------\n";
    }
}

#endif