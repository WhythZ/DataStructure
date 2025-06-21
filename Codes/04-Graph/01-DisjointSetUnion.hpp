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
    std::vector<size_t> parent;

    //用于按秩合并优化，合并时将矮树挂到高树下以降低树的高度
    //只有当某节点为根节点时，其秩值才有意义，用于衡量其树高度
    std::vector<size_t> rank;

    //缓存不相交集合的数量
    size_t setNum;

public:
    DisjointSetUnion(size_t);        //并查集中元素的个数
    
    size_t Find(size_t);             //路径压缩优化，查询某个元素所处不相交集合的根节点
    void Union(size_t, size_t);      //按秩合并优化，合并两个不相交集合集为一个新的集合

    size_t GetSetNum() const;        //获取并查集中不相交集合的数量
    void Print() const;              //打印内核数组用于测试，特别标注根节点
};

DisjointSetUnion::DisjointSetUnion(size_t _size)
{
    //每个元素初始时都作为一个独立的不相交集合
    parent.resize(_size);
    for (size_t i = 0; i < _size; i++)
        parent[i] = i;

    //不相交集合数量
    setNum = _size;
    
    //所有的秩初始为0
    rank.resize(_size, 0);
}

size_t DisjointSetUnion::Find(size_t _idx)
{
    // //递归法，集合链极长时可能导致栈溢出，最好采用迭代法
    // if (_idx != parent[_idx])
    // {
    //     parent[_idx] = Find(parent[_idx]);
    //     return parent[_idx];
    // }
    // else
    //     return _idx;

    //迭代法，先获取根节点索引
    size_t _root = _idx;
    while (_root != parent[_root])
        _root = parent[_root];
    //然后再压缩路径
    while (_idx != _root)
    {
        size_t _backup = parent[_idx];
        parent[_idx] = _root;
        _idx = _backup;
    }
    //最后返回根节点索引
    return _root;
}

void DisjointSetUnion::Union(size_t _idx1, size_t _idx2)
{
    //将第二个索引节点所属集合并入第一个索引节点所属集合
    // parent[Find(_idx2)] = Find(_idx1);

    // //确保两个索引处的元素是根节点
    // _idx1 = Find(_idx1);
    // _idx2 = Find(_idx2);
    // //将_idx2所属集合合并到_idx1所属集合上
    // if (_idx1 != _idx2)
    //     parent[_idx2] = _idx1;

    _idx1 = Find(_idx1);
    _idx2 = Find(_idx2);
    //若归属集合相同，则无需进行后续检查
    if (_idx1 == _idx2) return;
    
    //按秩合并决策树，若树1较矮则挂到树2，若树2较矮则挂到树1
    if (rank[_idx1] < rank[_idx2])
        parent[_idx1] = _idx2;
    else if(rank[_idx1] > rank[_idx2])
        parent[_idx2] = _idx1;
    else
    {
        //秩相等时任意挂接
        parent[_idx2] = _idx1;
        //被挂载根节点对应的秩值递增
        rank[_idx1]++;
    }

    //不相交集合数量递减
    setNum--;
}

size_t DisjointSetUnion::GetSetNum() const
{
    // size_t _num = 0;
    // for (size_t i = 0; i < parent.size(); i++)
    // {
    //     if (i == parent[i])
    //         _num++;
    // }
    // return _num;

    return setNum;
}

void DisjointSetUnion::Print() const
{
    for (size_t i = 0; i < parent.size(); i++)
    {
        if (i == parent[i])
            std::cout << "{" << parent[i] << "} ";
        else
            std::cout << " " << parent[i] << "  ";
    }
    std::cout << "\n";
}

namespace Test_Disjoint_Set_Union
{
    void MainTest()
    {
        std::cout << "--------------------------------------------------\n";

        //开辟一个包含10个元素的并查集
        DisjointSetUnion dsu(10); dsu.Print();
        //{0} {1} {2} {3} {4} {5} {6} {7} {8} {9}

        //测试下Find函数
        std::cout << "**dsu.Find(2)\n"; std::cout << dsu.Find(2) << "\n";
        //2

        //测试下GetSetNum函数
        std::cout << "##dsu.GetSetNum()\n"; std::cout << dsu.GetSetNum() << "\n";
        //10

        //测试下Union函数
        std::cout << "**dsu.Union(0, 1)\n"; dsu.Union(0, 1); dsu.Print();
        //按秩合并优化前：{0}  0  {2} {3} {4} {5} {6} {7} {8} {9}
        //按秩合并优化后：{0}  0  {2} {3} {4} {5} {6} {7} {8} {9}
        std::cout << "**dsu.Union(1, 2)\n"; dsu.Union(1, 2); dsu.Print();
        //按秩合并优化前：{0}  0   0  {3} {4} {5} {6} {7} {8} {9}
        //按秩合并优化后：{0}  0   0  {3} {4} {5} {6} {7} {8} {9}
        std::cout << "**dsu.Union(9, 8)\n"; dsu.Union(9, 8); dsu.Print();
        //按秩合并优化前：{0}  0   0  {3} {4} {5} {6} {7}  9  {9}
        //按秩合并优化后：{0}  0   0  {3} {4} {5} {6} {7}  9  {9}
        std::cout << "**dsu.Union(8, 7)\n"; dsu.Union(8, 7); dsu.Print();
        //按秩合并优化前：{0}  0   0  {3} {4} {5} {6}  9   9  {9}
        //按秩合并优化后：{0}  0   0  {3} {4} {5} {6}  9   9  {9}
        std::cout << "**dsu.Union(7, 0)\n"; dsu.Union(7, 0); dsu.Print();
        //按秩合并优化前： 9   0   0  {3} {4} {5} {6}  9   9  {9}
        //按秩合并优化后： 9   0   0  {3} {4} {5} {6}  9   9  {9}
        std::cout << "**dsu.Union(1, 3)\n"; dsu.Union(1, 3); dsu.Print();
        //按秩合并优化前： 9   9   0   9  {4} {5} {6}  9   9  {9}
        //按秩合并优化后： 9   9   0   9  {4} {5} {6}  9   9  {9}
        std::cout << "**dsu.Union(2, 9)\n"; dsu.Union(2, 9); dsu.Print();
        //按秩合并优化前： 9   9   9   9  {4} {5} {6}  9   9  {9}
        //按秩合并优化后： 9   9   9   9  {4} {5} {6}  9   9  {9}

        //测试下GetSetNum函数
        std::cout << "##dsu.GetSetNum()\n"; std::cout << dsu.GetSetNum() << "\n";
        //4

        //继续测试Union函数
        std::cout << "**dsu.Union(4, 9)\n"; dsu.Union(4, 9); dsu.Print();
        //按秩合并优化前： 9   9   9   9  {4} {5} {6}  9   9   4
        //按秩合并优化后： 9   9   9   9   9  {5} {6}  9   9  {9}
        std::cout << "**dsu.Union(1, 5)\n"; dsu.Union(1, 5); dsu.Print();
        //按秩合并优化前： 9   4   9   9  {4}  4  {6}  9   9   4
        //按秩合并优化后： 9   9   9   9   9   9  {6}  9   9  {9}
        std::cout << "**dsu.Union(6, 0)\n"; dsu.Union(6, 0); dsu.Print();
        //按秩合并优化前： 4   4   9   9   6   4  {6}  9   9   4
        //按秩合并优化后： 9   9   9   9   9   9   9   9   9  {9}

        //测试下Find函数
        std::cout << "**dsu.Find(0)\n"; std::cout << dsu.Find(0) << "\n";
        //按秩合并优化前：6
        //按秩合并优化后：9
        dsu.Print();
        //按秩合并优化前： 6   4   9   9   6   4  {6}  9   9   4
        //按秩合并优化后： 9   9   9   9   9   9   9   9   9  {9}

        //测试下GetSetNum函数
        std::cout << "##dsu.GetSetNum()\n"; std::cout << dsu.GetSetNum() << "\n";
        //1

        std::cout << "--------------------------------------------------\n";
    }
}

#endif