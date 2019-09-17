#include "node.h"
#include <ostream>
#include <iostream>


template<typename T>
class Queue{
    private:
        std::shared_ptr<Node<T>> top_node;
        std::shared_ptr<Node<T>> bottom_node;

    public:
        Queue():top_node(nullptr),bottom_node(nullptr){};
        Queue(T const& data_in):top_node(std::make_shared<Node<T>>(data_in)),bottom_node(top_node){
            std::cout << "Top: " << *this->top_node;
            std::cout << "Bottom: " << *this->top_node;
            std::cout << std::endl;
        };

        void push(T const& data_in);
        T pop();
        T const& top();
        bool is_empty(){return this->top_node == nullptr;};

        void print_from_bottom(){
            std::shared_ptr<Node<T>> current = this->bottom_node;
            while(current){
                std::cout << *current;
                current = current->get_prev_node();
            }
            std::cout << std::endl;
        }   

        friend std::ostream & operator<<(std::ostream& stream, Queue<T> prnt_q){
            while(prnt_q.top_node != nullptr){
                stream << prnt_q.top_node.get()->get_data();
                prnt_q.top_node = prnt_q.top_node->get_next_node();
            }
            return stream << '\n';
        }
};



template<typename T>
void Queue<T>::push(T const& data_in){

    if(this->is_empty()){
        this->top_node = std::make_shared<Node<T>>(data_in);
    }else if(this->top_node == this->bottom_node) {
        this->top_node = std::make_shared<Node<T>>(data_in, this->top_node);
        this->bottom_node->set_next_node(nullptr);
        this->bottom_node->set_prev_node(this->top_node);
        std::cout << "t" << this->bottom_node->get_prev_node() << '\n';
        // this->top_node->get_next_node()->set_prev_node(this->top_node);
    }else{

    }
    }


/*push old
if(this->bottom_node == this->top_node){
        this->bottom_node = std::make_shared<Node<T>>(*this->top_node); //set bottom_node to 0

        this->top_node = std::make_shared<Node<T>>(data_in, this->bottom_node); //set top to 1

        this->bottom_node->set_previous_node(this->top_node); //set 0->prev 1

        std::cout << "2nd Case: " << *this->top_node->get_next_node()->get_prev_node() << '\n';
    }else{

        std::cout<< "Top Node Before: " << *this->top_node << ' ' << *this->top_node->get_next_node() << '\n';
        std::shared_ptr<Node<T>> temp = std::make_shared<Node<T>>(data_in, this->top_node);
        this->top_node = temp;
        this->top_node->get_next_node()->set_previous_node(temp);

        std::cout << "3rd Case: " << *this->top_node->get_next_node()->get_prev_node() << '\n';
    }
    // std::cout << this->top_node.use_count() << ' ' << this->bottom_node.use_count() << '\n'; 
*/

template<typename T>
T Queue<T>::pop() {
    auto t = this->bottom_node->get_data();
    std::cout << *this->bottom_node->get_prev_node() << ' ' << this->bottom_node.use_count() << '\n';

    this->bottom_node = this->bottom_node->get_prev_node();

    std::cout << *this->bottom_node << ' ' << this->bottom_node.use_count() << '\n';
    return t;
}