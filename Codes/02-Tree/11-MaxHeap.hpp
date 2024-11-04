#ifndef _MAX_HEAP_HPP_
#define _MAX_HEAP_HPP_

#include <iostream>
#include <vector>
#include <cmath>

//最大堆的数组形式实现
template <typename T>
class MaxHeap
{
private:
    std::vector<T> array;           //以数组形式存储完全二叉树形状的堆
    size_t height = 0;              //维护一个表示二叉树高度的值

public:
    void PrintTree() const;         //以最大堆的形式可视化打印该数组
    T GetTop() const;               //获取堆顶元素的值

    void Push(T);                   //将新元素推送到堆中并维持平衡
    void Pop();                     //弹出堆顶元素并维持平衡
    
private:
    void PrintLayer(size_t) const;  //打印对应深度的二叉树层

    //获取迭代器对应元素的索引值
    size_t GetIdxFromItr(typename std::vector<T>::iterator);
    //以迭代器获取其指代元素的父节点、左右子节点的迭代器
    typename std::vector<T>::iterator GetParentItr(typename std::vector<T>::iterator);
    typename std::vector<T>::iterator GetLChildItr(typename std::vector<T>::iterator);
    typename std::vector<T>::iterator GetRChildItr(typename std::vector<T>::iterator);
    
    //以迭代器锁定堆中元素，对其进行向上或向下的渗流操作
    void PercolateUp(typename std::vector<T>::iterator);
    void PercolateDown(typename std::vector<T>::iterator);
};

template <typename T>
void MaxHeap<T>::PrintTree() const
{
    for (size_t _depth = 0; _depth <= height; _depth++)
    {
        PrintLayer(_depth);
    }
}

template <typename T>
T MaxHeap<T>::GetTop() const
{
    //列表首位便是堆顶的最大值
    return array[0];
}

template <typename T>
void MaxHeap<T>::Push(T _val)
{
    //将元素推送到数组末尾，即堆的最底部的最左侧的可以插入节点的空位处
    array.emplace_back(_val);
    //对新插入的元素进行向上渗流
    PercolateUp(array.end() - 1);

    //更新树高，以换底公式计算$\log_2{n}$，并向下取整
    height = floor(log(array.size()) / log(2));
}

template <typename T>
void MaxHeap<T>::Pop()
{
    if (array.size() == 0)
        throw std::invalid_argument("ERROR: You cannot pop from an empty maxheap");

    //移除堆顶，将数组末尾的元素转移到堆顶
    std::iter_swap(array.begin(), array.end() - 1);
    array.erase(array.end() - 1);

    //然后对堆顶进行向下渗流
    PercolateDown(array.begin());

    //更新树高，以换底公式计算$\log_2{n}$，并向下取整
    height = floor(log(array.size()) / log(2));
}

template <typename T>
void MaxHeap<T>::PrintLayer(size_t _depth) const
{
    //计算该深度的第一个节点的索引
    size_t _firstIdx = std::pow(2, _depth) - 1;

    //计算该层拥有的节点数
    size_t _nodeNum = (_depth < height) ? pow(2, _depth) : array.size() - (pow(2, height) - 1);
    // size_t _nodeNum = 0;
    // if (_depth < height)
    //     _nodeNum = pow(2, _depth);
    // else if (_depth == height)
    //     _nodeNum = array.size() - (pow(2, height) - 1);

    std::cout << "Layer[" << _depth << "]:\t";
    for (size_t i = _firstIdx; i < _firstIdx + _nodeNum; i++)
    {
        if (i % 2 == 1)
            std::cout << "<";
        std::cout << array[i];
        if (i % 2 == 0 && i != 0)
            std::cout << ">";
        std::cout << "  ";
    }
    std::cout << "\n";
}

template <typename T>
size_t MaxHeap<T>::GetIdxFromItr(typename std::vector<T>::iterator _itr)
{
    return std::distance(array.begin(), _itr);
}

template <typename T>
typename std::vector<T>::iterator MaxHeap<T>::GetParentItr(typename std::vector<T>::iterator _elem)
{
    //根节点没有父节点，返回空
    if (_elem == array.begin())
        return array.end();

    //注意此处的除法是向下取整
    size_t _idx = (GetIdxFromItr(_elem) + 1) / 2 - 1;
    return array.begin() + _idx;
}

template <typename T>
typename std::vector<T>::iterator MaxHeap<T>::GetLChildItr(typename std::vector<T>::iterator _elem)
{
    size_t _idx = 2 * GetIdxFromItr(_elem) + 1;
    //若超出范围，则说明没有子节点，返回空
    if (_idx >= array.size())
        return array.end();
    return array.begin() + _idx;
}

template <typename T>
typename std::vector<T>::iterator MaxHeap<T>::GetRChildItr(typename std::vector<T>::iterator _elem)
{
    size_t _idx = 2 * GetIdxFromItr(_elem) + 2;
    //若超出范围，则说明没有子节点，返回空
    if (_idx >= array.size())
        return array.end();
    return array.begin() + _idx;
}

template <typename T>
void MaxHeap<T>::PercolateUp(typename std::vector<T>::iterator _itr)
{
    //根节点则到顶了，无法也无需再向上渗流
    if (_itr == array.begin())
        return;

    //获取目标元素的父节点
    typename std::vector<T>::iterator _parent = GetParentItr(_itr);
    if (*_itr > *_parent)
    {
        //交换二者位置确保大的在上面（std::iter_swap并未交换两个迭代器指向的位置，交换的是两个位置上的值）
        std::iter_swap(_itr, _parent);
        //递归调用此函数，直到渗流到合适的位置
        PercolateUp(_parent);
    }
}

template <typename T>
void MaxHeap<T>::PercolateDown(typename std::vector<T>::iterator _itr)
{
    //若到达叶节点，则直接返回（此处array.end()是作为类似nullptr的存在）
    if (GetLChildItr(_itr) == array.end() && GetRChildItr(_itr) == array.end())
        return;

    //获取左右子节点中值最大的那个
    typename std::vector<T>::iterator _maxChild = *GetLChildItr(_itr) > *GetRChildItr(_itr) ? GetLChildItr(_itr) : GetRChildItr(_itr);
    if (*_itr < *_maxChild)
    {
        std::iter_swap(_itr, _maxChild);
        PercolateDown(_maxChild);
    }
}

namespace Test_Max_Heap
{
    void MainTest()
    {
        std::cout << "--------------------------------------------------\n";

        MaxHeap<int> mh;
        mh.Push(66);
        mh.Push(99);
        mh.Push(88);
        mh.Push(77);
        mh.Push(11);
        mh.Push(33);
        mh.Push(22);
        mh.Push(55);
        mh.Push(44);
        std::cout << "**mh.PrintTree()\n"; mh.PrintTree();
        //Layer[0]:       99
        //Layer[1]:       <77  88>
        //Layer[2]:       <66  11>  <33  22>
        //Layer[3]:       <55  44>

        std::cout << "**mh.Push(121)\n"; mh.Push(121);
        std::cout << "**mh.PrintTree()\n"; mh.PrintTree();
        //Layer[0]:       121  
        //Layer[1]:       <99  88>  
        //Layer[2]:       <66  77>  <33  22>  
        //Layer[3]:       <55  44>  <11

        std::cout << "**mh.Pop()\n"; mh.Pop();
        std::cout << "**mh.PrintTree()\n"; mh.PrintTree();
        //Layer[0]:       99
        //Layer[1]:       <77  88>
        //Layer[2]:       <66  11>  <33  22>
        //Layer[3]:       <55  44>
        
        std::cout << "**mh.Pop()\n"; mh.Pop();
        std::cout << "**mh.Pop()\n"; mh.Pop();
        std::cout << "**mh.Pop()\n"; mh.Pop();
        std::cout << "**mh.PrintTree()\n"; mh.PrintTree();
        //Layer[0]:       66
        //Layer[1]:       <55  44>
        //Layer[2]:       <22  11>  <33

        std::cout << "**mh.Push(132)\n"; mh.Push(132);
        std::cout << "**mh.PrintTree()\n"; mh.PrintTree();
        //Layer[0]:       132
        //Layer[1]:       <55  66>
        //Layer[2]:       <22  11>  <33  44>
        
        std::cout << "--------------------------------------------------\n";
    }
}

#endif