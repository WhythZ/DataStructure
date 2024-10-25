#ifndef _INT_SORTING_VISUALIZER_HPP_
#define _INT_SORTING_VISUALIZER_HPP_

#include <vector>
#include <fstream>

#include "01-SelectionSort.hpp"
#include "02-InsertionSort.hpp"
#include "03-BubbleSort.hpp"
#include "04-HeapSort.hpp"
#include "05-MergeSort.hpp"
#include "06-QuickSort.hpp"
#include "07-BucketSort.hpp"
#include "08-RadixSort.hpp"

class IntSortingVisualizer
{
private:
	static IntSortingVisualizer* instance;
	std::vector<int> unorderedList;

public:
	static IntSortingVisualizer* GetInstance();
	void Run();

private:
	IntSortingVisualizer();
	~IntSortingVisualizer();
	IntSortingVisualizer(const IntSortingVisualizer&) = delete;
	IntSortingVisualizer& operator=(const IntSortingVisualizer&) = delete;
	
	void InitAssert(bool, std::string);
	bool LoadTestCase(std::string);
};

IntSortingVisualizer* IntSortingVisualizer::instance = nullptr;

IntSortingVisualizer* IntSortingVisualizer::GetInstance()
{
	if (!instance)
		instance = new IntSortingVisualizer();
	return instance;
}

void IntSortingVisualizer::Run()
{
	std::vector<int> _copy1 = unorderedList;
	SelectionSort<int>(_copy1);
	for (int i = 0; i < unorderedList.size();i++) { std::cout << _copy1[i] << ","; }
	std::cout << "\n";
}

IntSortingVisualizer::IntSortingVisualizer()
{
	//加载测试案例文件中的整数列表
	InitAssert(LoadTestCase("03-Sorting/IntTestCase.csv"), "ERROR: File \"IntTestCase.csv\" Not Found!");
}

IntSortingVisualizer::~IntSortingVisualizer()
{

}

void IntSortingVisualizer::InitAssert(bool _flag, std::string _msg)
{
	if (!_flag)
		std::cout << _msg << "\n";
}

bool IntSortingVisualizer::LoadTestCase(std::string _path)
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

#endif