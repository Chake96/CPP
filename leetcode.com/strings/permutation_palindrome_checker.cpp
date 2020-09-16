#include <bits/stdc++.h>
using namespace std;

//using hashing int
bool check_palindrome1(const string& in){
	int mask_check = 0;	
	for(auto c: in){
		c = (1 << c);
		mask_check ^= c;
	}
	//more than 1 odd means its not capable of making palindromes
	return ((mask_check &(mask_check-1)) == 0);
}

/*int main(int argc, char** argv){
	string input = " ";
	bool result = false;
	bool sorted = argc > 1;
	if(sorted) cout << "Sorting Inputs\n";
	while(getline(cin, input)){
		if(sorted) sort(input.begin(), input.end());
		result = check_palindrome1(input);
		cout << input << ((result) ? " is a palindrome\n" : " is not a palindrome\n");
	}
	
}*/
