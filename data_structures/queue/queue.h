#include "node.h"

#include<iostream>


template<typename T>
class Queue{
    
    private:
        std::shared_ptr<Node<T>> head;
        std::shared_ptr<Node<T>> tail;
        bool check_all_links();

    public:
        Queue():head(nullptr),tail(nullptr){};
        Queue(T const& data_in):head(std::make_shared<Node<T>>(Node<T>(data_in))),tail(this->head){};

        void push(T const& data_in);
        T pop();
        // bool prevs_good();

        bool is_empty(){return this->head == nullptr;};

        friend std::ostream& operator<<(std::ostream& stream, Queue<T> prnt_q){
            std::shared_ptr<Node<T>> current = prnt_q.head;
            while(current){
                stream << *current;
                current = current->get_next_node();
            }
            return stream << '\n';
        }

};

template<typename T>
void Queue<T>::push(T const& data_in){

    if(this->head == nullptr && this->tail ==nullptr){
        this->head = std::make_shared<Node<T>>(Node<T>(data_in, this->tail));
        this->head->set_next_node(this->tail);
        this->tail = head; //std::make_shared<Node<T>>(Node<T>(*this->head));
        std::cout << "Head:\n" << *this->head << "\n\tNext: " << this->head->get_next_node()
        <<  "\nTail:\n" << *this->tail << "\n\tNext: " << this->tail.get()->get_next_node() <<
        "\n\tPrevious: \n";
    }else if(this->head == this->tail){
        std::shared_ptr<Node<T>> temp = std::make_shared<Node<T>>(*this->head);
        this->head = std::make_shared<Node<T>>(Node<T>(data_in, temp));
        this->head->set_prev_node(nullptr);
        this->head->get_next_node()->set_prev_node(this->head);
        this->head->get_next_node()->set_next_node(this->tail);
        this->tail->set_next_node(nullptr);

        temp = this->tail;
        std::cout << *this->tail->get_prev_node()->get_prev_node();
        std::cout << "Test\n";
        while(temp){
            std::cout << "Tail Print: " << *temp;
            temp = temp->get_prev_node();
        }

    }else{
        
    }
}


// template<typename T>
// bool Queue<T>::prevs_good(){
//     std::shared_ptr<Node<T>> current = this->head->get_next_node();
//     for(current; current != nullptr; current = current->get_next_node()){
//         if(current->get_prev_node()){
//             std::cout <<  current->get_prev_node() << ' ';
//         }else{
//             return false;
//         }

//     }
// }



template<typename T>
T Queue<T>::pop(){
    T val;
    val = this->tail->get_data();
    if(this->tail.unique()) std::cout << "True\n";
    
    std::cout << *this->tail << '\n';
    std::cout << *this->tail->get_prev_node() << '\n';

    return val;
}


