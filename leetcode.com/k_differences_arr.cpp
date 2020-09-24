#include <bits/stdc++.h>

using namespace std;

int main(){
	int k = 2;
	unordered_map<int, int> m;
	vector<int> in = {1,2,4,9,11,40,7};
	for(auto i: in)
		m.insert({i,i*k});
	
	for(auto i: in){
		if(m.find(i+k) != m.end() || m.find(i-k) != m.end()){
				std::cout << i << " has a " << k << "difference in the array\n";
		}else{
				std::cout << "F\n";
		}
	}

	return 0;
}
