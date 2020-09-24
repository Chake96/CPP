#include "stack.hpp"
#include <stdio.h>
#include <iostream>
#include <string>


int main(){
	
	int random_num = 0;
	std::size_t stack_size = 20;
	Stack<int, 20> twenty_stack;
	
	FILE* u_random_file;
	
	u_random_file = fopen("/dev/urandom", "r");
	
	if(!u_random_file){
		std::perror("Failed opening udev");
		return EXIT_FAILURE;
	}
	int index = stack_size;
	for(; index > 0; index--){
		fread(&random_num, sizeof(random_num), 1, u_random_file);
		twenty_stack.push(random_num);
	}
	index = stack_size;
	std::cout << "Printing Stack Contents (Size = " << stack_size << ")\n";
	for(;index > 0; index--){
		std::cout << twenty_stack.top() << '\n';
		twenty_stack.pop();
	}
	
	fclose(u_random_file);


}
