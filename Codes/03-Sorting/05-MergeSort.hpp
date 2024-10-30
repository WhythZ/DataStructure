#ifndef _MERGE_SORT_HPP_
#define _MERGE_SORT_HPP_

#include <vector>

template <typename T>
void MergeSort(std::vector<T>& _list, std::vector<std::vector<T>>& _states)
{
    //记录初始状态
    _states.emplace_back(_list);
}

#endif