#ifndef _LOAD_TEST_CASE_HPP_
#define _LOAD_TEST_CASE_HPP_

#include <vector>
#include <fstream>

std::vector<int> GetUnorderedIntList()
{
    std::vector<int> _list;

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

#endif