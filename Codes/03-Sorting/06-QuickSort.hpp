#ifndef _QUICK_SORT_HPP_
#define _QUICK_SORT_HPP_

#include <vector>

template <typename T>
void QuickSort(std::vector<T>& _list, std::vector<std::vector<T>>& _states)
{
    //记录初始状态
    _states.emplace_back(_list);
}

#endif