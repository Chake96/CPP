#include <vector>
#include <assert.h>

template<typename T>
class Stack {
	    private:
	            std::vector<T> elems; // elements
	    public:
	            void push(T const& elem); // push element
	            T pop(); // pop element
	            T const& top() const; // return top element
		    bool empty() const { // return whether the stack is empty
			    return elems.empty();										        } 
};
