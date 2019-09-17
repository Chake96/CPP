#include  "stack.hpp"
#include <iostream>
#include <string>

template<typename T>
void Stack<T>::push (T const& elem){ 
	    elems.push_back(elem); // append copy of passed elem
}

template<typename T>
T Stack<T>::pop (){ 
	    assert(!elems.empty());
	    T elem = elems.back(); // save copy of last element
	    elems.pop_back(); // remove last element
	    return elem; // return copy of saved element
}

template<typename T>
T const& Stack<T>::top () const{
	    assert(!elems.empty());
	        return elems.back(); // return copy of last element
}

int main(){ 
	    Stack< int> intStack; // stack of ints
	        Stack<std::string> stringStack; // stack of strings
		    // manipulate int stack
		    intStack.push(7);
		    std::cout << intStack.top() << '\n';
		    // manipulate string stack
		    stringStack.push("hello");
		    std::cout << stringStack.top() << '\n';
		    stringStack.pop();
}
