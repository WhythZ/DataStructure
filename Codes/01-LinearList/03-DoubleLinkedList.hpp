#ifndef _DOUBLE_LINKED_LIST_HPP_
#define _DOUBLE_LINKED_LIST_HPP_

#include <iostream>

//双向链表的每个节点都存储了前后两个节点的地址
template <typename T>
struct DoubleNode
{
    T data;
    DoubleNode<T>* former;
    DoubleNode<T>* next;
};

//相比单向链表，双向链表只需要在Insert和Erase这两个的实现上多处理一个former指针即可
template <typename T>
class DoubleLinkedList
{
private:
    int length = 0;                       //列表当前长度
    DoubleNode<T>* head = nullptr;        //头节点指针
    DoubleNode<T>* tail = nullptr;        //尾节点指针

public:
    DoubleLinkedList() = default;         //构造函数
    ~DoubleLinkedList();                  //析构函数
};

namespace Test_Double_Linked_List
{
    void MainTest()
    {
        std::cout << "--------------------------------------------------" << "\n";

        //测试

        std::cout << "--------------------------------------------------" << "\n";
    }
}

#endif