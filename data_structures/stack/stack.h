
#include <ostream>
#include <cstddef>
#include "node.h"




template<typename T> class Stack{
    
    private:
        std::unique_ptr<Node<T>> head;

    public:
        Stack():head(nullptr){};
        Stack(T const& data_in):head(new Node<T>(data_in)){};
        void push(T const& new_data);
        void push(T && new_data);
        void pop();
        T const& top();
        bool is_empty(){return this->head == nullptr;};

        friend std::ostream& operator<<(std::ostream& stream, Stack<T> const& prnt_stack){
            auto current = prnt_stack.head.get();
            std::size_t node_num = 0;
            while(current != nullptr){
                stream << "Node " << node_num  << ": [" << *current << ']';
                current = current->next_node.get();
            }
            return stream << '\n';
        }
};


template<typename T>
void Stack<T>::push(T const& data_in){
    this->head = (std::make_unique<Node<T>>(data_in, std::move(head)));
}

template<typename T>
void Stack<T>::push(T && data_in){
    this->head = std::make_unique<Node<T>>(std::move(data_in), std::move(head));
}

template<typename T>
void Stack<T>::pop(){
    if(this->head == nullptr) return;
    this->head= std::move(this->head->next_node);
}

template<typename T>
T const& Stack<T>::top(){
    return this->head.get()->get_data();
}
