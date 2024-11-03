#ifndef _BUCKET_SORT_HPP_
#define _BUCKET_SORT_HPP_

#include <vector>
#include "SortingStates.hpp"

//桶排序：
//
template <typename T>
void BucketSort(std::vector<T>& _list, SortingStates& _states)
{
    #pragma region StatesRecord
    //记录初始状态
    _states.EmplaceBack(_list);
    #pragma endregion
}

#endif