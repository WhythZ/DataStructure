#ifndef _L_QUEUE_HPP_
#define _L_QUEUE_HPP_

#include <iostream>
#include "02-LinkedList.hpp"

template <typename T>
class LQueue
{
private:
    LinkedList<T> list;        //单向链表内核

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
        throw std::runtime_error("ERROR: Queue Is Empty");
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
        throw std::runtime_error("ERROR: Queue Is Empty");
    //删除链表头部元素
    list.PopFront();
}

namespace Test_L_Queue
{
    void MainTest()
    {
        //初始化测试
        LQueue<std::string> queue;

        //函数测试
        queue.Push("Tamako");
        queue.Push("Yui");
        queue.Push("Nina");
        std::cout << queue.GetFront() << "\n";
        //Tamako
        queue.Pop();
        std::cout << queue.GetFront() << "\n";
        //Yui
        queue.Pop();
        std::cout << queue.GetFront() << "\n";
        //Nina
        queue.Pop();
        std::cout << queue.GetFront() << "\n";
        //ERROR: Queue Is Empty
    }
}

#endif