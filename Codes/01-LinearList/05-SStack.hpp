#ifndef _S_STACK_HPP_
#define _S_STACK_HPP_

#include <iostream>
#include <algorithm>

template <typename T>
class SStack
{
private:
    int stackSize;               //栈当前占用的大小
    int arrayCapacity;           //栈内置数组的（初始）容量
    T* array;                    //使用C++内置数组实现栈

public:
    SStack(int = 10);            //构造函数
    ~SStack();                   //析构函数

    bool IsEmpty() const;        //返回栈是否为空栈
    T GetTop() const;            //返回栈顶部的元素值
    int GetCapacity() const;     //用于测试

    void Push(T const&);         //将元素推送到栈的顶端
    void Pop();                  //删除栈的顶端元素

private:
    void DoubleTheCapacity();    //对栈的数组进行扩容 
};

template <typename T>
SStack<T>::SStack(int _capacity)
{
    stackSize = 0;
    arrayCapacity = std::max(1, _capacity);
    array = new T[arrayCapacity];
}

template <typename T>
SStack<T>::~SStack()
{
    delete[] array;
}

template <typename T>
bool SStack<T>::IsEmpty() const
{
    //栈的大小为0则为空
    return (stackSize == 0);
}

template <typename T>
T SStack<T>::GetTop() const
{
    if (IsEmpty())
        throw std::invalid_argument("ERROR: SStack Is Empty Calling {T SStack<T>::GetTop() const}");
    return array[stackSize - 1];
}

template <typename T>
int SStack<T>::GetCapacity() const
{
    return arrayCapacity;
}

template <typename T>
void SStack<T>::Push(T const& _obj)
{
    //如果栈的大小即将超过数组的容量，则需扩容
    if (stackSize == arrayCapacity)
    {
        //一般是扩容两倍
        DoubleTheCapacity();
    }
    //添加新元素到内置数组的末尾
    array[stackSize] = _obj;
    //递增stackSize大小以便访问
    ++stackSize;
}

template <typename T>
void SStack<T>::Pop()
{
    if (IsEmpty())
        throw std::invalid_argument("ERROR: SStack Is Empty Calling {void SStack<T>::Pop()}");
    //将栈大小递减就相当于删除了尾部元素，因为越界的元素无法访问
    --stackSize;
}

template <typename T>
void SStack<T>::DoubleTheCapacity()
{
    //临时的指针指向新开辟的扩容数组
    T* _temp = new T[2 * arrayCapacity];
    //将原数组内的数转移到新数组内
    for (int i = 0; i < arrayCapacity; i++)
    {
        _temp[i] = array[i];
    }
    //销毁原数组占用的内存
    delete[] array;
    //将栈的数组指针指向新数组，无需管此作用域内的临时指针
    array = _temp;
    //登记一下新的数组容量
    arrayCapacity *= 2;
}

namespace Test_S_Stack
{
    void MainTest()
    {
        std::cout << "--------------------------------------------------\n";

        //对象初始化测试
        SStack<int> stack(2);

        //IsEmpty函数测试
        std::cout << "##IsEmpty: " << stack.IsEmpty() << "\n";
        //##IsEmpty: 1

        //Push、Pop、GetTop函数测试
        stack.Push(11); std::cout << "**Push(11)\n";
        std::cout << "##GetTop: " << stack.GetTop() << "\n";
        //##GetTop: 11
        stack.Push(22); std::cout << "**Push(22)\n";
        std::cout << "##GetTop: " << stack.GetTop() << "\n";
        //##GetTop: 22
        stack.Pop(); std::cout << "**Pop\n";
        std::cout << "##GetTop: " << stack.GetTop() << "\n";
        //##GetTop: 11

        //IsEmpty函数测试
        std::cout << "##IsEmpty: " << stack.IsEmpty() << "\n";
        //##IsEmpty: 0

        //扩容测试
        stack.Push(22); std::cout << "**Push(22)\n";
        stack.Push(33); std::cout << "**Push(33)\n";
        std::cout << "##GetTop: " << stack.GetTop() << "\n";
        //##GetTop: 33
        std::cout << "##GetCapacity: " << stack.GetCapacity() << "\n";
        //##GetCapacity: 4

        std::cout << "--------------------------------------------------\n";
    }
}

#endif