#include "01-LinearList/01-SequentialList.hpp"
#include "01-LinearList/02-SingleLinkedList.hpp"
#include "01-LinearList/03-LStack.hpp"
#include "01-LinearList/04-SStack.hpp"
#include "01-LinearList/05-LQueue.hpp"
#include "01-LinearList/06-SQueue.hpp"

void TestLinearList()
{
    Test_Sequential_List::MainTest();
    Test_Single_Linked_List::MainTest();
    Test_L_Stack::MainTest();
    Test_S_Stack::MainTest();
    Test_L_Queue::MainTest();
    Test_S_Queue::MainTest();
}

int main()
{
    TestLinearList();
}