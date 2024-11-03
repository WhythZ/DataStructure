#ifndef _BUBBLE_SORT_HPP_
#define _BUBBLE_SORT_HPP_

#include <vector>

//冒泡排序：
//
template <typename T>
void BubbleSort(std::vector<T>& _list, SortingStates& _states)
{
    #pragma region StatesRecord
    //记录初始状态
    _states.EmplaceBack(_list);
    #pragma endregion
}

#endif