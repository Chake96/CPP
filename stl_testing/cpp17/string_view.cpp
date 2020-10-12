#include <optional>
#include <string_view>
#include <string>
#include <iostream>

int main(){
	std::string test = " this is a test string";
	std::string_view str_view(test);
	auto begin = str_view.begin();
	while(begin != str_view.end()){
		std::cout << *begin << ',';
		begin += 1;
	}
	std::cout << '\n';
	std::string test2 = "we changed the string!";
	str_view= std::string_view(test2);
	std::cout << ((str_view.find("we") != std::string::npos)? "we found the string!":"string not found") << '\n';
	std::cout << ((str_view.find("yes") != std::string::npos)? "we found the string!":"string not found") << '\n';
	for(auto c: str_view)
		std::cout << c;
	std::cout << '\n';
	return 0;
}
