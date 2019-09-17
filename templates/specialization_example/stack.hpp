#include <dequeue>
#include <string>
#include <cassert>

template<> //specification template class 
class Stack<std::string> { //handles strings specifically
	private:
		std::dequeue<std::string> elements;

	public:

		
		void push(std::string const&);//pushes onto stack
		void pop(); //pops off stack
		std::string const& top() const; //returns a reference of the element at the top of the stack
		
		bool empty() const {
			return elements.empty();
		}
		
		void Stack<std::string>::push(std::string const& element_in) {
			this->elements.push_back(element_int);
		}

		void Stack<std::string>::pop() {
			assert(not elements.empty()) //not empty check 
			this->elements.pop_back();
		}

		std::string const& Stack<std::string>::top() const{
			assert(not elements.empty()); //not empty check
			return this->elements.back();
		}


};