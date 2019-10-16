#include "tst.h"
#include <iostream>
#include <string>



int main(int argc, char**argv){
	if(argc != 2){
		std::cout << "Command Line Error: Please use Correct amount of Arguments\n";
		std::cout << "Syntax: ./tst " << '"' << "first word in tree" << '"' << std::endl;
	}

	try{
		std::string input = argv[1];
		std::cout << "Inputted Word: " << input << std::endl;
		std::unique_ptr<tsTree> tree(new tsTree(input));			
		tree->print();
	}catch(... ){
		std::cerr << "Error: " << ' ' << std::endl; 
	}


	return EXIT_SUCCESS;
}
