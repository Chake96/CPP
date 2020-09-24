#include <iostream>
#include "queue.h"




int main(){

	Queue<int> a(0);
	std::cout << a;
	a.push(1);
	// a.push(2);
	// a.push(3);
	// a.print_from_bottom();
	// auto pop = a.pop();
	// std::cout << pop << '\n';
	// a.pop();
	// a.pop();
	// a.pop();
	std::cout << a;

	return EXIT_SUCCESS;
}
