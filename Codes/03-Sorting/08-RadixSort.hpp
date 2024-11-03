#ifndef _RADIX_SORT_HPP_
#define _RADIX_SORT_HPP_

#include <vector>
#include "SortingStates.hpp"

//基数排序：
template <typename T>
void RadixSort(std::vector<T>& _list, SortingStates& _states)
{
    #pragma region StatesRecord
    //记录初始状态
    _states.EmplaceBack(_list);
    #pragma endregion
}

#endif