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
	static SortingManager* instance;                                   //该类的单例
	std::vector<int> srcList;                                          //存储原始的乱序列表

public:
	static SortingManager* GetInstance();                              //获取类单例
	void Run();                                                        //运行可视化程序

private:
	SortingManager();
	~SortingManager() = default;
	SortingManager(const SortingManager&) = delete;
	SortingManager& operator=(const SortingManager&) = delete;
	
	void LoadTestCase(std::string);                                    //加载乱序列表测试用例文件

	//使用传入的排序算法对列表进行排序测试
	void TestWith(std::function<void(std::vector<int>&, std::vector<std::vector<int>>&)>, SortType);
};

SortingManager* SortingManager::instance = nullptr;

SortingManager* SortingManager::GetInstance()
{
	if (!instance)
		instance = new SortingManager();
	return instance;
}

void SortingManager::Run()
{
	TestWith(SelectionSort<int>, SortType::Selection);
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

void SortingManager::TestWith(std::function<void(std::vector<int>&, std::vector<std::vector<int>>&)> _algorithm, SortType _tag)
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
		std::cout << ">>SelectionSort=O(" << _states.size() - 1 << ")\n";
		break;
	case SortType::Insertion:
		std::cout << ">>InsertionSort=O(" << _states.size() - 1 << ")\n";
		break;
	case SortType::Bubble:
		std::cout << ">>BubbleSort=O(" << _states.size() - 1 << ")\n";
		break;
	case SortType::Heap:
		std::cout << ">>HeapSort=O(" << _states.size() - 1 << ")\n";
		break;
	case SortType::Merge:
		std::cout << ">>MergeSort=O(" << _states.size() - 1 << ")\n";
		break;
	case SortType::Quick:
		std::cout << ">>QuickSort=O(" << _states.size() - 1 << ")\n";
		break;
	case SortType::Bucket:
		std::cout << ">>BucketSort=O(" << _states.size() - 1 << ")\n";
		break;
	case SortType::Radix:
		std::cout << ">>RadixSort=O(" << _states.size() - 1 << ")\n";
		break;
	default:
		break;
	}

	//外层循环遍历排序算法执行过程中的各个状态
	size_t _counter = 0;
	for (std::vector<std::vector<int>>::iterator _it1 = _states.begin(); _it1 != _states.end(); _it1++)
	{
		//打印状态顺序索引
		std::cout << "[" << _counter << "]: ";

		//内层循环遍历打印每个状态下的列表状况
		for (std::vector<int>::iterator _it2 = _it1->begin(); _it2 != _it1->end(); _it2++)
		{
			std::cout << *_it2 << ",";
		}

		_counter++;
		std::cout << "\n";
	}

	std::cout << "--------------------------------------------------\n";
}

#endif