#ifndef _BUBBLE_SORT_HPP_
#define _BUBBLE_SORT_HPP_

#include <vector>

//冒泡排序：
template <typename T>
void BubbleSort(std::vector<T>& _list, SortingStates& _states)
{
    #pragma region StatesRecord
    //记录初始状态
    _states.EmplaceBack(_list);
    #pragma endregion

    //外层循环表示要冒(n-1)次泡泡
    for (size_t i = 1; i < _list.size(); i++)
    {
        //内层循环表示要依次对比列表中相邻元素的大小，适时进行交换，共检测(n-1)次
        for (size_t j = 0; j < _list.size() - 1; j++)
        {
            if (_list[j] > _list[j + 1])
            {
                std::swap(_list[j], _list[j + 1]);

                #pragma region StatesRecord
                std::vector<size_t> _tags = { j, j + 1 };
                _states.EmplaceBack(_list, _tags);
                #pragma endregion
            }
        }
    }
}

#endif