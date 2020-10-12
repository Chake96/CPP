#include <memory>
#include "add.hpp"
#include <iostream>
#include "assert.h"
int main(){
	int a = 5, b = 10;
	auto c = add(a,b);
	assert(typeid(c) == typeid(int));
	double d = 0.5, e = 500.6;
	auto f = add(d,e);
	assert(typeid(f) == typeid(double));
	return 0;
}
