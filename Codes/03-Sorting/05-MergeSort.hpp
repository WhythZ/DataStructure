#ifndef _MERGE_SORT_HPP_
#define _MERGE_SORT_HPP_

#include <vector>
#include "SortingStates.hpp"

#define MERGE_SORT_THRESHOLD 4

//以上下界索引的方式，传入被排序列表的需要被融合的两个子部分
template <typename T>
bool Merge(std::vector<T>& _list, size_t _1stLower, size_t _2ndLower, size_t _2ndUpper, SortingStates& _states)
{
    //需要被合并的两个子列表必然是相邻的
    size_t _1stUpper = _2ndLower - 1;

    //分别指向两个（默认是有序的）列表中的被比较元素的索引
    size_t _1stIdx = _1stLower;
    size_t _2ndIdx = _2ndLower;

    while (true)
    {
        if(_list[_1stIdx] )
    }
}

//混用了插入排序的归并排序，若阈值取1的话那就是纯萃的归并排序
template <typename T>
void MergeSort(std::vector<T>& _list, size_t _begin, size_t _end, SortingStates& _states)
{
    #pragma region StatesRecord
    //记录初始状态
    _states.EmplaceBack(_list);
    #pragma endregion

    //计算
    size_t _length = _end - _begin + 1;
}

#endif