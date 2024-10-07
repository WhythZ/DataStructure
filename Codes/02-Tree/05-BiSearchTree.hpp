#ifndef _BI_SEARCH_TREE_HPP_
#define _BI_SEARCH_TREE_HPP_

#include <iostream>
//引入二叉树节点类
#include "../02-Tree/03-BiTreeNode.hpp"

//二叉搜索树类，使用组合而非继承的方法包装着一个二叉树节点，不支持存储相同数据的节点
template <typename T>
class BiSearchTree
{
private:
    BiTreeNode<T>* root;                   //维护一个二叉树节点内核

public:
    BiSearchTree();                        //构造函数，无=或构造的重载函数
    ~BiSearchTree();                       //析构函数，清空搜索树

    bool IsEmpty() const;                  //判断搜索树是否为空
    int GetSize() const;                   //获取树的节点数
    void PrintTree() const;                //打印整个搜索树
    T FindMin() const;                     //返回存储的最小值
    T FindMax() const;                     //返回存储的最大值
    // T FindFormer(const T&) const;          //寻找树中比传入值小的相邻值
    // T FindLatter(const T&) const;          //寻找树中比传入值大的相邻值
    T FindByIdx(int) const;                //以索引k获取树中从小到大排在第(k+1)位的值
    bool Contains(const T&) const;         //查找是否存在某个节点

    void Insert(const T&);                 //直接将新的节点插入正确位置
    void Erase(const T&);                  //以值删除某个数据节点
    void MakeEmpty();                      //清空搜索树

private:
    BiTreeNode<T>* FindMinPtr(BiTreeNode<T>*) const;
    BiTreeNode<T>* FindMaxPtr(BiTreeNode<T>*) const;
    // T FindFormer(const T&, BiTreeNode<T>*) const;
    // T FindLatter(const T&, BiTreeNode<T>*) const;
    T FindByIdx(int, BiTreeNode<T>*) const;
    bool Contains(const T&, BiTreeNode<T>*) const;

    void Insert(const T&, BiTreeNode<T>*);
    void Erase(const T&, BiTreeNode<T>*);
    void MakeEmpty(BiTreeNode<T>*);
};

template <typename T>
BiSearchTree<T>::BiSearchTree()
{
    root = nullptr;
}

template <typename T>
BiSearchTree<T>::~BiSearchTree()
{
    MakeEmpty();
}

template <typename T>
bool BiSearchTree<T>::IsEmpty() const
{
    //只要内核为空，那么这个搜索树就为空
    return (root == nullptr);
}

template <typename T>
int BiSearchTree<T>::GetSize() const
{
    return root->GetSize();
}

template <typename T>
void BiSearchTree<T>::PrintTree() const
{
    //健壮性
    if (IsEmpty())
        return;
    root->PrintTree();
}

template <typename T>
T BiSearchTree<T>::FindMin() const
{
    if (IsEmpty())
        throw std::invalid_argument("ERROR: Tree Is Empty {T BiSearchTree<T>::FindMin() const}");

    //从自身的根节点开始调用递归搜索
    BiTreeNode<T>* _node = FindMinPtr(root);

    //如果返回空指针，则说明root没有左子节点，root存储的就是最小值
    if (_node == nullptr)
        return root->GetNodeData();
    //反之则最小值是FindMinPtr返回的那个节点的值
    else
        return _node->GetNodeData();
}

template <typename T>
T BiSearchTree<T>::FindMax() const
{
    if (IsEmpty())
        throw std::invalid_argument("ERROR: Tree Is Empty {T BiSearchTree<T>::FindMax() const}");
        
    //从自身的根节点开始调用递归搜索
    BiTreeNode<T>* _node = FindMaxPtr(root);

    //如果返回空指针，则说明root没有右子节点，root存储的就是最大值
    if (_node == nullptr)
        return root->GetNodeData();
    //反之则最大值是FindMaxPtr返回的那个节点的值
    else
        return _node->GetNodeData();
}

// template <typename T>
// T BiSearchTree<T>::FindFormer(const T& _obj) const
// {
//     return FindFormer(_obj, root);
// }

// template <typename T>
// T BiSearchTree<T>::FindLatter(const T& _obj) const
// {
//     return FindLatter(_obj, root);
// }

template <typename T>
T BiSearchTree<T>::FindByIdx(int _idx) const
{
    return FindByIdx(_idx, root);
}

template <typename T>
bool BiSearchTree<T>::Contains(const T& _obj) const
{
    //从自身内核二叉树节点开始搜索
    return Contains(_obj, root);
}

template <typename T>
void BiSearchTree<T>::Insert(const T& _obj)
{
    Insert(_obj, root);
}

template <typename T>
void BiSearchTree<T>::Erase(const T& _obj)
{
    //从根节点开始搜索被删除的元素
    Erase(_obj, root);
}

template <typename T>
void BiSearchTree<T>::MakeEmpty()
{
    //清空内核节点
    MakeEmpty(root);
    //置空根节点
    root = nullptr;
}

template <typename T>
BiTreeNode<T>* BiSearchTree<T>::FindMinPtr(BiTreeNode<T>* _btn) const
{
    //若传入节点为空，则返回空指针
    if (_btn == nullptr)
        return nullptr;
    //若传入节点无左子节点，则根据搜索树规则，自身存储的就是最小的数据
    if (_btn->GetLeftChildPtr() == nullptr)
        return _btn;
    //若有左子节点，则递归左子节点的FindMin函数
    else
        return FindMinPtr(_btn->GetLeftChildPtr());
}

template <typename T>
BiTreeNode<T>* BiSearchTree<T>::FindMaxPtr(BiTreeNode<T>* _btn) const
{
    //若传入节点为空，则返回空指针
    if (_btn == nullptr)
        return nullptr;
    
    // //若传入节点无右子节点，则根据搜索树规则，自身存储的就是最小的数据
    // if (_btn->GetRightChildPtr() == nullptr)
    //     return _btn;
    // //若有右子节点，则递归右子节点的FindMin函数
    // else
    //     return FindMaxPtr(_btn->GetRightChildPtr());

    //这里提供另一种方法思路
    while (_btn->GetRightChildPtr() != nullptr)
    {
        //不断将_btn赋值为自己的右子节点，直到自己的的右子节点为空
        _btn = _btn->GetRightChildPtr();
    }
    //那么此时自己就是最右侧的节点，即值最大的节点
    return _btn;
}

// template <typename T>
// T BiSearchTree<T>::FindFormer(const T& _obj, BiTreeNode<T>* _btn) const
// {
// }

// template <typename T>
// T BiSearchTree<T>::FindLatter(const T& _obj, BiTreeNode<T>* _btn) const
// {
// }

template <typename T>
T BiSearchTree<T>::FindByIdx(int _idx, BiTreeNode<T>* _btn) const
{
    //排除空指针
    if (_btn == nullptr)
        throw std::invalid_argument("ERROR: Null Pointer {T BiSearchTree<T>::FindByIdx(int _idx, BiTreeNode<T>* _btn) const}");
    //排除非法索引
    else if (_idx < 0 || _idx >= _btn->GetSize())
        throw std::invalid_argument("ERROR: Invalid Index {T BiSearchTree<T>::FindByIdx(int _idx, BiTreeNode<T>* _btn) const}");

    //存储传入节点的左子节点的体积
    int _leftSize = 0;
    if (_btn->HasLeftChild())
        _leftSize = _btn->GetLeftChildPtr()->GetSize();

    //进行索引，原理解析参考笔记
    if (_idx == _leftSize)
        return _btn->GetNodeData();
    else if (_idx < _leftSize)
        return FindByIdx(_idx, _btn->GetLeftChildPtr());
    else
        return FindByIdx(_idx - _leftSize - 1, _btn->GetRightChildPtr());
}

template <typename T>
bool BiSearchTree<T>::Contains(const T& _val, BiTreeNode<T>* _btn) const
{
    //如果传入节点为空节点，则说明找完了整棵树都不存在存储着传入值的节点
    if (_btn == nullptr)
        return 0;

    //如果目标值等于传入节点的值，则直接确定该树存在该值
    if (_val == _btn->GetNodeData())
        return 1;
    //如果小于，则递归搜索左子节点
    if (_val < _btn->GetNodeData())
        return Contains(_val, _btn->GetLeftChildPtr());
    //如果大于，则递归搜索右子节点
    else
        return Contains(_val, _btn->GetRightChildPtr());
}

template <typename T>
void BiSearchTree<T>::Insert(const T& _obj, BiTreeNode<T>* _btn)
{
    //如果是空二叉树则用传入值初始化内核节点（意味着该搜索树将被插入第一个值）
    if (_btn == nullptr)
    {
        root = new BiTreeNode<T>(_obj);
        return;
    }

    //若是值相等，则直接结束，我不想让二叉搜索树中有相等的值（除非有需求要求我必须这么做）
    if (_obj == _btn->GetNodeData())
        return;
    if (_obj < _btn->GetNodeData())
    {
        //如果左子节点为空，则说明就该把新节点插在这里
        if (_btn->GetLeftChildPtr() == nullptr)
            _btn->SetLeftChild(_obj);
        //否则继续递归
        else
            Insert(_obj, _btn->GetLeftChildPtr());
    }
    if (_obj > _btn->GetNodeData())
    {
        if (_btn->GetRightChildPtr() == nullptr)
            _btn->SetRightChild(_obj);
        else
            Insert(_obj, _btn->GetRightChildPtr());
    }
}

template <typename T>
void BiSearchTree<T>::Erase(const T& _obj, BiTreeNode<T>* _btn)
{
    //要删除的是空指针，说明要删除的对象不存在
    if (_btn == nullptr)
        return;
    //若是小于/大于，则从传入节点的左/右子树继续搜寻
    if (_obj < _btn->GetNodeData())
        Erase(_obj, _btn->GetLeftChildPtr());
    else if (_obj > _btn->GetNodeData())
        Erase(_obj, _btn->GetRightChildPtr());
    //否则就说明二者相等，即需要被删除的对象就是传入节点
    else
    {
        //记录传入节点的父节点以待使用
        BiTreeNode<T>* _parent = _btn->GetParentPtr();

        //若是叶节点就好说，直接删除
        if (_btn->IsLeaf())
        {
            //若是根节点，则无需考虑父节点
            if (_parent == nullptr)
            {
                //直接清空
                root = nullptr;
                return;
            }
            //否则就要考虑父节点
            if (_parent->GetLeftChildPtr() == _btn)
                _parent->DelLeftChild();
            else
                _parent->DelRightChild();
        }
        //若是有一个子节点的节点
        else if (_btn->GetDegree() == 1)
        {
            //若是根节点
            if (_parent == nullptr)
            {
                if (_btn->HasLeftChild())
                    _btn = _btn->GetLeftChildPtr();
                else
                    _btn = _btn->GetRightChildPtr();
                //直接结束
                return;
            }
            //若是内部节点
            if (_parent->GetLeftChildPtr() == _btn)
            {
                if (_btn->HasLeftChild())
                    _parent->SetLeftChild(_btn->GetLeftChildPtr());
                else
                    _parent->SetLeftChild(_btn->GetRightChildPtr());
            }
            else
            {
                if (_btn->HasLeftChild())
                    _parent->SetRightChild(_btn->GetLeftChildPtr());
                else
                    _parent->SetRightChild(_btn->GetRightChildPtr());
            }
        }
        //若是有两个子节点的内部节点
        else
        {
            //获取_btn右子树的最小值所在的节点
            BiTreeNode<T>* _node = FindMinPtr(_btn->GetRightChildPtr());
            //获取_btn右子树的最小值
            T _min = _node->GetNodeData();
            //递归调用此方法删除节点
            Erase(_min, _btn);
            //将_btn的值替换为_min
            _btn->SetNodeData(_min);
        }
    }
}

template <typename T>
void BiSearchTree<T>::MakeEmpty(BiTreeNode<T>* _btn)
{
    //如果传入对象为空，则结束函数即可，否则递归调用清空函数
    if (_btn == nullptr)
        return;
    else
    {
        //清空其左右子树
        MakeEmpty(_btn->GetLeftChildPtr());
        MakeEmpty(_btn->GetRightChildPtr());
        //此处无需销毁_btn的内存，其父节点被销毁时也会销毁自己的
    }
    //将传入节点的孩子删除
    _btn->DelLeftChild();
    _btn->DelRightChild();
}

namespace Test_Bi_Search_Tree
{
    void TestTreeBuild()
    {
        //测试构造函数
        BiSearchTree<int> bst;

        //测试添加新元素，第一个被添加到搜索树的值将作为根节点值
        bst.Insert(5);
        bst.Insert(5);
        bst.Insert(2);
        bst.Insert(21);
        bst.Insert(1);
        bst.Insert(9);
        bst.Insert(4);
        bst.Insert(6);
        bst.Insert(7);
        bst.Insert(17);
        bst.Insert(8);
        bst.Insert(14);
        bst.Insert(23);
        bst.Insert(10);
        bst.Insert(15);
        bst.Insert(12);
        std::cout << "**bst.PrintTree()\n"; bst.PrintTree();
        //-[5]
        //        -L[2]
        //                -L[1]
        //                -R[4]
        //        -R[21]
        //                -L[9]
        //                        -L[6]
        //                                -L[ ]
        //                                -R[7]
        //                                        -L[ ]
        //                                        -R[8]
        //                        -R[17]
        //                                -L[14]
        //                                        -L[10]
        //                                                -L[ ]
        //                                                -R[12]
        //                                        -R[15]
        //                                -R[ ]
        //                -R[23]

        //测试叶节点值的删除
        std::cout << "**bst.Erase(12)\n"; bst.Erase(12);
        std::cout << "**bst.PrintTree()\n"; bst.PrintTree();
        // -[5]
        //         -L[2]
        //                 -L[1]
        //                 -R[4]
        //         -R[21]
        //                 -L[9]
        //                         -L[6]
        //                                 -L[ ]
        //                                 -R[7]
        //                                         -L[ ]
        //                                         -R[8]
        //                         -R[17]
        //                                 -L[14]
        //                                         -L[10]
        //                                         -R[15]
        //                                 -R[ ]
        //                 -R[23]
        
        //测试有一个子节点的内部节点的删除
        std::cout << "**bst.Erase(6)\n"; bst.Erase(6);
        std::cout << "**bst.PrintTree()\n"; bst.PrintTree();
        // -[5]
        //         -L[2]
        //                 -L[1]
        //                 -R[4]
        //         -R[21]
        //                 -L[9]
        //                         -L[7]
        //                                 -L[ ]
        //                                 -R[8]
        //                         -R[17]
        //                                 -L[14]
        //                                         -L[10]
        //                                         -R[15]
        //                                 -R[ ]
        //                 -R[23]
        
        //测试有两个子节点的内部节点的删除
        std::cout << "**bst.Erase(9)\n"; bst.Erase(9);
        std::cout << "**bst.PrintTree()\n"; bst.PrintTree();
        //-[5]
        //        -L[2]
        //                -L[1]
        //                -R[4]
        //        -R[21]
        //                -L[10]
        //                        -L[7]
        //                                -L[ ]
        //                                -R[8]
        //                        -R[17]
        //                                -L[14]
        //                                        -L[ ]
        //                                        -R[15]
        //                                -R[ ]
        //                -R[23]

        //测试根节点的删除
        std::cout << "**bst.Erase(5)\n"; bst.Erase(5);
        std::cout << "**bst.PrintTree()\n"; bst.PrintTree();
        //-[7]
        //        -L[2]
        //                -L[1]
        //                -R[4]
        //        -R[21]
        //                -L[10]
        //                        -L[8]
        //                        -R[17]
        //                                -L[14]
        //                                        -L[ ]
        //                                        -R[15]
        //                                -R[ ]
        //                -R[23]

        //测试体积获取
        std::cout << "##bst.GetSize(): " << bst.GetSize() << "\n";\
        //##bst.GetSize(): 11

        //测试清空
        std::cout << "**bst.MakeEmpty()\n"; bst.MakeEmpty();
        std::cout << "##bst.IsEmpty(): " << bst.IsEmpty() << "\n";
        //##bst.IsEmpty(): 1
    }

    void TestFinding()
    {
        //测试构造函数
        BiSearchTree<int> bst;

        //测试添加新元素，第一个被添加到搜索树的值将作为根节点值
        bst.Insert(5);
        bst.Insert(5);
        bst.Insert(2);
        bst.Insert(21);
        bst.Insert(1);
        bst.Insert(9);
        bst.Insert(4);
        bst.Insert(6);
        bst.Insert(7);
        bst.Insert(17);
        bst.Insert(8);
        bst.Insert(14);
        bst.Insert(23);
        bst.Insert(10);
        bst.Insert(15);
        bst.Insert(12);
        std::cout << "**bst.PrintTree()\n"; bst.PrintTree();
        //-[5]
        //        -L[2]
        //                -L[1]
        //                -R[4]
        //        -R[21]
        //                -L[9]
        //                        -L[6]
        //                                -L[ ]
        //                                -R[7]
        //                                        -L[ ]
        //                                        -R[8]
        //                        -R[17]
        //                                -L[14]
        //                                        -L[10]
        //                                                -L[ ]
        //                                                -R[12]
        //                                        -R[15]
        //                                -R[ ]
        //                -R[23]

        //测试极值查找、存在性判断
        std::cout << "##bst.FindMin(): " << bst.FindMin() << "\n";
        //##bst.FindMin(): 1
        std::cout << "##bst.FindMax(): " << bst.FindMax() << "\n";
        //##bst.FindMax(): 23
        std::cout << "##bst.Contains(14): " << bst.Contains(14) << "\n";
        //##bst.Contains(14): 1
        std::cout << "##bst.Contains(99): " << bst.Contains(99) << "\n";
        //##bst.Contains(99): 0

        //测试中间值查找
        std::cout << "##bst.FindByIdx(1): " << bst.FindByIdx(1) << "\n";
        //##bst.FindByIdx(1): 2
        std::cout << "##bst.FindByIdx(3): " << bst.FindByIdx(3) << "\n";
        //##bst.FindByIdx(3): 5
        std::cout << "##bst.FindByIdx(7): " << bst.FindByIdx(7) << "\n";
        //##bst.FindByIdx(7): 9

        // //测试某个值的前后相邻值的查找
        // std::cout << "##bst.FindFormer(5): " << bst.FindFormer(5) << "\n";
        // //##bst.FindFormer(5): 
        // std::cout << "##bst.FindLatter(5): " << bst.FindLatter(5) << "\n";
        // //##bst.FindLatter(5): 
    }

    void MainTest()
    {
        std::cout << "--------------------------------------------------\n";

        std::cout << "--------------------TestArea01--------------------\n";
        TestTreeBuild();
        std::cout << "--------------------TestArea02--------------------\n";
        TestFinding();

        std::cout << "--------------------------------------------------\n";
    }
}

#endif