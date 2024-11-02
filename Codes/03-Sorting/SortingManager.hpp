#ifndef _SORTING_MANAGER_HPP_
#define _SORTING_MANAGER_HPP_

#include <vector>
#include <fstream>
#include <functional>

#include "01-SelectionSort.hpp"
#include "02-InsertionSort.hpp"
#include "03-BubbleSort.hpp"
#include "04-HeapSort.hpp"
#include "05-MergeSort.hpp"
#include "06-QuickSort.hpp"
#include "07-BucketSort.hpp"
#include "08-RadixSort.hpp"

//用于标记各种排序方法的枚举类
enum class SortType
{
	Selection = 0,
	Insertion = 1,
	Bubble = 2,
	Heap = 3,
	Merge = 4,
	Quick = 5,
	Bucket = 6,
	Radix = 7
};

class SortingManager
{
private:
	static SortingManager* instance;            //该类的单例
	std::vector<int> srcList;                   //存储原始的乱序列表

public:
	static SortingManager* GetInstance();       //获取类单例
	void Run(SortType);                         //运行排序算法

private:
	SortingManager();
	~SortingManager() = default;
	SortingManager(const SortingManager&) = delete;
	SortingManager& operator=(const SortingManager&) = delete;
	
	void LoadTestCase(std::string);             //加载乱序列表测试用例文件

	//使用传入的排序算法对列表进行排序测试
	void TestWith(std::function<void(std::vector<int>&, std::vector<std::vector<int>>&)>, SortType) const;
	//对比列表的相邻两个状态，找出被交换的两个元素索引（此函数的复杂度的确高，但是可以和排序算法本身逻辑分离）
	std::tuple<size_t, size_t> GetComparison(const std::vector<int>&, const std::vector<int>&) const;
};

SortingManager* SortingManager::instance = nullptr;

SortingManager* SortingManager::GetInstance()
{
	if (!instance)
		instance = new SortingManager();
	return instance;
}

void SortingManager::Run(SortType _type)
{
	switch (_type)
	{
	case SortType::Selection:
		TestWith(SelectionSort<int>, _type);
		break;
	case SortType::Insertion:
		TestWith(InsertionSort<int>, _type);
		break;
	case SortType::Bubble:
		TestWith(BubbleSort<int>, _type);
		break;
	case SortType::Heap:
		TestWith(HeapSort<int>, _type);
		break;
	case SortType::Merge:
		TestWith(MergeSort<int>, _type);
		break;
	case SortType::Quick:
		TestWith(QuickSort<int>, _type);
		break;
	case SortType::Bucket:
		TestWith(BucketSort<int>, _type);
		break;
	case SortType::Radix:
		TestWith(RadixSort<int>, _type);
		break;
	default:
		break;
	}
}

SortingManager::SortingManager()
{
	//加载测试案例文件中的整数列表
	LoadTestCase("../Codes/03-Sorting/IntTestCase.csv");
}

void SortingManager::LoadTestCase(std::string _path)
{
	//加载路径下的文件
	std::ifstream _file(_path);
	//检查是否成功加载
	if (!_file.good())
		throw std::runtime_error("ERROR: File \"IntTestCase.csv\" Not Found!");

	//通过循环来遍历每行内容；getline函数第一参数位接收被读取的文件，第二参数位是存放读取的数据的对象，第三参数位以逗号为分隔符
	std::string _gridBuf;
	while (std::getline(_file, _gridBuf, ','))
	{
		srcList.emplace_back(stoi(_gridBuf));
	}

	//关掉文件
	_file.close();
}

void SortingManager::TestWith(std::function<void(std::vector<int>&, std::vector<std::vector<int>>&)> _algorithm, SortType _tag) const
{
	//复制一份原始乱序列表并对其进行排序
	std::vector<int> _copy = srcList;
	//将排序过程存储在容器中，该容器记录了一个存储int的线性表从unordered到ordered的全过程
	std::vector<std::vector<int>> _states;
	_algorithm(_copy, _states);

	std::cout << "--------------------------------------------------\n";
	std::cout << "##LengthOfUnorderedList=" << srcList.size() << "\n";
	
	//打印算法名称与复杂度
	switch (_tag)
	{
	case SortType::Selection:
		std::cout << "##SelectionSort=O(" << _states.size() - 1 << ")\n";
		break;
	case SortType::Insertion:
		std::cout << "##InsertionSort=O(" << _states.size() - 1 << ")\n";
		break;
	case SortType::Bubble:
		std::cout << "##BubbleSort=O(" << _states.size() - 1 << ")\n";
		break;
	case SortType::Heap:
		std::cout << "##HeapSort=O(" << _states.size() - 1 << ")\n";
		break;
	case SortType::Merge:
		std::cout << "##MergeSort=O(" << _states.size() - 1 << ")\n";
		break;
	case SortType::Quick:
		std::cout << "##QuickSort=O(" << _states.size() - 1 << ")\n";
		break;
	case SortType::Bucket:
		std::cout << "##BucketSort=O(" << _states.size() - 1 << ")\n";
		break;
	case SortType::Radix:
		std::cout << "##RadixSort=O(" << _states.size() - 1 << ")\n";
		break;
	default:
		break;
	}

	//在外层的列表状态遍历过程中存储当前状态和前一个状态的差异（即一个Swap操作造成的差异）
	size_t _idx1 = 0, _idx2 = 0;
	for (size_t i = 0; i < _states.size(); i++)
	{
		//打印状态顺序索引
		std::cout << "[" << i << "]:\t";

		//获取和前一个列表状态的差异位置索引
		if (i > 0)
		{
			_idx1 = std::get<0>(GetComparison(_states[i], _states[i - 1]));
			_idx2 = std::get<1>(GetComparison(_states[i], _states[i - 1]));
		}

		//内层循环遍历打印每个状态下的列表状况
		for (size_t j = 0; j < _states[i].size(); j++)
		{
			if ((j == _idx1 || j == _idx2) && _idx1 != _idx2)
			{
				std::cout << "{" << _states[i][j] << "},";
				continue;
			}
			std::cout << _states[i][j] << ",";
		}

		std::cout << "\n";
	}

	std::cout << "--------------------------------------------------\n";
}

std::tuple<size_t, size_t> SortingManager::GetComparison(const std::vector<int>& _list1, const std::vector<int>& _list2) const
{
	//使用vector重载的==运算符进行比较（会考虑元素的顺序）
	if (_list1 == _list2)
		throw std::runtime_error("ERROR: Two states of the list are equal");
	
	if (_list1.size() != _list2.size())
		throw std::runtime_error("ERROR: Size of the two states of the list are unequal");

	//记录两个差异位置的索引
	size_t _idx1, _idx2;
	//记录两列表共有几个相同索引位置处的元素值不同，若超过了两个则说明两个状态的差异并不是单个Swap操作造成的
	size_t _diffCounter = 0;

	//对比两个列表相同索引位置的值
	for (size_t i = 0; i < _list1.size(); i++)
	{
		if (_list1[i] != _list2[i])
		{
			_diffCounter++;
			if (_diffCounter == 1)
				_idx1 = i;
			else if (_diffCounter == 2)
				_idx2 = i;
			else if (_diffCounter > 2)
				throw std::runtime_error("ERROR: More than one \"Swap\" operation between the two list states");
		}
	}

	return std::tuple<size_t, size_t>(_idx1, _idx2);
}

#endif