#include <iostream>
#include "stack.hpp"

int main(int argc, char* argv[]) {

	Stack<std::string> str_stack;
	std::string str1 = "test";
	str_stack.push(str1);

	std::cout << str_stack.top(); << '\n';

	return 0;
}