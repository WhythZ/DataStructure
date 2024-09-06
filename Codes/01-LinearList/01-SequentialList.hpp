#ifndef _SEQUENTIAL_LIST_HPP_
#define _SEQUENTIAL_LIST_HPP_

//包含错误抛出相关的头文件<stdexcept>
#include <iostream>

template <typename T>
class SequentialList
{
private:
	int capacity = 0;           //数组最大容量
    T* head = nullptr;          //数组首地址
    int length = 0;             //数组当前长度

public:
    SequentialList(int);        //构造函数
    ~SequentialList();          //析构函数

    bool IsEmpty() const;       //返回数组是否为空
    T GetElem(int) const;       //用索引读取对应元素（只读）
    int Find(const T&) const;   //返回查找对象的索引
    int GetCapacity() const;    //获取数组最大容量
    int GetLength() const;      //获取数组长度

    bool Insert(const T&, int); //插入元素到指定位置
    void PushBack(const T&);    //插入元素到数组尾部
    void Erase(int);            //删除指定位置的元素
    void PopBack();             //删除数组尾部元素
    void Clear();               //清空数组，但不销毁
};

template <typename T>
SequentialList<T>::SequentialList(int _capacity)
{
    //初始化数组容量
    capacity = _capacity;
    //为首地址分配堆区内存
    head = new T[capacity];
    //创建失败则退出
    if (!head)
    {
	    //中断程序并返回某错误码
	    throw std::runtime_error("ERROR: Contruct Failed");
    }
    //初始化长度为零
    length = 0;
}

template <typename T>
SequentialList<T>::~SequentialList()
{
    if (head)
        delete[] head;
}

template <typename T>
bool SequentialList<T>::IsEmpty() const
{
    return (length == 0);
}

template <typename T>
T SequentialList<T>::GetElem(int _idx) const
{
    //排除越界索引
    if (_idx < 0 || _idx >= length)
        throw std::runtime_error("ERROR: Illegal Access");
    return head[_idx];
}

template <typename T>
int SequentialList<T>::Find(const T& _obj) const
{
    for (int i = 0; i < length; i++)
    {
        if (head[i] == _obj)
            return i;
    }
    //找不到那就返回-1
    return -1;
}

template <typename T>
int SequentialList<T>::GetCapacity() const
{
    return capacity;
}

template <typename T>
int SequentialList<T>::GetLength() const
{
    return length;
}

template <typename T>
bool SequentialList<T>::Insert(const T& _obj, int _idx)
{
    //数组满了无法插入
    if (capacity == length)
        return false;
    //排除越界索引，其中(_idx == length)意味着将元素插入到列表末尾
    if (_idx < 0 || _idx > length)
        return false;
    //插入位置及其后的元素被挤后移
    if (_idx < length)
    {
        for (int i = length; i > _idx; i--)
        {
            head[i] = head[i - 1];
        }
    }
    //正式插入元素并递增数组长度
    head[_idx] = _obj;
    length++;
    return true;
}

template <typename T>
void SequentialList<T>::PushBack(const T& _obj)
{
    //插入数组的尾部
    Insert(_obj, length);
}

template <typename T>
void SequentialList<T>::Erase(int _idx)
{
    //排除越界索引
    if (_idx < 0 || _idx >= length)
        throw std::runtime_error("ERROR: Illegal Access");
    for (int i = _idx; i < length - 1; i++)
        head[i] = head[i + 1];
    //长度递减，这样原本的最后一个元素就是越界而无法访问的了，不用管
    length--;
}

template <typename T>
void SequentialList<T>::PopBack()
{
    //删除尾部元素
    Erase(length);
}

template <typename T>
void SequentialList<T>::Clear()
{
    //长度设置为零，超出长度的索引无法使用GetElem函数成功检索，故而原来那些位置上的元素无需额外操作
    length = 0;
}

namespace Test_Sequential_List
{
    class Item
    {
    public:
        int id = 0;
        Item() = default;
        Item(int _id) :id(_id) {}
    };

    void PrintListInt(SequentialList<int>& _list)
    {
        for (int i = 0; i < _list.GetLength(); i++)
        {
            std::cout << _list.GetElem(i) << " ";
        }
        std::cout << "\n";
    }

    void MainTest()
    {
        std::cout << "--------------------------------------------------" << "\n";

        //测试构造函数
        SequentialList<Item> itemList(10);
        SequentialList<int> intList(10);

        //测试GetCapacity与GetLength函数
        std::cout << intList.GetCapacity() << "\n";
        //10
        std::cout << intList.GetLength() << "\n";
        //0

        //测试Insert函数
        int a = 0, b = 11, c = 22, d = 33, x = 99;
        intList.Insert(a, 0);
        intList.Insert(b, 1);
        intList.Insert(c, 2);
        intList.Insert(d, 3);
        PrintListInt(intList);
        //0 11 22 33
        intList.Insert(x, 4);
        PrintListInt(intList);
        //0 11 22 33 99
        intList.Insert(x, 0);
        PrintListInt(intList);
        //99 0 11 22 33 99
        intList.Insert(x, 2);
        PrintListInt(intList);
        //99 0 99 11 22 33 99

        //测试Erase函数
        intList.Erase(2);
        PrintListInt(intList);
        //99 0 11 22 33 99
        intList.Erase(0);
        PrintListInt(intList);
        //0 11 22 33 99
        intList.Erase(4);
        PrintListInt(intList);
        //0 11 22 33

        //测试Find函数
        std::cout << intList.Find(22) << "\n";
        //2

        //测试Clear函数与IsEmpty函数
        std::cout << intList.IsEmpty() << "\n";
        //0
        intList.Clear();
        PrintListInt(intList);
        //输出结果为空白
        std::cout << intList.IsEmpty() << "\n";
        //1

        std::cout << "--------------------------------------------------" << "\n";
    }
}

#endif