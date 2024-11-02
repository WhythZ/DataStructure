#ifndef _INSERTION_SORT_HPP_
#define _INSERTION_SORT_HPP_

#include <vector>

//交换列表中的两个元素，额外使用O(1)的内存空间
template <typename T>
void Swap(std::vector<T>& _list, int _idx1, int _idx2)
{
    if (_idx1 == _idx2)
        return;

    T _temp = _list[_idx1];
    _list[_idx1] = _list[_idx2];
    _list[_idx2] = _temp;
}

//插入排序：
//从0索引处开始，取出1索引值，其与0索引值比较，若[1]比[0]大则无需移动，若小则将[1]插入[0]左侧
//然后从1索引处开始，取出2索引值，其与1索引值比较，若[2]比[1]大则无需移动，若小则将其与[0]比较；若[2]比[0]大则将[2]插入[0]右侧、[1]左侧，若小则将[2]插入[0]左侧
//以此类推后续过程，直到遍历至列表中的最后一个元素并完成其判断与可能的移动，排序结束
template <typename T>
void InsertionSort(std::vector<T>& _list, std::vector<std::vector<T>>& _states)
{
    //记录初始状态
    _states.emplace_back(_list);

    //注意从索引1处开始而不是0，因为0索引处的左侧没有元素，其无需进行插入操作
    for (std::vector<T>::iterator _it = _list.begin() + 1; _it != _list.end(); _it++)
    {
        //取出索引处的元素，并在存储了指向其前一个元素的迭代器后将索引处元素移除
        T _pop = *_it;
        std::vector<T>::iterator _temp = _it - 1;
        _list.erase(_it);

        //从迭代器_it左侧的第一个元素开始向左遍历，依次将_pop与*_temp进行比较
        while (_temp != _list.begin())
        {
            //若不比该元素小，则将_pop插入该元素右侧
            if (_pop >= *_temp)
            {
                _list.insert(_temp + 1, _pop);
                break;
            }

            _temp--;
        }
    }
}

#endif