#ifndef SIMPLE_MAX_FUNCTIONS_H
#define SIMPLE_MAX_FUNCTIONS_H

template<typename T>
T max(T a, T b){
	return b < a ? a : b;
}


#endif
