#ifndef _HEAP_SORT_HPP_
#define _HEAP_SORT_HPP_

#include <vector>
#include "SortingStates.hpp"

//堆排序：
template <typename T>
void HeapSort(std::vector<T>& _list, SortingStates& _states)
{
    #pragma region StatesRecord
    //记录初始状态
    _states.EmplaceBack(_list);
    #pragma endregion
}

#endif