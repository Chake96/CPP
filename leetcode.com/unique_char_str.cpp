#include <bits/stdc++.h>
using namespace std;


bool all_unique(const string& in){
	int sum = 0;
	for(unsigned int i = 0; i < in.length(); i++){
		int bi = in[i]-' ';
		if(sum & (1 << bi))
			return false;
		sum = sum | (1 << bi);
	}
	return true;
}

bool all_unique_ascii(const string& in){
	bool flags[256]{};
	for(auto c: in){
		if(flags[(unsigned int)c] == 1)
			return false;
		flags[(unsigned int)c] = 1;
	}
	return true;
}

int main(){
	string input = " ";
	bool result = false;
	while(getline(cin, input)){
		if(input.length() == 1) {
			result = true;
		}else if(input.length() > 256){
			result = false;	
		}else{
			result = all_unique(input) || all_unique_ascii(input);
		}
		cout << input << (result ? " is unique\n": " is not unique\n"); 
	}
	
}
