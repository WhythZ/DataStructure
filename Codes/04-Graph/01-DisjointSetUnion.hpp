#ifndef _DISJOINT_SET_UNION_
#define _DISJOINT_SET_UNION_

#include <iostream>
#include <vector>

// template <typename T>
class DisjointSetUnion
{
private:
    //对于元素值等于索引值的元素，其为所在不相交集合的根节点
    //对于元素值等于索引值的元素，其元素值是其父节点的索引值
    std::vector<size_t> trees;
    
public:
    DisjointSetUnion(size_t);        //并查集中元素的个数
    
    size_t Find(size_t);             //查询某个元素所处不相交集合的根节点
    void Union(size_t, size_t);      //合并两个不相交集合集为一个新的集合

    void Print() const;              //打印内核数组用于测试，特别标注根节点
};

DisjointSetUnion::DisjointSetUnion(size_t _size)
{
    trees.resize(_size);
    //初始时，每个元素都作为一个独立的不相交集合
    for (size_t i = 0; i < _size; i++)
        trees[i] = i;
}

size_t DisjointSetUnion::Find(size_t _idx)
{
    #pragma region WithoutOptimization
    //暴力实现，直接找到目标根节点，时间复杂度为O(h)=O(\ln n)

    // //递归法，递归地向上查询最顶层的根节点
    // return (_idx == trees[_idx]) ? _idx : Find(trees[_idx]);

    // //迭代法，直接通过循环找到根节点
    // while (_idx != trees[_idx])
    //     _idx = trees[_idx];
    // return _idx;
    #pragma endregion

    #pragma region PathCompression
    //路径压缩，在搜索过程中将每个树铺平开来以使得最大深度为1，时间复杂度为O(1)

    // //递归法
    // if (_idx != trees[_idx])
    // {
    //     trees[_idx] = Find(trees[_idx]);
    //     return trees[_idx];
    // }
    // else
    //     return _idx;

    //迭代法，先获取根节点索引
    size_t _root = _idx;
    while (_root != trees[_idx])
        _root = trees[_idx];
    //然后再压缩路径
    while (_idx != _root)
    {
        size_t _backup = trees[_idx];
        trees[_idx] = _root;
        _idx = _backup;
    }
    //最后返回根节点索引
    return _root;
    #pragma endregion
}

void DisjointSetUnion::Union(size_t _idx1, size_t _idx2)
{
    //将第二个索引对应的根节点并到第一个索引对应的根节点上
    //此处使用的Find实现了路径压缩，无需再额外实现
    trees[Find(_idx2)] = Find(_idx1);
}

void DisjointSetUnion::Print() const
{
    for (size_t i = 0; i < trees.size(); i++)
    {
        if (i == trees[i])
            std::cout << "{" << trees[i] << "} ";
        else
            std::cout << " " << trees[i] << "  ";
    }
    std::cout << "\n";
}

namespace Test_Disjoint_Set_Union
{
    void MainTest()
    {
        std::cout << "--------------------------------------------------\n";

        //开辟一个包含10个元素的并查集
        DisjointSetUnion dsu(10);
        dsu.Print();
        //{0} {1} {2} {3} {4} {5} {6} {7} {8} {9}

        //测试下Find函数
        std::cout << "**dsu.Find(2)\n"; std::cout << dsu.Find(2) << "\n";
        //2

        //测试下Union函数
        std::cout << "**dsu.Union(1, 2)\n"; dsu.Union(1, 2); dsu.Print();
        //{0} {1}  1  {3} {4} {5} {6} {7} {8} {9}
        std::cout << "**dsu.Union(2, 3)\n"; dsu.Union(2, 3); dsu.Print();
        //{0} {1}  1   1  {4} {5} {6} {7} {8} {9}
        std::cout << "**dsu.Union(3, 4)\n"; dsu.Union(3, 4); dsu.Print();
        //{0} {1}  1   1   1  {5} {6} {7} {8} {9}
        std::cout << "**dsu.Union(4, 5)\n"; dsu.Union(4, 5); dsu.Print();
        //{0} {1}  1   1   1   1  {6} {7} {8} {9}

        //测试下Find函数
        std::cout << "**dsu.Find(5)\n"; std::cout << dsu.Find(5) << "\n";
        //1
        std::cout << "**dsu.Find(6)\n"; std::cout << dsu.Find(6) << "\n";
        //6

        std::cout << "--------------------------------------------------\n";
    }
}

#endif