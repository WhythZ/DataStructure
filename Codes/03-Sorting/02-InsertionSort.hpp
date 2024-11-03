#ifndef _INSERTION_SORT_HPP_
#define _INSERTION_SORT_HPP_

#include <vector>
#include "SortingStates.hpp"

//插入排序：
//取出列表索引1处的值，其与0索引值比较，若[1]比[0]大则无需移动，若小则将[1]插入[0]左侧
//然后取出索引2处的值，其与1索引值比较，若[2]比[1]大则无需移动，若小则将其与[0]比较；若[2]比[0]大则将[2]插入[0]右侧、[1]左侧，若小则将[2]插入[0]左侧
//依此类推后续过程，直到遍历至列表中的最后一个元素并完成其判断与可能的移动，排序结束
template <typename T>
void InsertionSort(std::vector<T>& _list, SortingStates& _states)
{
    #pragma region StatesRecord
    //记录初始状态
    _states.EmplaceBack(_list);
    #pragma endregion

    //注意我们从索引1处开始，因为索引0处的左侧无元素可以比较
    for (size_t i = 1; i < _list.size(); i++)
    {
        //将i索引处的值向左浮动至符合顺序的位置进行"插入"
        size_t _idx = i;
        while (_list[_idx - 1] > _list[_idx])
        {
            std::swap(_list[_idx - 1], _list[_idx]);
            _idx--;
        }

        #pragma region StatesRecord
        //标记被插入处的索引
        std::vector<size_t> _tags = { _idx };
        _states.EmplaceBack(_list, _tags);
        #pragma endregion
    }
}

#endif