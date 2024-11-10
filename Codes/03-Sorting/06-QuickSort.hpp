#ifndef _QUICK_SORT_HPP_
#define _QUICK_SORT_HPP_

#include <vector>
#include "SortingStates.hpp"

//从传入的三个索引中确定基准元素，并将三个元素重新置位，将基准放入第三个索引位置，最小值第一个位置，最大值第二个位置
template <typename T>
void SetPivotFromThree(std::vector<T>& _list, size_t _1Idx, size_t _2Idx, size_t _3Idx)
{
    //确保索引顺序
    if (!(_1Idx <= _2Idx && _2Idx <= _3Idx))
        throw std::runtime_error("ERROR: Incorrect order of indices when calling \"SetPivotFromThree\"");

    //确保将最小值放在第一个索引的位置
    if (_list[_2Idx] < _list[_1Idx])
        std::swap(_list[_2Idx], _list[_1Idx]);
    if (_list[_3Idx] < _list[_1Idx])
        std::swap(_list[_3Idx], _list[_1Idx]);

    //然后将剩下的两个元素比较大小，确保中位数在第三个索引位置，最大值在第二个索引位置
    if (_list[_2Idx] < _list[_3Idx])
        std::swap(_list[_2Idx], _list[_3Idx]);
}

//从列表头部、中间、尾部三个元素中选取中位数作为基准元素进行快速排序
template <typename T>
void MetaQuickSort(std::vector<T>& _list, size_t _begin, size_t _end, SortingStates& _states)
{
    #pragma region StatesRecord
    std::vector<size_t> _tags1 = {};
    std::vector<size_t> _tags2;
    for (size_t i = _begin; i <= _end; i++) { _tags2.emplace_back(i); }
    _states.EmplaceBack(_list, _tags1, _tags2);
    #pragma endregion

    //计算传入部分列表的长度
    size_t _length = _end - _begin + 1;
    if (_length <= 1)
        return;
    //因为我们需要至少三个元素才能使用后面的方法进行排序，所以要单独处理两元素情况
    if (_length == 2)
    {
        if (_list[_begin] > _list[_end])
        {
            std::swap(_list[_begin], _list[_end]);

            #pragma region StatesRecord
            std::vector<size_t> _tags = { _begin, _end };
            _states.EmplaceBack(_list, _tags);
            #pragma endregion
        }
        return;
    }
    // //可以在长度低于某阈值时使用低空间复杂度排序，如传入排序
    // if (_length <= N) { return; }
    
    //计算列表中点位置元素的索引，此变量仅在确定基准时使用一次，不影响后续实际排序时的逻辑
    size_t _mid = (_begin + _end) / 2;
    //将三者中的最小值放入列表_begin索引处，最大值放入_mid，中位数即基准元素放入_end
    SetPivotFromThree(_list, _begin, _mid, _end);

    #pragma region StatesRecord
    _tags1 = { _begin, _mid, _end };
    _states.EmplaceBack(_list, _tags1);
    #pragma endregion
    
    //用两个索引箭头分别从第二个元素和倒数第二个元素位置开始向中间遍历
    size_t _lower = _begin + 1;
    size_t _upper = _end - 1;
    bool _flagL = false;
    bool _flagU = false;
    
    //左箭头碰到比基准大的元素，就可以暂停外部循环而进入内部循环移动右箭头寻找比基准小的元素
    while (true)
    {
        //总数为奇数个时，结束循环的条件为两索引箭头重合，偶数时则为二者大小关系颠倒
        if (_lower >= _upper)
        {
            //将基准元素放到_lower的位置
            //因为_upper递减途中可能会遇到比基准小的元素，而_lower只会停在比基准大的元素处，所以将其换到列表末尾即基准右侧是一定没问题的
            std::swap(_list[_lower], _list[_end]);

            #pragma region StatesRecord
            std::vector<size_t> _tags = { _lower, _end };
            _states.EmplaceBack(_list, _tags);
            #pragma endregion

            break;
        }

        //将箭头移到两个需要被互换的位置
        if (!_flagL)
        {
            if (_list[_lower] > _list[_end])
                _flagL = true;
            else
                _lower++;
        }
        if (!_flagU)
        {
            if (_list[_upper] < _list[_end])
                _flagU = true;
            else
                _upper--;
        }

        //两个标识都为true时应当进行互换，并为下一轮循环做准备
        if (_flagL && _flagU)
        {
            std::swap(_list[_lower], _list[_upper]);

            #pragma region StatesRecord
            std::vector<size_t> _tags = { _lower, _upper };
            _states.EmplaceBack(_list, _tags);
            #pragma endregion

            _flagL = false;
            _flagU = false;
            _lower++;
            _upper--;
        }
    }

    //此时基准元素位于_lower索引处，对其左右两侧元素递归进行快速排序即可
    MetaQuickSort(_list, _begin, _lower - 1, _states);
    MetaQuickSort(_list, _lower + 1, _end, _states);
}

//快速排序
template <typename T>
void QuickSort(std::vector<T>& _list, SortingStates& _states)
{
    #pragma region StatesRecord
    //记录初始状态
    _states.EmplaceBack(_list);
    #pragma endregion

    MetaQuickSort(_list, 0, _list.size() - 1, _states);
}

// ##LengthOfUnorderedList=15
// ##QuickSort
// [0]:     14 , 2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [1]:    {14},{2},{5},{12},{3},{9},{13},{1},{10},{15},{8},{6},{7},{4},{11}
// [2]:    <1>, 2 , 5 , 12 , 3 , 9 , 13 ,<14>, 10 , 15 , 8 , 6 , 7 , 4 ,<11>
// [3]:     1 , 2 , 5 ,<4>, 3 , 9 , 13 , 14 , 10 , 15 , 8 , 6 , 7 ,<12>, 11
// [4]:     1 , 2 , 5 , 4 , 3 , 9 ,<7>, 14 , 10 , 15 , 8 , 6 ,<13>, 12 , 11
// [5]:     1 , 2 , 5 , 4 , 3 , 9 , 7 ,<6>, 10 , 15 , 8 ,<14>, 13 , 12 , 11
// [6]:     1 , 2 , 5 , 4 , 3 , 9 , 7 , 6 , 10 ,<8>,<15>, 14 , 13 , 12 , 11
// [7]:     1 , 2 , 5 , 4 , 3 , 9 , 7 , 6 , 10 , 8 ,<11>, 14 , 13 , 12 ,<15>
// [8]:    {1},{2},{5},{4},{3},{9},{7},{6},{10},{8}, 11 , 14 , 13 , 12 , 15
// [9]:    <1>, 2 , 5 , 4 ,<8>, 9 , 7 , 6 , 10 ,<3>, 11 , 14 , 13 , 12 , 15
// [10]:    1 , 2 ,<3>, 4 , 8 , 9 , 7 , 6 , 10 ,<5>, 11 , 14 , 13 , 12 , 15
// [11]:   {1},{2}, 3 , 4 , 8 , 9 , 7 , 6 , 10 , 5 , 11 , 14 , 13 , 12 , 15
// [12]:    1 , 2 , 3 ,{4},{8},{9},{7},{6},{10},{5}, 11 , 14 , 13 , 12 , 15
// [13]:    1 , 2 , 3 ,<4>, 8 , 9 ,<7>, 6 , 10 ,<5>, 11 , 14 , 13 , 12 , 15
// [14]:    1 , 2 , 3 , 4 ,<5>, 9 , 7 , 6 , 10 ,<8>, 11 , 14 , 13 , 12 , 15
// [15]:    1 , 2 , 3 ,{4}, 5 , 9 , 7 , 6 , 10 , 8 , 11 , 14 , 13 , 12 , 15
// [16]:    1 , 2 , 3 , 4 , 5 ,{9},{7},{6},{10},{8}, 11 , 14 , 13 , 12 , 15
// [17]:    1 , 2 , 3 , 4 , 5 ,<6>, 7 ,<9>, 10 ,<8>, 11 , 14 , 13 , 12 , 15
// [18]:    1 , 2 , 3 , 4 , 5 , 6 , 7 ,<8>, 10 ,<9>, 11 , 14 , 13 , 12 , 15
// [19]:    1 , 2 , 3 , 4 , 5 ,{6},{7}, 8 , 10 , 9 , 11 , 14 , 13 , 12 , 15
// [20]:    1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 ,{10},{9}, 11 , 14 , 13 , 12 , 15
// [21]:    1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 ,<9>,<10>, 11 , 14 , 13 , 12 , 15
// [22]:    1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 ,{14},{13},{12},{15}
// [23]:    1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 ,<13>,<15>, 12 ,<14>
// [24]:    1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 , 13 ,<12>,<15>, 14
// [25]:    1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 , 13 , 12 ,<14>,<15>
// [26]:    1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 ,{13},{12}, 14 , 15
// [27]:    1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 ,<12>,<13>, 14 , 15
// [28]:    1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 , 12 , 13 , 14 ,{15}

#endif