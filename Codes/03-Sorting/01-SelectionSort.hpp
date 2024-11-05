#ifndef _SELECTION_SORT_HPP_
#define _SELECTION_SORT_HPP_

#include <vector>
#include "SortingStates.hpp"

//选择排序
//从列表的未排序部分（在最开始，整个列表视为未排序的）中取出最小的值，交换到该部分列表的首位（若首位本来就是最小的，则无需进行Swap操作）
//交换至首位后，该位置的值被纳入整个列表的已排序部分，下次判断操作则从剩余的未排序部分开始
template <typename T>
void SelectionSort(std::vector<T>& _list, SortingStates& _states)
//传入需要被排序的列表的引用，以及用于存储排序过程的容器的引用
{
    #pragma region StatesRecord
    //记录初始状态
    _states.EmplaceBack(_list);
    #pragma endregion

    for (size_t i = 0; i < _list.size(); i++)
    {
        //获取列表的未排序部分的最小元素索引
        size_t _minIdx = i;
        for (size_t j = i + 1; j < _list.size(); j++)
        {
            if (_list[j] < _list[_minIdx])
                _minIdx = j;
        }

        //如果已经是最小的了，则直接跳过该轮循环，无需执行Swap操作
        if (i == _minIdx)
            continue;

        //将未排序部分列表的最小值放到其首（即已排序部分列表的末尾）
        std::swap(_list[i], _list[_minIdx]);

        #pragma region StatesRecord
        //每交换一次即实现了一次操作，记录该操作后的列表状态，标记被交换的两个索引
        std::vector<size_t> _tags = { i, _minIdx };
        _states.EmplaceBack(_list, _tags);
        #pragma endregion
    }
}

// ##LengthOfUnorderedList=15
// ##SelectionSort
// [0]:     14 , 2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [1]:    <1>, 2 , 5 , 12 , 3 , 9 , 13 ,<14>, 10 , 15 , 8 , 6 , 7 , 4 , 11
// [2]:     1 , 2 ,<3>, 12 ,<5>, 9 , 13 , 14 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [3]:     1 , 2 , 3 ,<4>, 5 , 9 , 13 , 14 , 10 , 15 , 8 , 6 , 7 ,<12>, 11
// [4]:     1 , 2 , 3 , 4 , 5 ,<6>, 13 , 14 , 10 , 15 , 8 ,<9>, 7 , 12 , 11
// [5]:     1 , 2 , 3 , 4 , 5 , 6 ,<7>, 14 , 10 , 15 , 8 , 9 ,<13>, 12 , 11
// [6]:     1 , 2 , 3 , 4 , 5 , 6 , 7 ,<8>, 10 , 15 ,<14>, 9 , 13 , 12 , 11
// [7]:     1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 ,<9>, 15 , 14 ,<10>, 13 , 12 , 11
// [8]:     1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 ,<10>, 14 ,<15>, 13 , 12 , 11
// [9]:     1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 ,<11>, 15 , 13 , 12 ,<14>
// [10]:    1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 ,<12>, 13 ,<15>, 14
// [11]:    1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 , 12 , 13 ,<14>,<15>

#endif