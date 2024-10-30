# 必须放在CMakeLists.txt文件的开头，用于指定所需的CMake的最低版本，此命令只能执行一次
cmake_minimum_required(VERSION 3.10)
# 该函数必须紧随cmake_minimum_required()函数之后，用于指定项目名称、版本、描述等信息
project(DataStructure)

# 该函数第一个参数接收地址，第二个参数（可自定名称）用于搜索地址后记录该地址下的.cpp源文件
aux_source_directory(Codes SrcMain)   # 搜索根目录下的源文件
# aux_source_directory(Codes/01-LinearList SrcLinearList)
# aux_source_directory(Codes/02-Tree SrcTree)
# aux_source_directory(Codes/03-Sorting SrcSorting)

# 该函数用于指定头文件的搜索路径，可以有多个路径
# include_directories()

# 该函数用于生成可执行文件，第一个参数指定文件名，往后的参数以空格间隔，传入先前导出的相关变量
add_executable(Main ${SrcMain})