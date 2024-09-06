#include "01-LinearList/01-SequentialList.hpp"
#include "01-LinearList/02-LinkedList.hpp"
#include "01-LinearList/03-LStack.hpp"
#include "01-LinearList/04-SStack.hpp"
#include "01-LinearList/05-LQueue.hpp"

int main()
{
    std::cout << "--------------------------------------------------" << "\n";
    // Test_Sequential_List::MainTest();
    std::cout << "--------------------------------------------------" << "\n";
    // Test_Linked_List::MainTest();
    std::cout << "--------------------------------------------------" << "\n";
    // Test_L_Stack::MainTest();
    std::cout << "--------------------------------------------------" << "\n";
    // Test_S_Stack::MainTest();
    std::cout << "--------------------------------------------------" << "\n";
    Test_L_Queue::MainTest();
    std::cout << "--------------------------------------------------" << "\n";
}