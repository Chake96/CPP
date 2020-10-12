
#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
#include <ctime>
#include <type_traits>
#include <set>
#include <map>
#include <string>

/*The code below is a quick example of using forwarding references as parameters while also being able to overload the functions

*/

/*c++11: uses std::remove_reference<T>::type
template<class T>
void log_and_add(T&& name){
	log_and_add_impl(std::forward<T>(name), std::is_integral<typename std::remove_reference<T>::type()>));
}
*/

//c++14: uses std::remove_reference_t<T>

//using time_system = std::chrono::
std::map<int, std::string> indexd_names = {{1,"carson"},{2,"copper"},{3,"Larry Page"}};
std::multiset<std::string> names;
using log_pair = std::pair<std::chrono::time_point<std::chrono::system_clock>, std::string>;
std::vector<log_pair> _log;
//std::vector<std::chrono::time_point<std::chrono::system_clock>> _log;


template<class T, class U=std::string>
void log(T time, U func_name){
	_log.push_back(std::make_pair(time, func_name));
}

std::string name_from_indx(int indx){
	auto it = indexd_names.find(indx);
	if(it != indexd_names.end()){
		return indexd_names[indx];
	}
	return "";
}

template<typename T>
void log_and_add(T&& name); //forward declare log_and_add so it can be called here
void log_and_add_impl(int indx, std::true_type){
	log_and_add(name_from_indx(indx));
}

template<class T>
void log_and_add_impl(T&& name, std::false_type){
	auto now = std::chrono::system_clock::now();
	log(now, "log_and_add");
	names.emplace(std::forward<T>(name));
}


template<class T>
void log_and_add(T&& name){
	log_and_add_impl(
		std::forward<T>(name), 
		std::is_integral<typename std::remove_reference_t<T>>());
}


int main(){
	log_and_add("carrot cake");
	log_and_add(1);
	for(auto i: _log){
		auto time = std::chrono::system_clock::to_time_t(i.first);
		auto name = i.second;
		std::cout << "Name {" << name << "} added at time: " << time << '\n';
	}
	log_and_add("carrot cake2");
	log_and_add(2);
	for(auto i: _log){
		auto time_point = std::chrono::system_clock::to_time_t(i.first);
		auto time = std::ctime(&time_point);
		auto name = i.second;
		std::cout << "Name {" << name << "} added at time: " << time << '\n';
	}
	return 0;
}
