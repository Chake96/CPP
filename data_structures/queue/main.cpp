#include <iostream>
#include <string>

#include "queue.h"


int main(){

    Queue<int> empty;
    Queue<int> i_q(0);

    int a = 1;
    // empty.push(0);
    // empty.push(1);
    i_q.push(a);
    std::cout << i_q;
    // i_q.push(2);
    std::cout << i_q;
    // auto val = i_q.pop();
    // std::cout << val << '\n' <<  i_q;

}