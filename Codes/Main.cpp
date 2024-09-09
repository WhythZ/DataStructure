#include "01-LinearList/01-SequentialList.hpp"
#include "01-LinearList/02-SingleLinkedList.hpp"
#include "01-LinearList/03-DoubleLinkedList.hpp"
#include "01-LinearList/04-LStack.hpp"
#include "01-LinearList/05-SStack.hpp"
#include "01-LinearList/06-LQueue.hpp"
#include "01-LinearList/07-SQueue.hpp"
#include "02-Tree/01-MultiTree.hpp"
#include "02-Tree/02-BinaryTree.hpp"

void TestLinearList()
{
    Test_Sequential_List::MainTest();
    Test_Single_Linked_List::MainTest();
    Test_Double_Linked_List::MainTest();
    Test_L_Stack::MainTest();
    Test_S_Stack::MainTest();
    Test_L_Queue::MainTest();
    Test_S_Queue::MainTest();
}

void TestTree()
{
    Test_Multi_Tree::MainTest();
    Test_Binary_Tree::MainTest();
}

int main()
{
    TestLinearList();
    TestTree();
}