#ifndef _SELECTION_SORT_HPP_
#define _SELECTION_SORT_HPP_

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

//选择排序
template <typename T>
void SelectionSort(std::vector<T>& _list)
{
    for (size_t i = 0; i < _list.size(); i++)
    {
        //获取列表的未排序部分的最小元素索引
        int _minIdx = i;
        for (size_t j = i + 1; j < _list.size(); j++)
        {
            if (_list[j] < _list[_minIdx])
                _minIdx = j;
        }

        //将未排序部分列表的最小值放到其首（即已排序部分列表的末尾）
        Swap(_list, i, _minIdx);
    }
}

#endif