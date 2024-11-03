#ifndef _BUBBLE_SORT_HPP_
#define _BUBBLE_SORT_HPP_

#include <vector>

// //基础的冒泡排序：
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

// //优化后的冒泡排序：
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

#endif