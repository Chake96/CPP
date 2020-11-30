#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <thread>
#include <mutex>
#include <random>

using namespace std;
std::mutex m;

int main(){
	std::random_device dev;
	std::mt19937 engine(dev());

	vector<int> vec{1,2,3,4,5,6,7,8,9};

	for_each(execution::par, vec.begin(), vec.end(), [&](auto& var){
			std::lock_guard<std::mutex> guard(m);
			var += 1;
			});

	for_each(execution::par_unseq, vec.cbegin(), vec.cend(), [](auto var){
			std::lock_guard<std::mutex> guard(m);
			cout << var << ' ';
			});
	cout << '\n';
	shuffle(vec.begin(), vec.end(), engine);

	for_each(execution::par_unseq, vec.cbegin(), vec.cend(), [](auto var){
			std::lock_guard<std::mutex> guard(m);
			cout << var << ' ';
			});
	cout << '\n';

}
