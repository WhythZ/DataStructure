#ifndef _S_QUEUE_HPP_
#define _S_QUEUE_HPP_

#include <iostream>
#include <algorithm>

//使用循环数组作为内核，使得首尾两端插入或删除元素的时间复杂度均为O(1)
template <typename T>
class SQueue
{
private:
    T* array;                   //数组首地址
    int queueSize;              //队列当前存了多少对象
    int arrayCapacity;          //内核数组的（初始）容量
    int frontIdx;               //循环数组的头部元素（队列前端）索引
    int backIdx;                //循环数组的尾部元素（队列后端）索引

public:
    SQueue(int = 10);           //构造函数
    ~SQueue();                  //析构函数

    bool IsEmpty() const;       //空判断
    T GetFront() const;         //获得队列前端元素值
    T* GetFrontPtr() const;     //获得队列前端元素指针
    void PrintArray() const;    //从头到尾打印内核数组（调试用）

    void Push(T const&);        //将新元素推送到数组尾部
    void Pop();                 //将数组头部即队列前端的元素删除

private:
    void DoubleTheCapacity();   //内核数组扩容
};

template <typename T>
SQueue<T>::SQueue(int _capacity)
{
    queueSize = 0;
    arrayCapacity = std::max(1, _capacity);
    //为数组在堆区申请内存，对每个T对象调用默认初始化构造函数
    array = new T[arrayCapacity];
    //队列的前端元素索引，也即存储下一次被取出队列的元素的索引
    frontIdx = 0;
    //队伍末端元素索引，每次Push新元素进来就给这个变量+1
    backIdx = -1;
}

template <typename T>
SQueue<T>::~SQueue()
{
    delete[] array;
}

template <typename T>
bool SQueue<T>::IsEmpty() const
{
    return (queueSize == 0);
}

template <typename T>
T SQueue<T>::GetFront() const
{
    if (IsEmpty())
        throw std::invalid_argument("ERROR: SQueue Is Empty Calling {T SQueue<T>::GetFront() const}");
    //返回队列前端元素
    return array[frontIdx];
}

template <typename T>
T* SQueue<T>::GetFrontPtr() const
{
    if (IsEmpty())
        throw std::invalid_argument("ERROR: SQueue Is Empty Calling {T* SQueue<T>::GetFrontPtr() const}");
    //返回队列前端元素指针
    return &array[frontIdx];
}

template <typename T>
void SQueue<T>::PrintArray() const
{
    std::cout << "Array: ";

    for (int i = 0; i < arrayCapacity; i++)
    {
        if (queueSize == 1 && i == 0)
        {
            std::cout << "[" << i << "]:" << array[i] << "*F*B ";
            continue;
        }
        else if (i == frontIdx)
        {
            std::cout << "[" << i << "]:" << array[i] << "*F   ";
            continue;
        }
        else if (i == backIdx)
        {
            std::cout << "[" << i << "]:" << array[i] << "*B   ";
            continue;
        }
        else
            std::cout << "[" << i << "]:" << array[i] << "     ";
    }

    if (backIdx == -1)
        std::cout << "[" << -1 << "]:" << "~*B\n";
    else
        std::cout << "[" << -1 << "]:" << "~\n";
}

template <typename T>
void SQueue<T>::Push(T const& _obj)
{
    //数组容量完全占满后扩容两倍
    if (queueSize == arrayCapacity)
        DoubleTheCapacity();

    //若本来就还有空位，或者扩容成功后，执行此块语句
    if (queueSize < arrayCapacity)
    {
        //当此时尾指针还没到达数组尾部时（包括初始的-1），无论在frontIdx的前或后，只要数组没满就可直接递增
        if (backIdx < arrayCapacity - 1)
        {
            //将尾索引向后推移
            backIdx++;
        }
        //触碰到底部就要折返回0索引处
        else if (backIdx == arrayCapacity - 1)
        {
            backIdx = 0;
        }

        //将元素放进来
        array[backIdx] = _obj;

        //递增队列规模
        queueSize++;

        //结束此函数
        return;
    }

    //正常经历了以上步骤就应当结束了，执行到了这里说明扩容失败了
    throw std::runtime_error("ERROR: Fail To Expand SQueue Capacity");
}

template <typename T>
void SQueue<T>::Pop()
{
    //排除异常
    if (IsEmpty())
        throw std::invalid_argument("ERROR: SQueue Is Empty Calling {void SQueue<T>::Pop()}");

    //直接递增
    if (frontIdx < arrayCapacity - 1)
    {
        //将原来位置上的储存对象清零（非必须，仅调试所需）
        array[frontIdx] = T();
        //将头索引向后推移
        frontIdx++;
    }
    //触碰到底部就折返回0索引处
    else if (frontIdx == arrayCapacity - 1)
    {
        frontIdx = 0;
    }

    //递减队列规模
    queueSize--;
}

template <typename T>
void SQueue<T>::DoubleTheCapacity()
{
    //开辟新数组
    T* _temp = new T[2 * arrayCapacity];

    //将原数组转移，此处采用的方法是将顺序归正并放在新数组的左侧
    if (backIdx > frontIdx)
    {
        for (int i = 0; i <= backIdx; i++)
            _temp[i] = array[i];
    }
    else if (backIdx < frontIdx)
    {
        for (int i = frontIdx; i < arrayCapacity; i++)
            _temp[i - frontIdx] = array[i];
        for (int j = 0; j <= backIdx; j++)
            _temp[j + frontIdx] = array[j];
    }
    //特殊处理数组容量为1且其内只有一个元素的情况
    else
        _temp[0]=array[0]

    //将头尾索引摆到正确位置
    frontIdx = 0;
    backIdx = arrayCapacity - 1;

    //销毁原数组，将指针转移，并登记新的容量
    delete[] array;
    array = _temp;
    arrayCapacity *= 2;
}

namespace Test_S_Queue
{
    struct Item
    {
        int data;
        //默认构造函数
        Item() :data(0) {}
        Item(int _data) :data(_data) {}
    };

    //重载左移运算符以便打印调试
    std::ostream& operator<<(std::ostream& _cout, Item& _item)
    {
        _cout << _item.data;
        //以便链式调用左移运算符
        return _cout;
    }
    
    void MainTest()
    {
        std::cout << "--------------------------------------------------\n";

        //初始化测试
        SQueue<Item> queue(4);
        queue.PrintArray();
        //Array: [0]:0*F   [1]:0     [2]:0     [3]:0     [-1]:~*B

        //Push函数测试情景一
        queue.Push(Item(11)); std::cout << "**Push Item(11)\n";
        queue.PrintArray();
        //Array: [0]:11*F*B [1]:0     [2]:0     [3]:0     [-1]:~
        queue.Push(Item(22)); std::cout << "**Push Item(22)\n";
        queue.Push(Item(33)); std::cout << "**Push Item(33)\n";
        queue.Push(Item(44)); std::cout << "**Push Item(44)\n";
        queue.PrintArray();
        //Array: [0]:11*F   [1]:22     [2]:33     [3]:44*B   [-1]:~

        //Pop函数测试
        queue.Pop(); std::cout << "**Pop\n";
        queue.Pop(); std::cout << "**Pop\n";
        queue.PrintArray();
        //Array: [0]:0     [1]:0     [2]:33*F   [3]:44*B   [-1]:~

        //Push函数测试情景二
        queue.Push(Item(55)); std::cout << "**Push Item(55)\n";
        queue.PrintArray();
        //Array: [0]:55*B   [1]:0     [2]:33*F   [3]:44     [-1]:~

        //扩容测试
        queue.Push(Item(66)); std::cout << "**Push Item(66)\n";
        queue.PrintArray();
        //Array: [0]:55     [1]:66*B   [2]:33*F   [3]:44     [-1]:~
        queue.Push(Item(77)); std::cout << "**Push Item(77)\n";
        queue.PrintArray();
        //Array: [0]:33*F   [1]:44     [2]:55     [3]:66     [4]:77*B   [5]:0     [6]:0     [7]:0     [-1]:~

        std::cout << "--------------------------------------------------\n";
    }
}

#endif