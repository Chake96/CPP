#include <typeinfo>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

void reverse_string(std::vector<char>& s) {
	std::size_t tail_it = s.size()-1;
	char temp = ' ';
	for(unsigned int it = 0; it < s.size()/2; it++){
		temp = std::move(s[it]);
		s[it] = std::move(s[tail_it]);
		s[tail_it] = std::move(temp);
		tail_it--;
	}
}




int main(int argc, char* argv[]){
	
	std::fstream random_f("/dev/urandom", std::fstream::in);
	unsigned long long int random_seed = 0;
	
	if(random_f){
		random_f.read(reinterpret_cast<char*>(&random_seed), sizeof(random_seed));
	}else{
		std::cerr << "I/O Error: Failed to open file" << std::endl;
	}

	srand(random_seed);
	
	if(argc < 1){ 
		std::cerr << "Wrong Args: " << *argv << std::endl;
		std::exit(1);
	}
	std::cout << argv[1] << " " << strlen(argv[1]) << std::endl;	
	
	std::vector<char> input_word(std::strlen(argv[1]));
	std::strcpy(&input_word[0], argv[1]);
	std::cout << "Before: << " << argv[1] << '\n';

	reverse_string(input_word);

	std::cout << "After: << ";
	std::string r_string(input_word.begin(), input_word.end());
	std::cout << r_string << std::endl;
	
	std::exit(0);
}
