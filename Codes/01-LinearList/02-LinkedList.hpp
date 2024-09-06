#ifndef _LINKED_LIST_HPP_
#define _LINKED_LIST_HPP_

#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node* next;
};

template <typename T>
class LinkedList
{
private:
    int length = 0;             //列表当前长度
    Node<T>* head = nullptr;    //头节点指针
    Node<T>* tail = nullptr;    //尾节点指针

public:
    LinkedList() = default;     //构造函数
    ~LinkedList();              //析构函数

    int GetLength() const;      //获取当前链表长度
    bool IsEmpty() const;       //查询当前列表是否为空
    T GetElem(int) const;       //检索特定索引的元素（只读）
    int Find(T) const;          //查找某元素的位置索引

    bool Insert(T, int);        //插入元素到指定位置
    void PushFront(T const&);   //将元素插入到链表头部
    void Erase(int);            //删除指定位置的元素
    void PopFront();            //删除头部元素
};

template <typename T>
LinkedList<T>::~LinkedList()
{
    //由于此链表的节点都是开辟在堆区的，所以要销毁所有节点开辟的内存
    while (head != nullptr)
    {
        //用_temp保存头节点指向的内存
        Node<T>* _temp = head;
        //用head指针指向下一个节点
        head = head->next;
        //删除temp指向的内存
        delete _temp;
    }
    //用空指针覆盖头尾指针，以防出现安全问题
    head = nullptr;
    tail = nullptr;
    //将链表的长度归零
    length = 0;
}

template <typename T>
int LinkedList<T>::GetLength() const
{
    return length;
}

template <typename T>
bool LinkedList<T>::IsEmpty() const
{
    return (length == 0);
}

template <typename T>
T LinkedList<T>::GetElem(int _idx) const
{
    //排除非法索引
    if (_idx < 0 || _idx >= length)
        throw std::runtime_error("ERROR: Illegal Access");
    //以_temp作为迭代器，从头指针开始追溯到指定索引位置的链节点
    Node<T>* _temp = head;
    for (int i = 0; i < _idx; i++)
    {
        _temp = _temp->next;
    }
    //返回的是值而非引用
    return _temp->data;
}

template <typename T>
int LinkedList<T>::Find(T _obj) const
{
    //计数器
    int _counter = 0;
    //迭代查找第一个相符的节点
    Node<T>* _temp = head;
    while (_temp != nullptr)
    {
        if (_temp->data == _obj)
        {
            return _counter;
        }
        _temp = _temp->next;
        _counter++;
    }
    //没找到就返回-1
    return -1;
}

template <typename T>
bool LinkedList<T>::Insert(T _obj, int _idx)
{
    //创建指向新节点的指针
    Node<T>* _new = new Node<T>;
    _new->data = _obj;

    //排除非法索引
    if (_idx < 0 || _idx > length)
        return false;
    //如果插入的位置是链表的第一个位置
    else if (_idx == 0)
    {
        //将新节点的next指针指向第一个节点（head指向的节点）
        _new->next = head;
        //将head指向的节点从原来的地方挪动到指向这个新节点
        head = _new;
        //因为此时只有一个节点，所以将tail指向这个节点,不然tail始终都指向nullptr
        tail = _new;
    }
    //如果插入的位置是链表的末尾（最后一个节点的后一位）
    else if (_idx == length)
    {
        _new->next = nullptr;
        //设置tail指向的节点（最后一个节点）的下一个元素（原本是空指针）为这个新节点
        tail->next = _new;
        //将tail指向新的末尾节点
        tail = _new;
    }
    //如果插入的位置在中间
    else
    {
        //注意经过此循环后_temp指向的是期望Insert到的位置的前一个节点，所以是(_idx - 1)
        Node<T>* _temp = head;
        for (int i = 0; i < _idx - 1; i++)
        {
            _temp = _temp->next;
        }
        _new->next = _temp->next;
        _temp->next = _new;
    }

    //增加长度
    length++;
    return true;
}

template <typename T>
void LinkedList<T>::PushFront(T const& _obj)
{
    //插入到头部
    Insert(_obj, 0);
}

template <typename T>
void LinkedList<T>::Erase(int _idx)
{
    //排除非法索引
    if (_idx < 0 || _idx > length)
        throw std::runtime_error("ERROR: Illegal Access");

    //创建迭代器
    Node<T>* _temp = head;
    //特殊处理第一个元素
    if (_idx == 0)
    {
        head = head->next;
        //删除头节点
        delete _temp;
    }
    else
    {
        //经历循环后_temp指向的是_idx索引位置的前一个节点
        for (int i = 0; i < _idx - 1; i++)
        {
            _temp = _temp->next;
        }
        //先存储一下要销毁的节点的内存位置
        Node<T>* _delete = _temp->next;
        //再把要销毁的节点的前后两个节点连接上
        _temp->next = _temp->next->next;
        //然后销毁对应节点
        delete _delete;

        //检查删除的是不是尾部节点，若是，则需要转移tail的指向
        if (_temp->next == nullptr)
            tail = _temp;
    }

    //长度缩减
    length--;
}

template <typename T>
void LinkedList<T>::PopFront()
{
	//删除头部元素
    Erase(0);
}

namespace Test_Linked_List
{
    class Item
    {
    public:
        int id = 0;
        Item() = default;
        Item(int _id) :id(_id) {}
    };

    void PrintListInt(LinkedList<int>& _list)
    {
        for (int i = 0; i < _list.GetLength(); i++)
        {
            std::cout << _list.GetElem(i) << " ";
        }
        std::cout << "\n";
    }

    void MainTest()
    {
        //测试构造函数
        LinkedList<Item> itemList;
        LinkedList<int> intList;

        //测试GetLength函数
        std::cout << intList.GetLength() << "\n";
        //0

        //测试IsEmpty函数
        std::cout << intList.IsEmpty() << "\n";
        //1
        
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
        intList.PushFront(x);
        PrintListInt(intList);
        //99 0 11 22 33 99
        intList.Insert(x, 2);
        PrintListInt(intList);
        //99 0 99 11 22 33 99
        
        //测试Erase函数
        intList.Erase(2);
        PrintListInt(intList);
        //99 0 11 22 33 99
        intList.PopFront();
        PrintListInt(intList);
        //0 11 22 33 99
        intList.Erase(4);
        PrintListInt(intList);
        //0 11 22 33

        //测试IsEmpty函数
        std::cout << intList.IsEmpty() << "\n";
        //0
        
        //测试Find函数
        std::cout << intList.Find(33) << "\n";
        //3
    }
}

#endif