#ifndef _BUBBLE_SORT_HPP_
#define _BUBBLE_SORT_HPP_

#include <vector>

//交换列表中的两个元素，额外使用O(1)的内存空间
template <typename T>
void Swap(std::vector<T>& _list, int _idx1, int _idx2)
{
    if (_idx1 == _idx2)
        return;

    T _temp = _list[_idx1];
    _list[_idx1] = _list[_idx2];
    _list[_idx2] = _temp;
}

//冒泡排序：
//
template <typename T>
void BubbleSort(std::vector<T>& _list, std::vector<std::vector<T>>& _states)
{
    //记录初始状态
    _states.emplace_back(_list);
}

#endif