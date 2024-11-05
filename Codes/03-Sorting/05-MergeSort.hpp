#ifndef _MERGE_SORT_HPP_
#define _MERGE_SORT_HPP_

#include <vector>
#include "SortingStates.hpp"

//当子列表的长度小于等于该值时，调用其它的低空间复杂度的排序函数（此处使用插入排序）以降低归并排序的空间复杂度
// #define MERGE_SORT_THRESHOLD 4
// #define MERGE_SORT_BORROW_FUNC InsertionSort 

//传入三个索引，定位需要被融合的两个已排好序的子部分，将二者融合
template <typename T>
bool Merge(std::vector<T>& _list, size_t _1Begin, size_t _2Begin, size_t _2End, SortingStates& _states)
{
    //需要被合并的两个子列表必然是相邻的
    size_t _1End = _2Begin - 1;
    //分别指向两个（默认是有序的）列表中的被比较元素的索引
    size_t _1Pt = _1Begin;
    size_t _2Pt = _2Begin;

    //存放排序结果的临时列表
    std::vector<T> _result;

    while (true)
    {
        //谁小放谁到结果列表里，并递增相应的索引
        if (_list[_1Pt] <= _list[_2Pt])
        {
            _result.emplace_back(_list[_1Pt]);
            _1Pt++;
        }
        else
        {
            _result.emplace_back(_list[_2Pt]);
            _2Pt++;
        }

        //当其中一个子列表被遍历完了后，跳出循环
        if (_1Pt == _1End || _2Pt == _2End)
            break;
    }

    //将另一个未被遍历完的子列表的剩余元素塞入结果列表里
    if (_1Pt < _1End)
    {
        for (size_t i = _1Pt; i <= _1End; i++)
        {
            _result.emplace_back(_list[i]);
        }
    }
    if (_2Pt < _2End)
    {
        for (size_t i = _2Pt; i <= _2End; i++)
        {
            _result.emplace_back(_list[i]);
        }
    }

    //用融合好的结果，替换掉传入列表中未融合的那部分
    _list.assign
}

//纯粹的归并排序
template <typename T>
void MetaMergeSort_Pure(std::vector<T>& _list, size_t _begin, size_t _end, SortingStates& _states)
{
    //计算需要（递归的）进行归并排序的部分的长度，以此计算出其分裂的两个子列表的定位索引
    size_t _length = _end - _begin + 1;
    size_t _2Begin = _begin + _length / 2;
    size_t _1End = _begin + _length / 2 - 1;

    //递归调用分裂出来的左侧的子列表
    MetaMergeSort_Pure(_list, _begin, _1End, _states);
    //递归调用分裂出来的右侧的子列表
    MetaMergeSort_Pure(_list, _2Begin, _end, _states);

    //将上述两个排好序的子列表合并
    Merge(_list, _begin, _2Begin, _end, _states);
}

// //混用了其他类型排序的归并排序
// template <typename T>
// void MetaMergeSort_Mix(std::vector<T>& _list, size_t _begin, size_t _end, SortingStates& _states)
// {
//     //计算需要（递归的）进行归并排序的部分的长度
//     size_t _length = _end - _begin + 1;
//
//     //若子列表长度小于等于预定的阈值，则对该子列表调用其它低空间复杂度的排序函数
//     if (_length <= MERGE_SORT_THRESHOLD)
//     {
//         MERGE_SORT_BORROW_FUNC(_list, _begin, _end, _states);
//     }
//     else
//     {
//         //计算分裂的两个子列表的定位索引
//         size_t _2Begin = _begin + _length / 2;
//         size_t _1End = _begin + _length / 2 - 1;
//      
//         //递归调用分裂出来的左侧的子列表
//         MetaMergeSort_Mix(_list, _begin, _1End, _states);
//         //递归调用分裂出来的右侧的子列表
//         MetaMergeSort_Mix(_list, _2Begin, _end, _states);   
//     }
//
//     //将上述两个排好序的子列表合并
//     Merge(_list, _begin, _2Begin, _end, _states);
// }

//为了满足SortingManager中记录排序函数的std::function<void(std::vector<T>&, SortingStates&)>变量的类型的统一性
template <typename T>
void MergeSort(std::vector<T>& _list, SortingStates& _states)
{
    #pragma region StatesRecord
    //记录初始状态
    _states.EmplaceBack(_list);
    #pragma endregion

    //对整个列表进行归并排序
    MetaMergeSort_Pure(_list, 0, _list.size() - 1, _states);
    // MetaMergeSort_Mix(_list, 0, _list.size() - 1, _states);

    #pragma region StatesRecord
    _states.EmplaceBack(_list);
    #pragma endregion
}

#endif