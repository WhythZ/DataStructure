#ifndef _HEAP_SORT_HPP_
#define _HEAP_SORT_HPP_

#include <vector>

//堆排序：
//
template <typename T>
void HeapSort(std::vector<T>& _list, std::vector<std::vector<T>>& _states)
{
    //记录初始状态
    _states.emplace_back(_list);
}

#endif