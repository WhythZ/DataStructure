#ifndef _TREE_ITERATOR_HPP_
#define _TREE_ITERATOR_HPP_

#include <iostream>
//引入队列与栈分别用于BFS与DFS的搜索遍历
#include "../01-LinearList/07-SQueue.hpp"
#include "../01-LinearList/05-SStack.hpp"
//引入普通的树节点类与二叉树节点类，用于测试
#include "../02-Tree/01-TreeNode.hpp"
#include "../02-Tree/03-BinaryTreeNode.hpp"

//X指的是树节点指针，比如TreeNode<T>*，或BinaryTreeNode<T>*
template <typename X>
class TreeIterator
{
private:
    X root;                         //被遍历的树对象的根节点
    SQueue<X> queue;                //队列，存储以BFS遍历的树节点指针结果
    SStack<X> stack;                //栈，存储以DFS遍历的树节点指针结果

public:
    TreeIterator(X);                //构造函数初始化被遍历的对象
    void TraversalBFS();            //以BFS遍历打印树的所有节点
    void TraversalDFS();            //以DFS遍历打印树的所有节点

private:
    void TraversalBFS(X);           //以BFS遍历打印传入节点的所有后代节点
    void TraversalDFS(X, int = 0);  //以DFS遍历打印传入节点的所有后代节点
};

template <typename X>
TreeIterator<X>::TreeIterator(X _treeRootNode)
{
    //每个树迭代器只为一个树服务
    root = _treeRootNode;
    //不论是队列还是栈，都要先将根节点添加进去
    queue.Push(_treeRootNode);
    stack.Push(_treeRootNode);
}

template <typename X>
void TreeIterator<X>::TraversalBFS()
{
    //因为根节点的入队是在构造函数进行的，所以只有此处可以打印此信息
    std::cout << "<" << queue.GetFront()->GetNodeData() << ">";
    //取出根节点进行递归遍历
    this->TraversalBFS(root);
    //待上述遍历打印完成后，换行
    std::cout << "\n";
}

template <typename X>
void TreeIterator<X>::TraversalDFS()
{
    //注意此处使用的是栈
    std::cout << "<" << stack.GetTop()->GetNodeData() << ">";
    //取出根节点进行递归遍历，默认从根节点的第一个子节点开始搜索
    this->TraversalDFS(root, 0);
    std::cout << "\n";
}

template <typename X>
void TreeIterator<X>::TraversalBFS(X _node)
{
    //调用此函数就说明队首节点被取出了，故而使用Pop函数将其删除（删除的实际上就是传入节点）
    std::cout << "</" << queue.GetFront()->GetNodeData() << ">";
    queue.Pop();

    //遍历传入节点的子节点
    for (int i = 0; i < _node->GetDegree(); i++)
    {
        //将子节点入队
        std::cout << "<" << _node->GetChildPtr(i)->GetNodeData() << ">";
        queue.Push(_node->GetChildPtr(i));
    }

    //然后将队首节点出队（记得使用Pop删除），递归执行此遍历函数
    if (!queue.IsEmpty())
    {
        TraversalBFS(queue.GetFront());
    }
}

template <typename X>
void TreeIterator<X>::TraversalDFS(X _node, int _idx)
{
    //如果刚刚取出的节点为叶节点，或索引数超出了最大索引范围，则应当折返回上一个分支处
    if (_node->IsLeaf() || _idx > (_node->GetDegree() - 1))
    {
        //将栈顶节点（其实就是传入的节点）出栈
        std::cout << "</" << stack.GetTop()->GetNodeData() << ">";
        stack.Pop();

        //防止无限循环
        if (stack.IsEmpty())
            return;

        //记录这个叶节点的父节点，不能用_node->GetParentPtr()获取，因为调用TraversalDFS()重载函数的节点不一定是根节点（只是把它当成根节点来打印而已）
        X _parent = stack.GetTop();
        //获取该父节点的下一个子节点分支的索引
        int _nextBranchIdx = _parent->FindChildIdx(_node) + 1;
        //然后继续递归搜索父节点
        TraversalDFS(_parent, _nextBranchIdx);
    }
    else
    {            
        //将传入节点的索引为_idx的子节点入栈
        X _next = _node->GetChildPtr(_idx);
        std::cout << "<" << _next->GetNodeData() << ">";
        stack.Push(_next);

        //然后继续递归遍历，默认从0索引的子节点开始搜索
        TraversalDFS(_next, 0);
    }
}

namespace Test_Tree_Iterator
{
    void TestTreeNodeTraversal()
    {
        //创建用于测试的树
        TreeNode<int> tree(99);
        tree.AddChild(11);
        tree.AddChild(22);
        tree.GetChildPtr(0)->AddChild(33);
        tree.GetChildPtr(0)->AddChild(44);
        tree.GetChildPtr(1)->AddChild(55);
        tree.GetChildPtr(0)->GetChildPtr(0)->AddChild(66);
        std::cout << "**Print tree:\n"; tree.PrintTree();
        //-[99]
        //        -[11]
        //                -[33]
        //                        -[66]
        //                -[44]
        //        -[22]
        //                -[55]

        //测试广度优先遍历，遍历的对象类型是TreeNode<int>*
        TreeIterator<TreeNode<int>*> itr1(&tree);
        std::cout << "**Traverse &tree By BFS\n"; itr1.TraversalBFS();
        //<99></99><11><22></11><33><44></22><55></33><66></44></55></66>

        //测试深度优先遍历
        std::cout << "**Traverse &tree By DFS\n"; itr1.TraversalDFS();
        //<99><11><33><66></66></33><44></44></11><22><55></55></22></99>

        //测试深度优先遍历的特殊情况（即遍历对象有父节点，我们应当忽略这个父节点）
        TreeIterator<TreeNode<int>*> itr2(tree.GetChildPtr(0));
        std::cout << "**Traverse tree.GetChildPtr(0) By DFS\n"; itr2.TraversalDFS();
        //<11><33><66></66></33><44></44></11>
    }

    void TestBinaryTreeNodeTraversal()
    {
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

        //创建BinaryTreeNode<int>*的迭代器
        TreeIterator<BinaryTreeNode<int>*> itr(&btn);

        //测试广度优先遍历
        itr.TraversalBFS();
        //<111></111><222><333></222><444><111></333><555></444></111><222><333></555></222><444></333><555></444></555>

        //测试深度优先遍历
        itr.TraversalDFS();
        //<111><222><444></444><111><222><444></444></222><333><555></555></333></111></222><333><555></555></333></111>
    }

    void MainTest()
    {
        std::cout << "--------------------------------------------------\n";

        std::cout << "--------------------TestArea01--------------------\n";
        TestTreeNodeTraversal();
        std::cout << "--------------------TestArea02--------------------\n";
        TestBinaryTreeNodeTraversal();
        
        std::cout << "--------------------------------------------------\n";
    }
}

#endif