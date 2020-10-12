#include <optional>
#include <iostream>



std::optional<int> create_big_int(bool b){
	int ret = 210000000;
	if(b == true) 
		return ret;
	return std::nullopt;
}


int main(){
	std::optional<int> oint = create_big_int(false);
	if(oint){
		std::cout << "big value created: " << oint.value() << '\n';
	}else{
		std::cout << "big value not created "  << '\n';
	}

	std::optional<int> oint2 = create_big_int(true);
	if(oint2){
		std::cout << "big value created: " << *oint2 << '\n';
	}else{
		std::cout << "big value not created "  << '\n';
	}

}
