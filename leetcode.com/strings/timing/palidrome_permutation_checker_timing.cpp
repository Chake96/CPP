#include "../../timing.cpp"
#include "../permutation_palindrome_checker.cpp"
#include <stdlib.h>
using namespace std;



int main(){
	string input = " ", sorted_input = " ";
	while(getline(cin, input)){
		partial_sort_copy(input.begin(), input.end(), sorted_input.begin(), sorted_input.end());
		auto time_unsorted = time_func(check_palindrome1, input);
		auto time_sorted = time_func(check_palindrome1, sorted_input);
		std::cout << "String: " << input << " of length: " << input.length() <<
		"\n palindrome_check took " << time_unsorted << " ns on unsorted string" <<
		"\n palindrome_check took " << time_sorted << " ns on sorted string\n";
	}
	input = " ";
	sorted_input = " ";
	random_device rd;
	std::mt19937 gen(rd());
	uniform_int_distribution<int> dist(0, 127);
	for(int i = 0; i < 1000000000; i++){
		unsigned char random = static_cast<unsigned char>(dist(gen));
		input.append(1, random);
	}
	partial_sort_copy(input.begin(), input.end(), sorted_input.begin(), sorted_input.begin());
	auto time_unsorted = time_func(check_palindrome1, input);
	std::cout  << "palindrome_check took " << time_unsorted << " nanoseconds on unsorted large string\n";
	auto time_sorted = time_func(check_palindrome1, sorted_input);
	std::cout  << "palindrome_check took " << time_sorted << " nanoseconds on sorted large string\n";
	return 0;
}

