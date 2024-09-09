#ifndef _DOUBLE_LINKED_LIST_HPP_
#define _DOUBLE_LINKED_LIST_HPP_

#include <iostream>

//双向链表的每个节点都存储了前后两个节点的地址
template <typename T>
struct DoubleNode
{
    T data;
    DoubleNode* former;
    DoubleNode* next;
};

//相比单向链表，双向链表只需要在Insert和Erase这两个的实现上多处理一个former指针即可
template <typename T>
class DoubleLinkedList
{
private:
    int length = 0;                  //列表当前长度
    DoubleNode<T>* head = nullptr;   //头节点指针
    DoubleNode<T>* tail = nullptr;   //尾节点指针

public:
    DoubleLinkedList() = default;    //构造函数
    ~DoubleLinkedList();             //析构函数

    int GetLength() const;           //获取当前链表长度
    bool IsEmpty() const;            //查询当前列表是否为空
    T GetElem(int) const;            //检索特定索引的元素（只读）
    int Find(T) const;               //查找某元素的位置索引
    T GetFront() const;              //返回链表头部元素
    T GetBack() const;               //返回链表尾部元素

    bool Insert(T, int);             //插入元素到指定位置
    void PushFront(T const&);        //将元素插入到链表头部
    void PushBack(T const&);         //将元素插入到链表尾部
    void Erase(int);                 //删除指定位置的元素
    void PopFront();                 //删除头部元素
    void PopBack();                  //删除尾部元素
};

//方法的实现，暂时懒得写

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