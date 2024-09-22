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
    T nodeData;                               //该节点存储的数据
    TreeNode<T>* parentNode;                  //该节点的父节点指针
    SingleLinkedList<TreeNode<T>> childList;  //该节点的子节点

public:
    //构造函数，初始化节点存储的数据以及该节点的父节点指针
    TreeNode(const T & = T(), TreeNode<T>* = nullptr);
    //拷贝构造，实现深拷贝
    TreeNode(const TreeNode<T>&);
    //运算符=的重载，实现深拷贝
    TreeNode<T>& operator=(const TreeNode<T>&);

    T GetNodeData() const;                    //获取该树节点存储的数据值
    bool IsRoot() const;                      //该节点是否是根节点（树的发端）
    bool IsLeaf() const;                      //该节点是否是叶节点（树的末端）
    int GetSize() const;                      //获取以该节点及其所有后代的个数
    int GetDepth() const;                     //获取以该节点为根节点的树的深度
    int GetDegree() const;                    //获取该节点的度，即子节点个数
    TreeNode<T>* GetParentPtr() const;        //获取指向父节点的指针
    TreeNode<T>* GetChildPtr(int) const;      //以索引获取指向某子节点的指针
    void PrintNeighbor() const;               //打印该节点自身及其相邻两层，共三层
    void PrintTree() const;                   //完整打印以该节点为根节点的树

    void AddChild(TreeNode<T>*);              //以传入节点的方式添加子节点
    void AddChild(T);                         //以传入新元素的方式添加子节点
    void DelChild(int);                       //通过索引删除子节点
    void DelChild(TreeNode<T>*);              //通过地址删除子节点

protected:
    void PrintTree(int) const;                //依据传入深度打印出基于相应层级的树
};

template <typename T>
TreeNode<T>::TreeNode(const T & _data, TreeNode<T> * _parent)
{
    nodeData = _data;
    parentNode = _parent;
}

template <typename T>
TreeNode<T>::TreeNode(const TreeNode<T>& _obj)
{
    //拷贝构造不继承被拷贝对象的父节点，不然会出很多问题
    this->parentNode = nullptr;
    this->nodeData = _obj.GetNodeData();

    //迭代器，遍历被传入节点的所有子节点，并将其一一附加到this节点上
    TreeNode<T>* _itr;
    for (int i = 0; i < _obj.GetDegree(); i++)
    {
        _itr = _obj.GetChildPtr(i);
        //AddChild函数是安全的深拷贝
        this->AddChild(_itr);
    }
}

template <typename T>
TreeNode<T>& TreeNode<T>::operator=(const TreeNode<T>& _obj)
{
    //防止自我赋值
    if (this == &_obj)
        return *this;

    //清除当前的子节点
    while (this->GetDegree() > 0)
    {
        this->DelChild(0);
    }

    //拷贝节点数据
    this->nodeData = _obj.GetNodeData();
    //保持父节点为空（即不拷贝等号右侧对象的父节点）
    this->parentNode = nullptr;

    //手动复制子节点，避免使用AddChild函数以避免循环依赖
    TreeNode<T>* _itr;
    for (int i = 0; i < _obj.GetDegree(); ++i)
    {
        _itr = _obj.GetChildPtr(i);
        //如果是叶节点，那便可以直接添加
        if (_itr->IsLeaf())
            this->childList.PushBack(TreeNode<T>(_itr->GetNodeData()));
        //如果有子节点，那就递归调用赋值重载运算符
        else
        {
            this->childList.PushBack(TreeNode<T>(T()));
            //解引用获取刚刚推送到链表末尾的值（TreeNode<T>类型的值）的引用，对其进行赋值（递归）
            *this->childList.GetElemPtr(this->GetDegree() - 1) = *_itr;
        }
    }

    //返回自身引用
    return *this;
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

template <typename T>
int TreeNode<T>::GetSize() const
{
    //将自身算进去
    int _counter = 1;

    //如果有子节点，那就需要加上子节点的节点数
    if (!IsLeaf())
    {
        //遍历子节点，加上每个子节点的所拥节点数（递归思想）
        for (int i = 0; i < GetDegree(); i++)
        {
            _counter += GetChildPtr(i)->GetSize();
        }
    }
    
    return _counter;
}

template <typename T>
int TreeNode<T>::GetDepth() const
{
    //计数器
    int _counter = 0;

    //若是叶节点，那么返回深度为0
    if (IsLeaf())
        return _counter;
    else
    {
        //否则不是叶节点，那么就说明还有下一层，故给计数器递增
        _counter++;

        //用于存储子结点中最大的深度
        int _maxDepth = 0;
        //迭代器，用于遍历子节点
        TreeNode<T>* _itr;
        for (int i = 0; i < GetDegree(); i++)
        {
            _itr = GetChildPtr(i);
            //递归的思想
            _maxDepth = std::max(_maxDepth, _itr->GetDepth());
        }

        //给计数器加上子结点中的最大深度
        _counter += _maxDepth;
        return _counter;
    }
}

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
void TreeNode<T>::PrintNeighbor() const
{
    //父节点的打印
    if (parentNode == nullptr)
        std::cout << "NULLPTR\n";
    else
        std::cout << "{" << parentNode->GetNodeData() << "}\n";

    //this节点的打印
    std::cout << "|\n";
    std::cout << "{" << this->GetNodeData() << "}\n";

    //子节点的打印
    if (!IsLeaf())
    {
        for (int i = 0; i < childList.GetLength(); i++)
        {
            std::cout << "|\t";
        }
        std::cout << "\n";

        for (int i = 0; i < childList.GetLength(); i++)
        {
            std::cout << "{" << this->GetChildPtr(i)->GetNodeData() << "}\t";
        }
        std::cout << "\n";
    }
}

template <typename T>
void TreeNode<T>::PrintTree() const
{
    //传入的初始深度为一，即以此节点为根节点打印整个树
    this->PrintTree(1);
}

template <typename T>
void TreeNode<T>::AddChild(TreeNode<T>* _node)
{
    //将传入节点通过深拷贝到新的内存，防止调用AddChild的节点与传入节点存在祖辈关系（会导致漏洞）
    TreeNode<T> _new = *_node;

    //将传入节点（不论其是否是根节点）的值（包装成新的TreeNode对象）添加到this节点的子节点列表
    AddChild(_new.GetNodeData());

    //记录刚被添加到子节点列表的新节点的地址
    TreeNode<T>* _newRoot = this->childList.GetElemPtr(childList.GetLength() - 1);

    //如果传入节点有子节点，将其加入刚被添加到this的子节点链表的那个子节点的子节点列表
    if (!_new.IsLeaf())
    {
        //迭代遍历传入的根节点的所有后代节点
        TreeNode<T>* _itr;
        for (int i = 0; i < _new.GetDegree(); i++)
        {
            _itr = _new.GetChildPtr(i);
            //递归调用此重载函数
            _newRoot->AddChild(_itr);
        }
    }
}

template <typename T>
void TreeNode<T>::AddChild(T _obj)
{
    //以传入数据构造节点，推送到子节点链表的末尾
    childList.PushBack(TreeNode<T>(_obj));
    //将链表末尾的新增节点的父节点设置为this节点
    childList.GetElemPtr(childList.GetLength() - 1)->parentNode = this;
}

template <typename T>
void TreeNode<T>::DelChild(int _idx)
{
    if (_idx < 0 || _idx >= childList.GetLength())
        throw std::invalid_argument("ERROR: Invalid Index When Calling {void TreeNode<T>::DelChild(int _idx)}");
    //在链表中删除该节点元素即可
    childList.Erase(_idx);
}

template <typename T>
void TreeNode<T>::DelChild(TreeNode<T>* _node)
{
    DelChild(childList.Find(_node));
}

template <typename T>
void TreeNode<T>::PrintTree(int _depth) const
{
    //根据传入的深度参数，得知当前节点处于多深，即得出打印时需要在前面打印几个横线
    for (int i = 0; i < _depth; i++)
    {
        std::cout << "--";
    }

    //打印节点本身
    std::cout << "[" << this->GetNodeData() << "]\n";

    //如果有后代，就以深度优先遍历所有后代
    if (!IsLeaf())
    {
        //用于遍历子节点的迭代器
        TreeNode<T>* _itr;
        //最外层的循环，遍历第一层后代节点
        for (int i = 0; i < this->GetDegree(); i++)
        {
            //更新迭代器指向
            _itr = this->GetChildPtr(i);

            //递归的方式进行打印，让子节点在下一层深度打印
            _itr->PrintTree(_depth + 1);
        }
    }
}

namespace Test_Tree_Node
{
    void TestSingleTreeNodeAndItsNeighbor()
    {
        //测试初始化
        TreeNode<int> tree(999);
        tree.PrintNeighbor();
        // NULLPTR
        // |
        // {999}

        //测试以值新增子节点
        tree.AddChild(111); std::cout << "**AddChild(111)\n";
        tree.AddChild(222); std::cout << "**AddChild(222)\n";
        tree.PrintNeighbor();
        // NULLPTR
        // |
        // {999}
        // |       |
        // {111}   {222}

        //测试以已有节点新增子节点，但是node333的地址不等于树中新增的对应节点的地址
        //因为这种方式是由SingleLinkedList将此节点PushBack到了链表内，是在堆区新开辟的内存地址
        TreeNode<int> node333(333);
        TreeNode<int> node444(444);
        tree.AddChild(&node333); std::cout << "**AddChild(node333)\n";
        tree.AddChild(&node444); std::cout << "**AddChild(node444)\n";
        tree.PrintNeighbor();
        // NULLPTR
        // |
        // {999}
        // |       |       |       |
        // {111}   {222}   {333}   {444}
        
        //测试以索引删除子节点
        tree.DelChild(0); std::cout << "**DelChild(0)\n";
        tree.PrintNeighbor();
        // NULLPTR
        // |
        // {999}
        // |       |       |
        // {222}   {333}   {444}

        //测试以传入子节点地址的方式删除该子节点
        TreeNode<int>* realNode333 = tree.GetChildPtr(1);
        tree.DelChild(realNode333); std::cout << "**DelChild(realNode333)\n";
        tree.PrintNeighbor();
        // NULLPTR
        // |
        // {999}
        // |       |
        // {222}   {444}
    }

    void TestMultipleNodesAsTree()
    {
        //初始化一个树
        TreeNode<int> smallTree(99);
        smallTree.AddChild(11);
        smallTree.GetChildPtr(0)->AddChild(33);
        smallTree.GetChildPtr(0)->GetChildPtr(0)->AddChild(66);
        smallTree.GetChildPtr(0)->AddChild(44);
        smallTree.AddChild(22);
        smallTree.GetChildPtr(1)->AddChild(55);

        //测试获取节点总数的函数
        std::cout << "##smallTree.GetSize(): " << smallTree.GetSize() << "\n";
        //##smallTree.GetSize(): 7

        //将smallTree附加到别的树上
        TreeNode<int> bigTree(77);
        bigTree.AddChild(&smallTree);
        bigTree.GetChildPtr(0)->AddChild(&smallTree);
        std::cout << "##bigTree.GetSize(): " << bigTree.GetSize() << "\n";
        //##bigTree.GetSize(): 15

        //测试深度的获取
        std::cout << "##smallTree.GetDepth(): " << smallTree.GetDepth() << "\n";
        //##smallTree.GetDepth(): 3
        std::cout << "##bigTree.GetDepth(): " << bigTree.GetDepth() << "\n";
        //##bigTree.GetDepth(): 5

        //测试整颗树的打印
        std::cout << "##Print smallTree:\n"; smallTree.PrintTree();
        //##Print smallTree:
        //--[99]
        //----[11]
        //------[33]
        //--------[66]
        //------[44]
        //----[22]
        //------[55]
        std::cout << "##Print bigTree:\n"; bigTree.PrintTree();
        //##Print bigTree:
        //--[77]
        //----[99]
        //------[11]
        //--------[33]
        //----------[66]
        //--------[44]
        //------[22]
        //--------[55]
        //------[99]
        //--------[11]
        //----------[33]
        //------------[66]
        //----------[44]
        //--------[22]
        //----------[55]

        //程序健壮性：运行下面的代码（近亲结婚产生后代）不会导致错误
        smallTree.AddChild(&smallTree);
        smallTree.AddChild(smallTree.GetChildPtr(0));
    }

    void TestDeepCopy()
    {
        //初始化一个树
        TreeNode<int> tree(99);
        tree.AddChild(11);
        tree.AddChild(22);
        tree.GetChildPtr(0)->AddChild(33);
        tree.GetChildPtr(0)->AddChild(44);
        tree.GetChildPtr(1)->AddChild(55);
        tree.GetChildPtr(0)->GetChildPtr(0)->AddChild(66);
        std::cout << "##Print tree:\n"; tree.PrintTree();
        //##Print tree:
        //--[99]
        //----[11]
        //------[33]
        //--------[66]
        //------[44]
        //----[22]
        //------[55]
        
        //测试拷贝构造
        TreeNode<int> copy1(tree);
        std::cout << "##Print copy1:\n"; copy1.PrintTree();
        //##Print copy1:
        //--[99]
        //----[11]
        //------[33]
        //--------[66]
        //------[44]
        //----[22]
        //------[55]

        //测试赋值运算符初始化
        copy1.DelChild(1);
        TreeNode<int> copy2 = copy1;
        std::cout << "##Print copy2:\n"; copy2.PrintTree();
        //##Print copy2:
        //--[99]
        //----[11]
        //------[33]
        //--------[66]
        //------[44]
    }

    void MainTest()
    {
        std::cout << "--------------------------------------------------\n";

        std::cout << "--------------------TestArea01--------------------\n";
        TestSingleTreeNodeAndItsNeighbor();
        std::cout << "--------------------TestArea02--------------------\n";
        TestMultipleNodesAsTree();
        std::cout << "--------------------TestArea03--------------------\n";
        TestDeepCopy();
        
        std::cout << "--------------------------------------------------\n";
    }
}

#endif