#ifndef LL_H
#define LL_H

#include <cstddef>
#include "Node.h"
#include <iostream>

template<class T>
class List{
    private:
        Node<T>* header{nullptr};
        std::size_t list_size{0};

    public: 
        List(T data_in);
        ~List();
        List<T>& operator=(const List<T>& rhs);
        void append(T data_in);
        void pop_last();

        std::size_t get_size(){return this->list_size;}


        //interal to ensure ls does not give up privacy
        friend std::ostream& operator<<(std::ostream & stream, List<T> const& ls){
                Node<int>* curr = ls.header;
                for(; curr != nullptr; curr = curr->next)
                    stream << *curr;
                return stream;
        }
};

template<typename T>
List<T>::List(T data_in){
    this->header = new Node<T>(data_in);
    this->list_size += 1;
}

template<typename T>
List<T>::~List(){
    Node<T>* curr = header;
    Node<T>* next = nullptr;
    while(curr){
        next = curr->get_next();
        delete curr;
        curr = next;
    }
    header = nullptr;
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& rhs){
    this->header = rhs.header;
}


template<typename T>
void List<T>::append(T ap_data){
    Node<T>* temp = this->header;
    this->header = new Node<T>(ap_data);
    this->header->next = temp;
    temp = nullptr;
    this->list_size += 1;
}

template<typename T>
void List<T>::pop_last(){
    Node<T>* target = this->header;
    this->header = this->header->next;
    delete target;
    this->list_size -= 1;
}

#endif