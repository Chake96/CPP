#include "simple_max_function.hpp"
#include <iostream>
#include <string>

int main(){
	int a = 1;
	int b = 0;
	std::cout << ::max(a,b) << std::endl; //reminder - :: is for global namespace calls
	return 0;
}
