#ifndef _BUBBLE_SORT_HPP_
#define _BUBBLE_SORT_HPP_

#include <vector>
#include "SortingStates.hpp"

// //基础的冒泡排序
// template <typename T>
// void BubbleSort(std::vector<T>& _list, SortingStates& _states)
// {
//     #pragma region StatesRecord
//     //记录初始状态
//     _states.EmplaceBack(_list);
//     #pragma endregion
//
//     //外层循环表示要冒(n-1)次泡泡
//     for (size_t i = 1; i < _list.size(); i++)
//     {
//         //内层循环表示要依次对比列表中相邻元素的大小，适时进行交换，共检测(n-1)次
//         for (size_t j = 0; j < _list.size() - 1; j++)
//         {
//             if (_list[j] > _list[j + 1])
//             {
//                 std::swap(_list[j], _list[j + 1]);
//
//                 #pragma region StatesRecord
//                 //记录该状态需要被标记的两个索引
//                 std::vector<size_t> _tags = { j, j + 1 };
//                 _states.EmplaceBack(_list, _tags);
//                 #pragma endregion
//             }
//         }
//     }
// }

// //优化后的冒泡排序
// template <typename T>
// void BubbleSort(std::vector<T>& _list, SortingStates& _states)
// {
//     #pragma region StatesRecord
//     //记录初始状态
//     _states.EmplaceBack(_list);
//     #pragma endregion
//
//     for (size_t i = 1; i < _list.size(); i++)
//     {
//         //当内部循环未发生std::swap时，则说明该列表已经排列有序
//         bool _isSorted = true;
//
//         //注意此处j<(size-i)，因为每次进行内部循环时，列表末尾已存在排序好的最大的(i-1)个元素
//         //此部分的元素无需对其进行前后的大小比较，故我们在原来的j<(size-1)的基础上再减去(i-1)
//         for (size_t j = 0; j < _list.size() - i; j++)
//         {
//             if (_list[j] > _list[j + 1])
//             {
//                 std::swap(_list[j], _list[j + 1]);
//                 //发生交换则说明需要继续下一轮检测
//                 _isSorted = false;
//
//                 #pragma region StatesRecord
//                 //记录该状态需要被标记的两个索引
//                 std::vector<size_t> _tags = { j, j + 1 };
//                 _states.EmplaceBack(_list, _tags);
//                 #pragma endregion
//             }
//         }
//
//         //已经有序的情况下，就无需继续剩下的循环了
//         if (_isSorted)
//             break;
//     }
// }

// ##LengthOfUnorderedList=15
// ##BubbleSort
// [0]:     14 , 2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [1]:    <2>,<14>, 5 , 12 , 3 , 9 , 13 , 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [2]:     2 ,<5>,<14>, 12 , 3 , 9 , 13 , 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [3]:     2 , 5 ,<12>,<14>, 3 , 9 , 13 , 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [4]:     2 , 5 , 12 ,<3>,<14>, 9 , 13 , 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [5]:     2 , 5 , 12 , 3 ,<9>,<14>, 13 , 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [6]:     2 , 5 , 12 , 3 , 9 ,<13>,<14>, 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [7]:     2 , 5 , 12 , 3 , 9 , 13 ,<1>,<14>, 10 , 15 , 8 , 6 , 7 , 4 , 11
// [8]:     2 , 5 , 12 , 3 , 9 , 13 , 1 ,<10>,<14>, 15 , 8 , 6 , 7 , 4 , 11
// [9]:     2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 14 ,<8>,<15>, 6 , 7 , 4 , 11
// [10]:    2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 14 , 8 ,<6>,<15>, 7 , 4 , 11
// [11]:    2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 14 , 8 , 6 ,<7>,<15>, 4 , 11
// [12]:    2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 14 , 8 , 6 , 7 ,<4>,<15>, 11
// [13]:    2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 14 , 8 , 6 , 7 , 4 ,<11>,<15>
// [14]:    2 , 5 ,<3>,<12>, 9 , 13 , 1 , 10 , 14 , 8 , 6 , 7 , 4 , 11 , 15
// [15]:    2 , 5 , 3 ,<9>,<12>, 13 , 1 , 10 , 14 , 8 , 6 , 7 , 4 , 11 , 15
// [16]:    2 , 5 , 3 , 9 , 12 ,<1>,<13>, 10 , 14 , 8 , 6 , 7 , 4 , 11 , 15
// [17]:    2 , 5 , 3 , 9 , 12 , 1 ,<10>,<13>, 14 , 8 , 6 , 7 , 4 , 11 , 15
// [18]:    2 , 5 , 3 , 9 , 12 , 1 , 10 , 13 ,<8>,<14>, 6 , 7 , 4 , 11 , 15
// [19]:    2 , 5 , 3 , 9 , 12 , 1 , 10 , 13 , 8 ,<6>,<14>, 7 , 4 , 11 , 15
// [20]:    2 , 5 , 3 , 9 , 12 , 1 , 10 , 13 , 8 , 6 ,<7>,<14>, 4 , 11 , 15
// [21]:    2 , 5 , 3 , 9 , 12 , 1 , 10 , 13 , 8 , 6 , 7 ,<4>,<14>, 11 , 15
// [22]:    2 , 5 , 3 , 9 , 12 , 1 , 10 , 13 , 8 , 6 , 7 , 4 ,<11>,<14>, 15
// [23]:    2 ,<3>,<5>, 9 , 12 , 1 , 10 , 13 , 8 , 6 , 7 , 4 , 11 , 14 , 15
// [24]:    2 , 3 , 5 , 9 ,<1>,<12>, 10 , 13 , 8 , 6 , 7 , 4 , 11 , 14 , 15
// [25]:    2 , 3 , 5 , 9 , 1 ,<10>,<12>, 13 , 8 , 6 , 7 , 4 , 11 , 14 , 15
// [26]:    2 , 3 , 5 , 9 , 1 , 10 , 12 ,<8>,<13>, 6 , 7 , 4 , 11 , 14 , 15
// [27]:    2 , 3 , 5 , 9 , 1 , 10 , 12 , 8 ,<6>,<13>, 7 , 4 , 11 , 14 , 15
// [28]:    2 , 3 , 5 , 9 , 1 , 10 , 12 , 8 , 6 ,<7>,<13>, 4 , 11 , 14 , 15
// [29]:    2 , 3 , 5 , 9 , 1 , 10 , 12 , 8 , 6 , 7 ,<4>,<13>, 11 , 14 , 15
// [30]:    2 , 3 , 5 , 9 , 1 , 10 , 12 , 8 , 6 , 7 , 4 ,<11>,<13>, 14 , 15
// [31]:    2 , 3 , 5 ,<1>,<9>, 10 , 12 , 8 , 6 , 7 , 4 , 11 , 13 , 14 , 15
// [32]:    2 , 3 , 5 , 1 , 9 , 10 ,<8>,<12>, 6 , 7 , 4 , 11 , 13 , 14 , 15
// [33]:    2 , 3 , 5 , 1 , 9 , 10 , 8 ,<6>,<12>, 7 , 4 , 11 , 13 , 14 , 15
// [34]:    2 , 3 , 5 , 1 , 9 , 10 , 8 , 6 ,<7>,<12>, 4 , 11 , 13 , 14 , 15
// [35]:    2 , 3 , 5 , 1 , 9 , 10 , 8 , 6 , 7 ,<4>,<12>, 11 , 13 , 14 , 15
// [36]:    2 , 3 , 5 , 1 , 9 , 10 , 8 , 6 , 7 , 4 ,<11>,<12>, 13 , 14 , 15
// [37]:    2 , 3 ,<1>,<5>, 9 , 10 , 8 , 6 , 7 , 4 , 11 , 12 , 13 , 14 , 15
// [38]:    2 , 3 , 1 , 5 , 9 ,<8>,<10>, 6 , 7 , 4 , 11 , 12 , 13 , 14 , 15
// [39]:    2 , 3 , 1 , 5 , 9 , 8 ,<6>,<10>, 7 , 4 , 11 , 12 , 13 , 14 , 15
// [40]:    2 , 3 , 1 , 5 , 9 , 8 , 6 ,<7>,<10>, 4 , 11 , 12 , 13 , 14 , 15
// [41]:    2 , 3 , 1 , 5 , 9 , 8 , 6 , 7 ,<4>,<10>, 11 , 12 , 13 , 14 , 15
// [42]:    2 ,<1>,<3>, 5 , 9 , 8 , 6 , 7 , 4 , 10 , 11 , 12 , 13 , 14 , 15
// [43]:    2 , 1 , 3 , 5 ,<8>,<9>, 6 , 7 , 4 , 10 , 11 , 12 , 13 , 14 , 15
// [44]:    2 , 1 , 3 , 5 , 8 ,<6>,<9>, 7 , 4 , 10 , 11 , 12 , 13 , 14 , 15
// [45]:    2 , 1 , 3 , 5 , 8 , 6 ,<7>,<9>, 4 , 10 , 11 , 12 , 13 , 14 , 15
// [46]:    2 , 1 , 3 , 5 , 8 , 6 , 7 ,<4>,<9>, 10 , 11 , 12 , 13 , 14 , 15
// [47]:   <1>,<2>, 3 , 5 , 8 , 6 , 7 , 4 , 9 , 10 , 11 , 12 , 13 , 14 , 15
// [48]:    1 , 2 , 3 , 5 ,<6>,<8>, 7 , 4 , 9 , 10 , 11 , 12 , 13 , 14 , 15
// [49]:    1 , 2 , 3 , 5 , 6 ,<7>,<8>, 4 , 9 , 10 , 11 , 12 , 13 , 14 , 15
// [50]:    1 , 2 , 3 , 5 , 6 , 7 ,<4>,<8>, 9 , 10 , 11 , 12 , 13 , 14 , 15
// [51]:    1 , 2 , 3 , 5 , 6 ,<4>,<7>, 8 , 9 , 10 , 11 , 12 , 13 , 14 , 15
// [52]:    1 , 2 , 3 , 5 ,<4>,<6>, 7 , 8 , 9 , 10 , 11 , 12 , 13 , 14 , 15
// [53]:    1 , 2 , 3 ,<4>,<5>, 6 , 7 , 8 , 9 , 10 , 11 , 12 , 13 , 14 , 15

//冒泡+下沉式的优化排序实现
template <typename T>
void BubbleSort(std::vector<T>& _list, SortingStates& _states)
{
    #pragma region StatesRecord
    //记录初始状态
    _states.EmplaceBack(_list);
    #pragma endregion

    //记录限定列表中间未排序部分的上下界的索引
    size_t _lower = 0;
    size_t _upper = _list.size() - 1;

    //死循环直到排序完成
    while (true)
    {
        //用此时的下界初始化，是为了应对比如{5,1,2,3,4}这种情况
        size_t _newUpper = _lower;
        //将最大值冒泡至列表顶端（右侧）
        for (size_t i = _lower; i < _upper; i++)
        {
            if (_list[i] > _list[i + 1])
            {
                std::swap(_list[i], _list[i + 1]);
                //最后一次发生std::swap的地方一定是新上界处，但不一定等于(_upper-1)
                _newUpper = i;

                #pragma region StatesRecord
                //记录两个被交换元素的索引
                std::vector<size_t> _tags = { i, i + 1 };
                _states.EmplaceBack(_list, _tags);
                #pragma endregion
            }
        }
        //简单地用(_upper-1)来刷新上界可能导致无意义的大小比较
        _upper = _newUpper;

        //同理，用此时的上界初始化
        size_t _newLower = _upper;
        //将最小值下沉至列表底端（左侧），注意此处使用的_upper是已经更新过的上界
        for (size_t i = _upper; i > _lower; i--)
        {
            if (_list[i - 1] > _list[i])
            {
                std::swap(_list[i - 1], _list[i]);
                _newLower = i;

                #pragma region StatesRecord
                //记录两个被交换元素的索引
                std::vector<size_t> _tags = { i, i + 1 };
                _states.EmplaceBack(_list, _tags);
                #pragma endregion
            }
        }
        //同理不能简单地用(_lower+1)更新下界
        _lower = _newLower;

        //比较被刷新过的上下界，若相等，则说明排序完成
        if (_lower == _upper)
            break;
    }
}

// ##LengthOfUnorderedList=15
// ##BubbleSort
// [0]:     14 , 2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [1]:    <2>,<14>, 5 , 12 , 3 , 9 , 13 , 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [2]:     2 ,<5>,<14>, 12 , 3 , 9 , 13 , 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [3]:     2 , 5 ,<12>,<14>, 3 , 9 , 13 , 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [4]:     2 , 5 , 12 ,<3>,<14>, 9 , 13 , 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [5]:     2 , 5 , 12 , 3 ,<9>,<14>, 13 , 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [6]:     2 , 5 , 12 , 3 , 9 ,<13>,<14>, 1 , 10 , 15 , 8 , 6 , 7 , 4 , 11
// [7]:     2 , 5 , 12 , 3 , 9 , 13 ,<1>,<14>, 10 , 15 , 8 , 6 , 7 , 4 , 11
// [8]:     2 , 5 , 12 , 3 , 9 , 13 , 1 ,<10>,<14>, 15 , 8 , 6 , 7 , 4 , 11
// [9]:     2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 14 ,<8>,<15>, 6 , 7 , 4 , 11
// [10]:    2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 14 , 8 ,<6>,<15>, 7 , 4 , 11
// [11]:    2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 14 , 8 , 6 ,<7>,<15>, 4 , 11
// [12]:    2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 14 , 8 , 6 , 7 ,<4>,<15>, 11
// [13]:    2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 14 , 8 , 6 , 7 , 4 ,<11>,<15>
// [14]:    2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 14 , 8 , 6 , 4 ,<7>,<11>, 15
// [15]:    2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 14 , 8 , 4 ,<6>,<7>, 11 , 15
// [16]:    2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 14 , 4 ,<8>,<6>, 7 , 11 , 15
// [17]:    2 , 5 , 12 , 3 , 9 , 13 , 1 , 10 , 4 ,<14>,<8>, 6 , 7 , 11 , 15
// [18]:    2 , 5 , 12 , 3 , 9 , 13 , 1 , 4 ,<10>,<14>, 8 , 6 , 7 , 11 , 15
// [19]:    2 , 5 , 12 , 3 , 9 , 1 ,<13>,<4>, 10 , 14 , 8 , 6 , 7 , 11 , 15
// [20]:    2 , 5 , 12 , 3 , 1 ,<9>,<13>, 4 , 10 , 14 , 8 , 6 , 7 , 11 , 15
// [21]:    2 , 5 , 12 , 1 ,<3>,<9>, 13 , 4 , 10 , 14 , 8 , 6 , 7 , 11 , 15
// [22]:    2 , 5 , 1 ,<12>,<3>, 9 , 13 , 4 , 10 , 14 , 8 , 6 , 7 , 11 , 15
// [23]:    2 , 1 ,<5>,<12>, 3 , 9 , 13 , 4 , 10 , 14 , 8 , 6 , 7 , 11 , 15
// [24]:    1 ,<2>,<5>, 12 , 3 , 9 , 13 , 4 , 10 , 14 , 8 , 6 , 7 , 11 , 15
// [25]:    1 , 2 , 5 ,<3>,<12>, 9 , 13 , 4 , 10 , 14 , 8 , 6 , 7 , 11 , 15
// [26]:    1 , 2 , 5 , 3 ,<9>,<12>, 13 , 4 , 10 , 14 , 8 , 6 , 7 , 11 , 15
// [27]:    1 , 2 , 5 , 3 , 9 , 12 ,<4>,<13>, 10 , 14 , 8 , 6 , 7 , 11 , 15
// [28]:    1 , 2 , 5 , 3 , 9 , 12 , 4 ,<10>,<13>, 14 , 8 , 6 , 7 , 11 , 15
// [29]:    1 , 2 , 5 , 3 , 9 , 12 , 4 , 10 , 13 ,<8>,<14>, 6 , 7 , 11 , 15
// [30]:    1 , 2 , 5 , 3 , 9 , 12 , 4 , 10 , 13 , 8 ,<6>,<14>, 7 , 11 , 15
// [31]:    1 , 2 , 5 , 3 , 9 , 12 , 4 , 10 , 13 , 8 , 6 ,<7>,<14>, 11 , 15
// [32]:    1 , 2 , 5 , 3 , 9 , 12 , 4 , 10 , 13 , 8 , 6 , 7 ,<11>,<14>, 15
// [33]:    1 , 2 , 5 , 3 , 9 , 12 , 4 , 10 , 13 , 6 ,<8>,<7>, 11 , 14 , 15
// [34]:    1 , 2 , 5 , 3 , 9 , 12 , 4 , 10 , 6 ,<13>,<8>, 7 , 11 , 14 , 15
// [35]:    1 , 2 , 5 , 3 , 9 , 12 , 4 , 6 ,<10>,<13>, 8 , 7 , 11 , 14 , 15
// [36]:    1 , 2 , 5 , 3 , 9 , 4 ,<12>,<6>, 10 , 13 , 8 , 7 , 11 , 14 , 15
// [37]:    1 , 2 , 5 , 3 , 4 ,<9>,<12>, 6 , 10 , 13 , 8 , 7 , 11 , 14 , 15
// [38]:    1 , 2 , 3 ,<5>,<4>, 9 , 12 , 6 , 10 , 13 , 8 , 7 , 11 , 14 , 15
// [39]:    1 , 2 , 3 ,<4>,<5>, 9 , 12 , 6 , 10 , 13 , 8 , 7 , 11 , 14 , 15
// [40]:    1 , 2 , 3 , 4 , 5 , 9 ,<6>,<12>, 10 , 13 , 8 , 7 , 11 , 14 , 15
// [41]:    1 , 2 , 3 , 4 , 5 , 9 , 6 ,<10>,<12>, 13 , 8 , 7 , 11 , 14 , 15
// [42]:    1 , 2 , 3 , 4 , 5 , 9 , 6 , 10 , 12 ,<8>,<13>, 7 , 11 , 14 , 15
// [43]:    1 , 2 , 3 , 4 , 5 , 9 , 6 , 10 , 12 , 8 ,<7>,<13>, 11 , 14 , 15
// [44]:    1 , 2 , 3 , 4 , 5 , 9 , 6 , 10 , 12 , 8 , 7 ,<11>,<13>, 14 , 15
// [45]:    1 , 2 , 3 , 4 , 5 , 9 , 6 , 10 , 12 , 7 ,<8>,<11>, 13 , 14 , 15
// [46]:    1 , 2 , 3 , 4 , 5 , 9 , 6 , 10 , 7 ,<12>,<8>, 11 , 13 , 14 , 15
// [47]:    1 , 2 , 3 , 4 , 5 , 9 , 6 , 7 ,<10>,<12>, 8 , 11 , 13 , 14 , 15
// [48]:    1 , 2 , 3 , 4 , 5 , 6 ,<9>,<7>, 10 , 12 , 8 , 11 , 13 , 14 , 15
// [49]:    1 , 2 , 3 , 4 , 5 , 6 ,<7>,<9>, 10 , 12 , 8 , 11 , 13 , 14 , 15
// [50]:    1 , 2 , 3 , 4 , 5 , 6 , 7 , 9 , 10 ,<8>,<12>, 11 , 13 , 14 , 15
// [51]:    1 , 2 , 3 , 4 , 5 , 6 , 7 , 9 , 10 , 8 ,<11>,<12>, 13 , 14 , 15
// [52]:    1 , 2 , 3 , 4 , 5 , 6 , 7 , 9 , 8 ,<10>,<11>, 12 , 13 , 14 , 15
// [53]:    1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 ,<9>,<10>, 11 , 12 , 13 , 14 , 15

#endif