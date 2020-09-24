#include "LL.h"
#include <iostream>

int main(){

    //heap
    std::cout << "Pointer Demonstration\n";
    int a = 0;
    List<int>* the_list = new List<int>(a);
    the_list->get_size();

    // std::cout << "List: " << *the_list << "\nSize:" << the_list->get_size() << '\n';
    // the_list->append(1);
    // the_list->append(*&a);
    // std::cout << "List: " << *the_list << "\nSize:" << the_list->get_size() << '\n';
    // the_list->pop_last();
    // std::cout << "List: " << *the_list << "\nSize:" << the_list->get_size() << '\n';
    // the_list->pop_last();
    // the_list->append(1);
    // std::cout << "List: " << *the_list << "\nSize:" << the_list->get_size() << '\n';


    //testing mixing and passing temps
    a = 0;
    int b = 1, c = 2;
    the_list->append(a);
    the_list->append(b);
    the_list->append(c);
    std::cout << "List: " << *the_list << "\nSize: " << the_list->get_size() << '\n';
    the_list->pop_last();
    std::cout << "List: " << *the_list << "\nSize: " << the_list->get_size() <<'\n';
    the_list->append(2);
    the_list->append(a);
    the_list->append(3);
    std::cout << "List: " << *the_list << "\nSize: " << the_list->get_size();

    delete the_list;

    return EXIT_SUCCESS;
}