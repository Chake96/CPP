#ifndef NODE_H
#define NODE_H

#include <ostream>

template<typename U>
class Node{

    private:
        U data;
        
    public:   
        Node<U>* next{nullptr}; //{} used to initalize to defaults
        Node(U data);
        Node();
        Node(Node<U>& node);

        Node<U>* get_next(){return this->next;}
        U& get_data(){return this->data;}
        Node<U>& operator=(const Node<U>& rhs);
        friend std::ostream& operator<<(std::ostream & strm, Node<U> const& node){
            strm << node.data << ' ';
            return strm;
        }
        
};

template<typename U>
Node<U>::Node(Node<U>& node):data(node.data),next(node.next){}

template<typename U>
Node<U>::Node(U node_data):data(node_data){};

template<typename U>
Node<U>& Node<U>::operator=(const Node<U>& rhs){
    this->next = rhs.next;
    this->data = rhs.data;
    return *this;
}

#endif 