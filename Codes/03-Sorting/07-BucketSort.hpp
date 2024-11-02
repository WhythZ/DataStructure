#ifndef _BUCKET_SORT_HPP_
#define _BUCKET_SORT_HPP_

#include <vector>

//桶排序：
//
template <typename T>
void BucketSort(std::vector<T>& _list, std::vector<std::vector<T>>& _states)
{
    //记录初始状态
    _states.emplace_back(_list);
}

#endif