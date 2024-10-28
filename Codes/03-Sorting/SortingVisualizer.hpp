#ifndef _SORTING_VISUALIZER_HPP_
#define _SORTING_VISUALIZER_HPP_

#include <vector>
#include <fstream>
#include <functional>

// #include "SDL.h"
#include "../../Libs/SDL2/include/SDL.h"

#include "01-SelectionSort.hpp"
#include "02-InsertionSort.hpp"
#include "03-BubbleSort.hpp"
#include "04-HeapSort.hpp"
#include "05-MergeSort.hpp"
#include "06-QuickSort.hpp"
#include "07-BucketSort.hpp"
#include "08-RadixSort.hpp"

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

class SortingVisualizer
{
private:
	static SortingVisualizer* instance;           //该类的单例
	std::vector<int> unorderedList;               //存储原始的乱序列表

public:
	static SortingVisualizer* GetInstance();      //获取类单例
	void Run();                                   //运行可视化程序

private:
	SortingVisualizer();
	~SortingVisualizer();
	SortingVisualizer(const SortingVisualizer&) = delete;
	SortingVisualizer& operator=(const SortingVisualizer&) = delete;
	
	void InitAssert(bool, std::string);           //初始化断言
	bool LoadTestCase(std::string);               //加载乱序列表测试用例文件

	//使用传入的排序算法对列表进行排序测试
	void TestWith(std::function<void(std::vector<int>&)>, SortType);
};

SortingVisualizer* SortingVisualizer::instance = nullptr;

SortingVisualizer* SortingVisualizer::GetInstance()
{
	if (!instance)
		instance = new SortingVisualizer();
	return instance;
}

void SortingVisualizer::Run()
{
	TestWith(SelectionSort<int>, SortType::Selection);
}

SortingVisualizer::SortingVisualizer()
{
	//加载测试案例文件中的整数列表
	InitAssert(LoadTestCase("../Codes/03-Sorting/IntTestCase.csv"), "ERROR: File \"IntTestCase.csv\" Not Found!");
}

SortingVisualizer::~SortingVisualizer()
{

}

void SortingVisualizer::InitAssert(bool _flag, std::string _msg)
{
	if (!_flag)
		throw std::runtime_error(_msg);
}

bool SortingVisualizer::LoadTestCase(std::string _path)
{
	//加载路径下的文件
	std::ifstream _file(_path);
	//检查是否成功加载
	if (!_file.good())
		return false;

	//通过循环来遍历每行内容；getline函数第一参数位接收被读取的文件，第二参数位是存放读取的数据的对象，第三参数位以逗号为分隔符
	std::string _gridBuf;
	while (std::getline(_file, _gridBuf, ','))
	{
		unorderedList.emplace_back(stoi(_gridBuf));
	}

	//关掉文件
	_file.close();
	return true;
}

void SortingVisualizer::TestWith(std::function<void(std::vector<int>&)> _algorithm, SortType _tag)
{
	switch (_tag)
	{
	case SortType::Selection:
		std::cout<<">>Selection Sort\n";
		break;
	case SortType::Insertion:
		std::cout<<">>Insertion Sort\n";
		break;
	case SortType::Bubble:
		std::cout<<">>Bubble Sort\n";
		break;
	case SortType::Heap:
		std::cout<<">>Heap Sort\n";
		break;
	case SortType::Merge:
		std::cout<<">>Merge Sort\n";
		break;
	case SortType::Quick:
		std::cout<<">>Quick Sort\n";
		break;
	case SortType::Bucket:
		std::cout<<">>Bucket Sort\n";
		break;
	case SortType::Radix:
		std::cout<<">>Radix Sort\n";
		break;
	default:
		break;
	}

	//复制一份原始乱序列表
	std::vector<int> _copy = unorderedList;
	
	//打印原始的乱序状态
	std::cout << "Before=[";
	for (std::vector<int>::iterator _it = _copy.begin(); _it != _copy.end(); _it++)
	{
		std::cout << *_it << ",";
	}
	std::cout << "]\n";

	//打印排序后状态
	_algorithm(_copy);
	std::cout << "Sorted=[";
	for (std::vector<int>::iterator _it = _copy.begin(); _it != _copy.end(); _it++)
	{
		std::cout << *_it << ",";
	}
	std::cout << "]\n";
}

#endif