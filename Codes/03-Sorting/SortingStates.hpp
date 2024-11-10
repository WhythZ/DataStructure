#ifndef _SORTING_STATES_HPP_
#define _SORTING_STATES_HPP_

#include <vector>

//该结构标记列表的各状态中需要在打印时被突出显示的元素
struct State
{
    std::vector<int> list;         //存储该状态下的整个列表
    std::vector<size_t> tags1;     //该列表的哪些索引处值应当被突出显示
    std::vector<size_t> tags2;     //另一种不同形式的突出显示

    State(std::vector<int>);
    State(std::vector<int>, std::vector<size_t>);
    State(std::vector<int>, std::vector<size_t>, std::vector<size_t>);
};

State::State(std::vector<int> _list)
{
    list = _list;
    //默认不标记任何值
    tags1 = {};
    tags2 = {};
}

State::State(std::vector<int> _list, std::vector<size_t> _tags1)
{
    list = _list;
    tags1 = _tags1;
    //默认不标记任何值
    tags2 = {};
}

State::State(std::vector<int> _list, std::vector<size_t> _tags1, std::vector<size_t> _tags2)
{
    list = _list;
    tags1 = _tags1;
    tags2 = _tags2;
}

std::ostream& operator<<(std::ostream& _cout, const State& _state)
{
    //遍历打印每个状态下的列表状况
    for (size_t i = 0; i < _state.list.size(); i++)
    {
        //如果当前索引是被第一种标记标记的（即存在于tags1列表内）
        if (std::find(_state.tags1.begin(), _state.tags1.end(), i) != _state.tags1.end())
        {
            //使用特殊方法打印
            _cout << "<" << _state.list[i] << ">";
            if (i != _state.list.size() - 1) std::cout << ",";
            continue;
        }
        //若没被第一种标记，就检测第二种标记（若两种标记都有，那此处逻辑是只采用第一种标记）
        if (std::find(_state.tags2.begin(), _state.tags2.end(), i) != _state.tags2.end())
        {
            _cout << "{" << _state.list[i] << "}";
            if (i != _state.list.size() - 1) std::cout << ",";
            continue;
        }
        //否则正常打印
        _cout << " " << _state.list[i];
        if (i != _state.list.size() - 1) std::cout << " ,";
    }
    return _cout;
}

//该结构记录排序算法对列表进行排序时的中间各过程
class SortingStates
{
private:
    std::vector<State> states;    //存储列表的每个状态

public:
    size_t GetSize() const;
    void Print() const;

    void EmplaceBack(std::vector<int>);
    void EmplaceBack(std::vector<int>, std::vector<size_t>);
    void EmplaceBack(std::vector<int>, std::vector<size_t>, std::vector<size_t>);
};

size_t SortingStates::GetSize() const
{
    return states.size();
}

void SortingStates::Print() const
{
	for (size_t i = 0; i < states.size(); i++)
	{
		//打印列表状态的顺序索引
		std::cout << "[" << i << "]:\t";
        //打印各列表状态的具体内容
        std::cout << states[i] << "\n";
    }
}

void SortingStates::EmplaceBack(std::vector<int> _list)
{
    State _state(_list);
    states.emplace_back(_state);
}

void SortingStates::EmplaceBack(std::vector<int> _list, std::vector<size_t> _tags1)
{
    State _state(_list, _tags1);
    states.emplace_back(_state);
}

void SortingStates::EmplaceBack(std::vector<int> _list, std::vector<size_t> _tags1, std::vector<size_t> _tags2)
{
    State _state(_list, _tags1, _tags2);
    states.emplace_back(_state);
}

#endif