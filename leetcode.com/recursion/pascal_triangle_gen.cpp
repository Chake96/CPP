#include <iostream>
#include <vector>


using std::vector;



vector<vector<unsigned int>> generate(unsigned int num_r){
	vector<vector<unsigned int>> result;
	if(num_r == 0) return result;
	
	//base-case 
	vector<unsigned int>* curr_row = new vector<unsigned int>(1,1);
	result.push_back(*curr_row);
	curr_row->clear();
	
	//n-th case
	for(unsigned int it = 1; it < num_r; it++){ //builds results
		curr_row->push_back(1);
		for(unsigned int fill_rit = 0; fill_rit < it-1;fill_rit++){ //builds individual rows
			curr_row->push_back(result[it-1][fill_rit] + result[it-1][fill_rit+1]);
		}		
		curr_row->push_back(1);
		result.push_back(*curr_row);
		curr_row->clear();
	}
	delete curr_row;

	return result;
}

int main(){

	vector<vector<unsigned int>> test = generate(5);
	for(vector<unsigned int> vec: test){
		std::cout << '[';
		for(unsigned int value: vec){
			std::cout << value << ",";
		}
		std::cout << "],\n";
	}


	std::exit(0);
}
