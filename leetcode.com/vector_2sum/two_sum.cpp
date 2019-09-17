#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

/*
	sort and pinch solution: sort array in increasing order, walk pointers into middle till solution is found, if none return nothing
	does not give original position of elements, only their values

std::vector<int> sum2SortnPinch(std::vector<int>& numbers, int target){
	std::vector<int> result;
	unsigned int lhs = 0, rhs = numbers.size()-1;
	auto sum = 0;
	std::sort(numbers.begin(), numbers.end(), std::less<int>());

	while(lhs < rhs && sum != target){
		std::cout << "Testing: " << numbers[lhs] << ", " << numbers[rhs] << std::endl;

		sum = numbers[lhs] + numbers[rhs];
		if(sum == target){
			result = {lhs,rhs};
		}else if (sum < target){
			lhs++;
		}else{
			rhs--;
		}
	}
	return result;
}
*/ 

//standard approach, no improvements to make
std::vector<int> sum2(std::vector<int>& numbers, int target){
	std::vector<int> result;
	std::map<int, int> hmap;

	//index all elements into map
	auto search_num = 0;
	for(int i = 0; i < numbers.size(); i++){
		search_num = target - numbers[i];
		if(hmap.find(search_num) != hmap.end()){
			result.push_back(hmap[search_num]);
			result.push_back(i);
		}	
		hmap.insert(std::pair(numbers[i], i));
	}

	return result;
}

std::vector<int> sum2fast(std::vector<int>& nums, int target){
	std::vector<int> orderednum(nums);
	std::sort(orderednum.begin(), orderednum.end()); 
	std::vector<int> result(2);
	int opposite_pointer = nums.size() -1;
	for(int i = 0 ; i < nums.size() ; i++){
		int required =  target - orderednum[i];
		while(orderednum[opposite_pointer] > required){
			opposite_pointer--;
		}
		if(orderednum[opposite_pointer] < required)continue;
		
		result[0] = std::distance(nums.begin(), std::find(nums.begin(), nums.end(), orderednum[i]));
		std::reverse(nums.begin(),nums.end()); 
		result[1] = nums.size() - 1 - std::distance(nums.begin(), std::find( nums.begin(),nums.end(), orderednum[opposite_pointer]));
		break;
	}
	return result;
}


int main(int argc, char** argv){
	std::vector<int> input = {3,1,3};
	int target = 6;
	std::vector<int> result = sum2fast(input, target);

	for(auto elm: result)
		std::cout << elm << " ";
	std::cout << std::endl;
	return EXIT_SUCCESS;
}
