#include <ostream>
#include <memory>
#include <string>

template<typename T>
class Node{


    private:
        std::shared_ptr<Node<T>> next_node;
        std::shared_ptr<Node<T>> prev_node; //making doubly-linked for easier pop
        T data;

    public:
        Node():next_node(nullptr){};
        Node(T const& data_in):next_node(nullptr),prev_node(nullptr),data(data_in){};
        Node(T const& data_in, std::shared_ptr<Node<T>> nxt_node):next_node(nxt_node),data(data_in),prev_node(nullptr){};
        Node(T const& data_in, std::shared_ptr<Node<T>> nxt_node, std::shared_ptr<Node<T>> prev_node):next_node(nxt_node),data(data_in),prev_node(prev_node){};
        
        Node(std::shared_ptr<Node<T>> cp_node):data(cp_node.get_data()),next_node(cp_node.get_next_node()),prev_node(cp_node.get_prev_node()){};

        void set_next_node(std::shared_ptr<Node<T>> prev_node){this->prev_node = std::move(prev_node);};
        void set_prev_node(std::shared_ptr<Node<T>> prev_node){this->prev_node = prev_node;};
        std::shared_ptr<Node<T>> get_next_node(){return this->next_node;};
        std::shared_ptr<Node<T>> get_prev_node(){return this->prev_node;};
        T get_data(){return this->data;};



        friend std::ostream & operator<<(std::ostream& stream, Node<T> node){
            stream << "Value: " << node.get_data() << ' ';
            return stream;
        }
};