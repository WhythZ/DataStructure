#ifndef _L_STACK_HPP_
#define _L_STACK_HPP_

#include <iostream>
#include "02-SingleLinkedList.hpp"

//由于此栈基于写好的单向链表的栈实现（构造函数无需传入参数），所以不需写构造析构函数
template <typename T>
class LStack
{
private:
    SingleLinkedList<T> list; //使用单向链表实现栈

public:
    bool IsEmpty() const;     //返回栈是否为空栈
    T GetTop() const;         //返回栈顶部的元素值
    
    void Push(T const&);      //将元素推送到栈的顶端
    void Pop();               //将顶端元素删除（此处不返回栈顶值）
};

template <typename T>
bool LStack<T>::IsEmpty() const
{
    return list.IsEmpty();
}

template <typename T>
T LStack<T>::GetTop() const
{
    //若栈为空，则报错
    if (IsEmpty())
        throw std::runtime_error("ERROR: Stack Is Empty");
    //否则返回栈顶部元素，即头部元素
    return list.GetFront();
}

template <typename T>
void LStack<T>::Push(T const& _obj)
{
    //将元素推送到栈的头部
    return list.PushFront(_obj);
}

template <typename T>
void LStack<T>::Pop()
{
    //若栈为空，则报错
    if (IsEmpty())
        throw std::runtime_error("ERROR: Stack Is Empty");
    //否则删除栈的头部元素
    list.PopFront();
}

namespace Test_L_Stack
{
    void MainTest()
    {
        std::cout << "--------------------------------------------------" << "\n";

        //对象初始化测试
        LStack<int> stack;

        //IsEmpty函数测试
        std::cout << "##IsEmpty: " << stack.IsEmpty() << "\n";
        //##IsEmpty: 1
        
        //测试Push与GetTop函数
        stack.Push(11); std::cout << "**Push [11]" << "\n";
        std::cout << "##GetTop: " << stack.GetTop() << "\n";
        //##GetTop: 11
        stack.Push(22); std::cout << "**Push [22]" << "\n";
        std::cout << "##GetTop: " << stack.GetTop() << "\n";
        //##GetTop: 22

        stack.Push(33); std::cout << "**Push [33]" << "\n";
        std::cout << "##GetTop: " << stack.GetTop() << "\n";
        //##GetTop: 33
        
        //测试Pop函数
        stack.Pop(); std::cout << "**Pop" << "\n";
        std::cout << "##GetTop: " << stack.GetTop() << "\n";
        //##GetTop: 22
        stack.Pop(); std::cout << "**Pop" << "\n";
        std::cout << "##GetTop: " << stack.GetTop() << "\n";
        //##GetTop: 11

        //IsEmpty函数测试
        std::cout << "##IsEmpty: " << stack.IsEmpty() << "\n";
        //##IsEmpty: 0

        std::cout << "--------------------------------------------------" << "\n";
    }
}

#endif