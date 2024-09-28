#ifndef _BINARY_TREE_NODE_HPP_
#define _BINARY_TREE_NODE_HPP_

#include <iostream>

//二叉树节点类
template <typename T>
class BinaryTreeNode
{
protected:
    T nodeData;                                  //该节点存储的数据
    BinaryTreeNode<T>* parentNode;               //该节点的父节点指针
    BinaryTreeNode<T>* leftChild;                //该节点的左子节点（树）指针
    BinaryTreeNode<T>* rightChild;               //该节点的右子节点（树）指针

public:
    //构造函数，初始化节点存储的数据
    BinaryTreeNode(const T & = T());
    //析构函数，此类没有子节点链表帮我们析构
    ~BinaryTreeNode();
    //运算符=的重载，实现深拷贝
    BinaryTreeNode<T>& operator=(const BinaryTreeNode<T>&);
    //拷贝构造，实现深拷贝
    BinaryTreeNode(const BinaryTreeNode<T>&);

    T GetNodeData() const;                       //获取该树节点存储的数据值
    bool IsRoot() const;                         //该节点是否是根节点（树的发端）
    bool HasLeftChild() const;                   //该节点是否有左子节点
    bool HasRightChild() const;                  //该节点是否有右子节点
    bool IsLeaf() const;                         //该节点是否是叶节点（树的末端）
    int GetSize() const;                         //获取以该节点及其所有后代的个数
    int GetDepth() const;                        //获取以该节点为根节点的树的深度
    int GetDegree() const;                       //获取该节点的度，即子节点个数
    BinaryTreeNode<T>* GetParentPtr() const;     //获取指向父节点的指针
    BinaryTreeNode<T>* GetLeftChildPtr() const;  //获取指向左子节点（树）的指针
    BinaryTreeNode<T>* GetRightChildPtr() const; //获取指向右子节点（树）的指针
    BinaryTreeNode<T>* GetChildPtr(int) const;   //提供和TreeNode相同的接口
    int FindChildIdx(BinaryTreeNode<T>*) const;  //提供和TreeNode相同的接口
    void PrintTree() const;                      //完整打印以该节点为根节点的树

    void SetNodeData(T);                         //更改自身节点的值
    void SetLeftChild(BinaryTreeNode<T>*);       //以传指针的方式设置左子节点（会覆盖）
    void SetLeftChild(T);                        //以传值的方式设置左子节点（会覆盖）
    void SetRightChild(BinaryTreeNode<T>*);      //以传指针的方式设置右子节点（会覆盖）
    void SetRightChild(T);                       //以传值的方式设置右子节点（会覆盖）
    void DelLeftChild();                         //删除左子节点
    void DelRightChild();                        //删除右子节点

protected:
    void PrintTree(int, int) const;              //打印对应深度和类型的树
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
    delete leftChild;
    delete rightChild;
}

template <typename T>
BinaryTreeNode<T>& BinaryTreeNode<T>::operator=(const BinaryTreeNode<T>& _obj)
{
    //防止自我赋值
    if (this == &_obj)
        return *this;

    //拷贝节点数据
    this->nodeData = _obj.GetNodeData();
    //不要拷贝等号右侧对象的父节点，也不要清空this的父节点，保持原有的就好
    // this->parentNode = nullptr;

    //拷贝传入节点的左右子节点
    BinaryTreeNode<T>* _left = _obj.GetLeftChildPtr();
    BinaryTreeNode<T>* _right = _obj.GetRightChildPtr();

    //如果是空的，那就赋空
    if (_left == nullptr)
        leftChild = nullptr;
    //如果是叶节点，那么就可以直接复制（注意不要用接收指针的SetXXChild函数重载版本，因其使用了赋值运算符的重载，会循环引用）
    else if (_left->IsLeaf())
        SetLeftChild(_left->GetNodeData());
    //否则递归调用赋值运算符的重载
    else
    {
        //指向nullptr的leftChild被访问时会报错，所以先在堆区初始化
        leftChild = new BinaryTreeNode<T>(0);
        //注意使用的是解引用，不然就是对指针的操作了
        *leftChild = *_left;
        //注意维护父指针，这个不能放外面，因为当第一个if满足时，nullptr没有自己的parentNode
        leftChild->parentNode = this;
    }
    
    //同样的操作对右子节点进行
    if (_right == nullptr)
        rightChild = nullptr;
    else if (_right->IsLeaf())
        SetRightChild(_right->GetNodeData());
    else
    {
        rightChild = new BinaryTreeNode<T>(0);
        *rightChild = *_right;
        rightChild->parentNode = this;
    }

    //返回自身引用
    return *this;
}

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode<T>& _obj)
{
    //注意，调用了此重载就不会调用默认构造函数，所以此处要再写一遍
    parentNode = nullptr;
    leftChild = nullptr;
    rightChild = nullptr;
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

template <typename T>
int BinaryTreeNode<T>::GetSize() const
{
    //将自身算进去
    int _counter = 1;
    //如果有子节点，那就需要加上子节点的节点数
    if (!IsLeaf())
    {
        //递归调用，加上子节点的体积
        if (HasLeftChild())
            _counter += leftChild->GetSize();
        if (HasRightChild())
            _counter += rightChild->GetSize();
    }
    return _counter;
}

template <typename T>
int BinaryTreeNode<T>::GetDepth() const
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
        //递归调用，获取二者的最大深度
        if (HasLeftChild())
            _maxDepth = std::max(_maxDepth, leftChild->GetDepth());
        if (HasRightChild())
            _maxDepth = std::max(_maxDepth, rightChild->GetDepth());

        //给计数器加上子结点中的最大深度
        _counter += _maxDepth;
        return _counter;
    }
}

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

template <typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::GetChildPtr(int _idx) const
{
    if (_idx < 0 || _idx > 1)
        throw std::invalid_argument("ERROR: Invalid Index {BinaryTreeNode<T>* BinaryTreeNode<T>::GetChildPtr(int _idx) const}");

    //若是叶节点就返回nullptr
    if (!IsLeaf())
    {
        //此函数目的是提供一个与TreeNode的获取子节点指针函数相连贯的逻辑，使得TreeNode的迭代器也可以迭代二叉树
        if (_idx == 0)
        {
            if (HasLeftChild())
                return leftChild;
            else
                return rightChild;
        }
        else
        {
            if (GetDegree() == 1)
                throw std::invalid_argument("ERROR: Invalid Index {BinaryTreeNode<T>* BinaryTreeNode<T>::GetChildPtr(int _idx) const}");
            else
                return rightChild;
        }
    }
    else
        throw std::invalid_argument("ERROR: The Node Has No Child {BinaryTreeNode<T>* BinaryTreeNode<T>::GetChildPtr(int _idx) const}");
}

template <typename T>
int BinaryTreeNode<T>::FindChildIdx(BinaryTreeNode<T>* _obj) const
{
    //该函数也是为了能够使用TreeNode的迭代器，而迭代器用到了TreeNode的这个同名函数，所以我们也提供一个
    if (_obj == leftChild && HasLeftChild())
        return 0;

    if (_obj == rightChild && HasRightChild())
    {
        if (GetDegree() == 2)
            return 1;
        if (GetDegree() == 1)
            return 0;
    }

    //经历上述过程都没找到，那就返回-1
    return -1;
}

template <typename T>
void BinaryTreeNode<T>::PrintTree() const
{
    //传入的初始深度为零、树类型为0，表示打印以此节点为根节点的整个树
    this->PrintTree(0, 0);
}

template <typename T>
void BinaryTreeNode<T>::SetNodeData(T _val)
{
    nodeData = _val;
}

template <typename T>
void BinaryTreeNode<T>::SetLeftChild(BinaryTreeNode<T>* _node)
{
    //将传入节点通过（赋值运算符已经过深拷贝重载）深拷贝到新的内存
    BinaryTreeNode<T> _new = *_node;

    if (!HasLeftChild())
    {
        //防止解引用得到无法被赋值的对象
        leftChild = new BinaryTreeNode<T>(0);
        //赋值运算符拷贝给左子节点（注意解引用获取leftChild的引用）
        *leftChild = _new;
        //注意对父节点进行维护
        leftChild->parentNode = this;
    }
    else
    {
        DelLeftChild();
        SetLeftChild(_node);
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
        leftChild->parentNode = this;
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
        //防止解引用得到无法被赋值的对象
        rightChild = new BinaryTreeNode<T>(0);
        //赋值运算符拷贝给左子节点（注意解引用获取rightChild的引用）
        *rightChild = _new;
        //注意对父节点进行维护
        rightChild->parentNode = this;
    }
    else
    {
        DelRightChild();
        SetRightChild(_node);
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
        rightChild->parentNode = this;
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
    leftChild = nullptr;
}

template <typename T>
void BinaryTreeNode<T>::DelRightChild()
{
    rightChild = nullptr;
}

template <typename T>
void BinaryTreeNode<T>::PrintTree(int _depth, int _type) const
{
    //根据传入的深度参数，得知当前节点处于多深，打印时需要在前面垫上相应的深度
    for (int i = 0; i < _depth; i++)
    {
        std::cout << "\t";
    }

    //打印节点本身
    switch (_type)
    {
    case 0:
        //根节点
        std::cout << "-[" << this->GetNodeData() << "]\n";
        break;
    case 1:
        //标记左子树
        std::cout << "-L[" << this->GetNodeData() << "]\n";
        break;
    case 2:
        //标记右子树
        std::cout << "-R[" << this->GetNodeData() << "]\n";
        break;
    default:
        throw std::invalid_argument("ERROR: Invalid Tree Type Number {void BinaryTreeNode<T>::PrintTree(int _depth, int _type) const}");
    }

    //先检测左子节点，递归调用
    if (HasLeftChild())
        leftChild->PrintTree(_depth + 1, 1);
    //若另一边的右节点存在，则打印以下内容表示该二叉树非满
    else if (HasRightChild())
    {
        //注意此处是(_depth + 1)
        for (int i = 0; i < _depth + 1; i++)
        {
            std::cout << "\t";
        }
        std::cout << "-L[ ]\n";
    }

    //然后检测右子节点
    if (HasRightChild())
        rightChild->PrintTree(_depth + 1, 2);
    else if (HasLeftChild())
    {
        //注意此处是(_depth + 1)
        for (int i = 0; i < _depth + 1; i++)
        {
            std::cout << "\t";
        }
        std::cout << "-R[ ]\n";
    }
}

namespace Test_Binary_Tree_Node
{
    void MainTest()
    {
        std::cout << "--------------------------------------------------\n";

        //初始化二叉树节点
        BinaryTreeNode<int> btn(111);
        std::cout << "**Print btn\n"; btn.PrintTree();
        //-[111]
        
        //扩增二叉树
        BinaryTreeNode<int> temp1(222);
        BinaryTreeNode<int> temp2(555);
        btn.SetLeftChild(&temp1);
        btn.SetRightChild(333);
        btn.GetLeftChildPtr()->SetLeftChild(444);
        btn.GetRightChildPtr()->SetRightChild(&temp2);
        std::cout << "**Print btn\n"; btn.PrintTree();
        //-[111]
        //        -L[222]
        //                -L[444]
        //                -R[ ]
        //        -R[333]
        //                -L[ ]
        //                -R[555]

        //测试拷贝构造与赋值运算符重载，下面两句是等效的
        // BinaryTreeNode<int> copy = btn;
        BinaryTreeNode<int> copy(btn);
        std::cout << "**Print copy\n"; copy.PrintTree();
        //-[111]
        //        -L[222]
        //                -L[444]
        //                -R[ ]
        //        -R[333]
        //                -L[ ]
        //                -R[555]

        //测试覆盖
        btn.SetLeftChild(888);
        BinaryTreeNode<int> temp3(999);
        btn.SetRightChild(&temp3);
        std::cout << "**Print btn\n"; btn.PrintTree();
        //-[111]
        //        -L[888]
        //        -R[999]

        //测试树的深度与体积的获取
        btn.GetLeftChildPtr()->SetLeftChild(&btn);
        std::cout << "**Print btn\n"; btn.PrintTree();
        //-[111]
        //        -L[888]
        //                -L[111]
        //                        -L[888]
        //                        -R[999]
        //                -R[ ]
        //        -R[999]
        std::cout << "##btn.GetSize(): " << btn.GetSize() << "\n";
        //##btn.GetSize(): 6
        std::cout << "##btn.GetDepth(): " << btn.GetDepth() << "\n";
        //##btn.GetDepth(): 3

        std::cout << "--------------------------------------------------\n";
    }
}

#endif