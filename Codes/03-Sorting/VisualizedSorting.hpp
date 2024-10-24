#ifndef _VISUALIZED_SORTING_HPP_
#define _VISUALIZED_SORTING_HPP_

#include <vector>
#include <fstream>
#include "03-Sorting/01-SelectionSort.hpp"
#include "03-Sorting/02-InsertionSort.hpp"
#include "03-Sorting/03-BubbleSort.hpp"
#include "03-Sorting/04-HeapSort.hpp"
#include "03-Sorting/05-MergeSort.hpp"
#include "03-Sorting/06-QuickSort.hpp"
#include "03-Sorting/07-BucketSort.hpp"
#include "03-Sorting/08-RadixSort.hpp"

namespace Test_Visualized_Sorting
{
	//用于存储从文件中读取的乱序列表
	std::vector<int> unorderedList;

	std::vector<int> GetUnorderedIntList()
	{
		//加载路径下的文件
		std::ifstream _file("GameData/test.CSV");
		//检查是否成功加载
		if (!_file.good())
		{
			std::cout << "CSV File Note Found" << std::endl;
			return;
		}

		//CSV需要逐行读取，该变量在循环中存储每一行的内容
		std::string lineBuf;
	}
}

#endif