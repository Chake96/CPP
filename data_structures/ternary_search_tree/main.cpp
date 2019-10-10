#include "tst.h"
#include <iostream>
#include <string>



int main(int argc, char**argv){
	if(argc != 2){
		std::cout << "Command Line Error: Please use Correct amount of Arguments\n";
	}
	
	try{
	}catch(... ){
		std::cerr << "Error: " << ' ' << std::endl; 
	}


	return EXIT_SUCCESS;
}
