#include <iostream>
#include <vector>



using std::vector;


vector<int> getRow(int r_ind){
	vector<int> result(1,1); 
	for(int i = 0; i < r_ind; i++){
		result.push_back(r_ind)
		
	}
	return result;
}

int main(){

	int row_num = 3;
	vector<int> result = getRow(row_num);
	std::cout << '[';
	for(int r: result)
		std::cout << r << ',';
	std::cout << ']';


}
