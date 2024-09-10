#ifndef _L_QUEUE_HPP_
#define _L_QUEUE_HPP_

#include <iostream>
#include "02-SingleLinkedList.hpp"

template <typename T>
class LQueue
{
private:
    SingleLinkedList<T> list;  //单向链表内核

public:
    bool IsEmpty() const;      //判断是否为空
    T GetFront() const;        //获取下一个将被取出队列的元素

    void Push(T const&);       //将新加入的元素放入链表尾部
    void Pop();                //将链表头部的元素删除
};

template <typename T>
bool LQueue<T>::IsEmpty() const
{
    return list.IsEmpty();
}

template <typename T>
T LQueue<T>::GetFront() const
{
    if (IsEmpty())
        throw std::invalid_argument("ERROR: LQueue Is Empty Calling {T LQueue<T>::GetFront() const}");
    return list.GetFront();
}

template <typename T>
void LQueue<T>::Push(T const& _obj)
{
    //将新元素添加到链表尾部
    list.PushBack(_obj);
}

template <typename T>
void LQueue<T>::Pop()
{
    if (IsEmpty())
        throw std::invalid_argument("ERROR: LQueue Is Empty Calling {void LQueue<T>::Pop()}");
    //删除链表头部元素
    list.PopFront();
}

namespace Test_L_Queue
{
    void MainTest()
    {
        std::cout << "--------------------------------------------------" << "\n";

        //初始化测试
        LQueue<std::string> queue;

        //函数测试
        queue.Push("Tamako"); std::cout << "**Push(\"Tamako\")\n";
        queue.Push("Yui"); std::cout << "**Push(\"Yui\")\n";
        queue.Push("Nina"); std::cout << "**Push(\"Nina\")\n";
        std::cout << "##GetFront: " << queue.GetFront() << "\n";
        //##GetFront: Tamako
        queue.Pop(); std::cout << "**Pop\n";
        std::cout << "##GetFront: " << queue.GetFront() << "\n";
        //##GetFront: Yui
        queue.Pop(); std::cout << "**Pop\n";
        std::cout << "##GetFront: " << queue.GetFront() << "\n";
        //##GetFront: Nina
        queue.Pop(); std::cout << "**Pop\n";
        std::cout << "##IsEmpty: " << queue.IsEmpty() << "\n";
        //##IsEmpty: 1

        std::cout << "--------------------------------------------------" << "\n";
    }
}

#endif