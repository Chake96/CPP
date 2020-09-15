#include <bits/stdc++.h>

int shortestSubarray(std::vector<int>& A, int K) {
        if(A.size() == 1 && A[0] != K){
                return -1;
        }
        int sum = 0;
        std::vector<std::pair<int,int*>> store;
        int* max_val = nullptr;
        std::vector<int>::iterator it = A.begin(), end = A.end();
        while(it != end){
                if(*it >= K){
                    return 1;
                }
                else if(*it + *it+1 >= K){
                        return 2;
                }else{
                    if(max_val == nullptr || *it > *max_val){
                        max_val = &*it;
                    }
                    std::pair<int, int*> n_pair(*it, &*it);
                    store.insert(std::upper_bound(store.begin(), store.end(),n_pair ,
                                            [](std::pair<int, int*>a, std::pair<int, int*> b){
                                            return a.first > b.first;
                                            })
                                    , n_pair);
                }
                it++;
        }
        std::size_t arr_sz = 3;
        std:: cout << *max_val << ' ' << *(max_val +1) << ' ' << *(max_val -1) << std::endl;
        int max_sum = (*max_val + *(max_val +1) + *(max_val -1) > *max_val) ? *max_val + *(max_val +1) + *(max_val -1) : *max_val;
        std::cout << max_sum << std::endl;

        for(;arr_sz < A.size(); arr_sz++){
            for(int i = 0; i < store.size(); i++){
                if(i > 0 && i < store.size()-1){
                }else if(i < store.size()-1){

                }else{

                }
            }
        }
        return -1;
}

int main(){
		std::vector<int> t = {-500, -100, 600, 1};
		int res = shortestSubarray(t, 1);
		std::cout << "Result: " <<  res << '\n';
		std::vector<int> t2 = {1,2};
		std::vector<int> t3 = {1,2, 60, 100,20, 50, 4, -2, 3,4 -500, -1, 1,1,1,-3,4};
		res = shortestSubarray(t2, 4);
		std::cout << "Result2: " << res << '\n';
		res = shortestSubarray(t3, 4);
		std::cout << "Result3: " << res << '\n';
		res = shortestSubarray(t3, 500);
		std::cout << "Result3: " << res << '\n';
		res = shortestSubarray(t3, 101);
		std::cout << "Result3: " << res << '\n';
		res = shortestSubarray(t3, 999);
		std::cout << "Result3: " << res << '\n';
		res = shortestSubarray(t3, 90);
		std::cout << "Result3: " << res << '\n';
		return 0;
}
