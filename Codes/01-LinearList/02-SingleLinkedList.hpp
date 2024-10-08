#ifndef _SINGLE_LINKED_LIST_HPP_
#define _SINGLE_LINKED_LIST_HPP_

#include <iostream>

template <typename T>
struct SingleNode
{
    T data;
    SingleNode<T>* next;
};

template <typename T>
class SingleLinkedList
{
private:
    int length = 0;                       //列表当前长度
    SingleNode<T>* head = nullptr;        //头节点指针
    SingleNode<T>* tail = nullptr;        //尾节点指针

public:
    SingleLinkedList() = default;         //构造函数
    ~SingleLinkedList();                  //析构函数

    int GetLength() const;                //获取当前链表长度
    bool IsEmpty() const;                 //查询当前列表是否为空
    T GetElem(int) const;                 //返回特定索引对应的元素值
    T* GetElemPtr(int) const;             //检索特定索引的元素的指针
    int Find(T) const;                    //返回第一个等于传入值的元素索引
    int Find(T*) const;                   //准确定位传入指针对应的元素索引
    T GetFront() const;                   //返回链表头部元素值
    T* GetFrontPtr() const;               //返回链表头部元素指针
    T GetBack() const;                    //返回链表尾部元素值
    T* GetBackPtr() const;                //返回链表尾部元素值

    bool Insert(T, int);                  //插入元素到指定位置
    void PushFront(T);                    //将元素插入到链表头部
    void PushBack(T);                     //将元素插入到链表尾部
    void Erase(int);                      //删除指定位置的元素
    void PopFront();                      //删除头部元素
    void PopBack();                       //删除尾部元素
};

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    //由于此链表的节点都是开辟在堆区的，所以要销毁所有节点开辟的内存
    while (head != tail)
    {
        //用_temp保存头节点指向的内存
        SingleNode<T>* _temp = head;
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
int SingleLinkedList<T>::GetLength() const
{
    return length;
}

template <typename T>
bool SingleLinkedList<T>::IsEmpty() const
{
    return (length == 0);
}

template <typename T>
T SingleLinkedList<T>::GetElem(int _idx) const
{
    //排除非法索引
    if (_idx < 0 || _idx >= length)
        throw std::invalid_argument("ERROR: Invalid Index Calling {T SingleLinkedList<T>::GetElem(int _idx) const}");
    
    //通过尾指针使得尾部元素的获取的时间复杂度降到O(1)
    if (_idx == length - 1)
        return tail->data;
    
    //以_temp作为迭代器，从头指针开始追溯到指定索引位置的链节点
    SingleNode<T>* _temp = head;
    for (int i = 0; i < _idx; i++)
    {
        _temp = _temp->next;
    }

    //返回的是值而非引用
    return _temp->data;
}

template <typename T>
T* SingleLinkedList<T>::GetElemPtr(int _idx) const
{
    //排除非法索引
    if (_idx < 0 || _idx >= length)
        throw std::invalid_argument("ERROR: Invalid Index Calling {T* SingleLinkedList<T>::GetElemPtr(int _idx) const}");
    
    //通过尾指针使得尾部元素的获取的时间复杂度降到O(1)
    if (_idx == length - 1)
        return &(tail->data);
    
    //以_temp作为迭代器，从头指针开始追溯到指定索引位置的链节点
    SingleNode<T>* _temp = head;
    for (int i = 0; i < _idx; i++)
    {
        _temp = _temp->next;
    }

    //返回的是指向该地址的指针
    return &(_temp->data);
}

template <typename T>
int SingleLinkedList<T>::Find(T _obj) const
{
    //计数器
    int _counter = 0;
    //迭代查找第一个相符的节点
    SingleNode<T>* _temp = head;
    while (_temp != nullptr)
    {
        if (_temp->data == _obj)
        {
            return _counter;
        }
        _temp = _temp->next;
        _counter++;
    }
    //没找到就报错
    throw std::runtime_error("ERROR: Failed To Find The Object Using {int SingleLinkedList<T>::Find(T _obj) const}");
}

template <typename T>
int SingleLinkedList<T>::Find(T* _obj) const
{
    //计数器
    int _counter = 0;
    //迭代查找第一个相符的节点
    SingleNode<T>* _temp = head;
    while (_temp != nullptr)
    {
        if (_obj == &(_temp->data))
        {
            return _counter;
        }
        _temp = _temp->next;
        _counter++;
    }
    //没找到就报错
    throw std::runtime_error("ERROR: Failed To Find The Object Using {int SingleLinkedList<T>::Find(T* _obj) const}");
}

template <typename T>
T SingleLinkedList<T>::GetFront() const
{
    //时间复杂度为O(1)
    return GetElem(0);
}

template <typename T>
T* SingleLinkedList<T>::GetFrontPtr() const
{
    //时间复杂度为O(1)
    return GetElemPtr(0);
}

template <typename T>
T SingleLinkedList<T>::GetBack() const
{
    //通过尾指针访问，可以使得时间复杂度为O(1)
    return GetElem(length - 1);
}

template <typename T>
T* SingleLinkedList<T>::GetBackPtr() const
{
    //通过尾指针访问，可以使得时间复杂度为O(1)
    return GetElemPtr(length - 1);
}

template <typename T>
bool SingleLinkedList<T>::Insert(T _obj, int _idx)
{
    //创建指向新节点的指针
    SingleNode<T>* _new = new SingleNode<T>;
    _new->data = _obj;

    //排除非法索引
    if (_idx < 0 || _idx > length)
        return false;
    //如果插入的位置是链表的第一个位置
    else if (_idx == 0)
    {
        //当插入的是第一个元素的时候
        if (length == 0)
        {
            //将head从nullptr指向这个新的节点
            head = _new;
            //因为此时只有一个节点，所以将tail指向这个节点,不然tail始终都指向nullptr
            tail = _new;
        }
        else
        {
            //将新节点的next指针指向第一个节点（head指向的节点）
            _new->next = head;
            //将head指向的节点从原来的地方挪动到指向这个新节点
            head = _new;
        }
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
        SingleNode<T>* _temp = head;
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
void SingleLinkedList<T>::PushFront(T _obj)
{
    //插入新元素到头部，时间复杂度为O(1)
    Insert(_obj, 0);
}

template <typename T>
void SingleLinkedList<T>::PushBack(T _obj)
{
    //插入新元素到尾部
    //由于可以通过尾指针添加新元素到尾部，所以时间复杂度为O(1)
    Insert(_obj, length);
}

template <typename T>
void SingleLinkedList<T>::Erase(int _idx)
{
    //排除非法索引
    if (_idx < 0 || _idx > length)
        throw std::invalid_argument("ERROR: Invalid Index Calling {void SingleLinkedList<T>::Erase(int _idx)}");

    //创建迭代器
    SingleNode<T>* _temp = head;
    //特殊处理第一个元素
    if (_idx == 0)
    {
        //若链表仅有一个元素的时候，将head右移（指向nullptr，且会与还指向0位元素的tail错开）会导致析构的时候判断出错
        if (length > 1)
        {
            //将头指针后移
            head = head->next;
        }
        //删除头节点原先的内存
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
        SingleNode<T>* _delete = _temp->next;
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
void SingleLinkedList<T>::PopFront()
{
	//删除头部元素，时间复杂度为O(1)
    Erase(0);
}

template <typename T>
void SingleLinkedList<T>::PopBack()
{
    //删除尾部元素
    //由于此链表是单向链表，Erase函数无法通过尾指针访问倒数第二个元素，所以必须从头指针开始遍历，所以PopBack的复杂度为O(n)
    Erase(length - 1);
}

namespace Test_Single_Linked_List
{
    void PrintListInt(SingleLinkedList<int>& _list)
    {
        std::cout << "List Elements: ";
        for (int i = 0; i < _list.GetLength(); i++)
        {
            std::cout << _list.GetElem(i) << " ";
        }
        std::cout << "\n";
    }

    void TestIntList()
    {
        //测试构造函数
        SingleLinkedList<int> intList;

        //测试IsEmpty函数
        std::cout << "##IsEmpty: " << intList.IsEmpty() << "\n";
        //##IsEmpty: 1
        
        //测试Insert、PushFront、PushBack函数
        int a = 22, b = 33, c = 44, x = 99;
        intList.Insert(a, 0);
        intList.Insert(b, 1);
        intList.Insert(c, 2);
        PrintListInt(intList);
        //List Elements: 22 33 44
        intList.PushBack(x);
        PrintListInt(intList);
        //List Elements: 22 33 44 99
        intList.PushFront(x);
        PrintListInt(intList);
        //List Elements: 99 22 33 44 99
        intList.Insert(x, 2);
        PrintListInt(intList);
        //List Elements: 99 22 99 33 44 99

        //测试Find、GetLength函数
        std::cout << "##Find [33]: " << intList.Find(33) << "\n";
        //##Find [33]: 3
        std::cout << "##GetLength: " << intList.GetLength() << "\n";
        //##GetLength: 6

        //测试Erase、PopBack、PopFront函数
        intList.PopBack(); std::cout << "**PopBack" << "\n";
        PrintListInt(intList);
        //List Elements: 99 22 99 33 44
        intList.PopFront(); std::cout << "**PopFront" << "\n";
        PrintListInt(intList);
        //List Elements: 22 99 33 44
        intList.Erase(1); std::cout << "**Erase [1]" << "\n";
        PrintListInt(intList);
        //List Elements: 22 33 44

        //测试GetFront、GetBack函数
        std::cout << "##GetFront: " << intList.GetFront() << "\n";
        //##GetFront: 22
        std::cout << "##GetBack: " << intList.GetBack() << "\n";
        //##GetBack: 44

        //测试GetElem函数
        std::cout << "##GetElem [2]: " << intList.GetElem(2) << "\n";
        //##GetElem [2]: 44
        intList.PopBack(); std::cout << "**PopBack" << "\n";
        PrintListInt(intList);
        //List Elements: 22 33
        std::cout << "##GetElem [1]: " << intList.GetElem(1) << "\n";
        //##GetElem [1]: 33
        intList.PopFront(); std::cout << "**PopFront" << "\n";
        PrintListInt(intList);
        //List Elements: 33
        std::cout << "##GetElem [0]: " << intList.GetElem(0) << "\n";
        //##GetElem [0]: 33
    }

    struct Item
    {
        int id = 0;
        Item() = default;
        Item(int _id) :id(_id) {}
    };

    void TestOther()
    {
        SingleLinkedList<Item> itemList;
        itemList.PushBack(Item(111));
        itemList.PopBack();
    }

    void MainTest()
    {
        std::cout << "--------------------------------------------------\n";

        // std::cout << "--------------------TestArea01--------------------\n";
        TestIntList();
        // std::cout << "--------------------TestArea02--------------------\n";
        TestOther();

        std::cout << "--------------------------------------------------\n";
    }
}

#endif