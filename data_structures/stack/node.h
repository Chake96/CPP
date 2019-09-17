#include <ostream>
#include <memory>


template<typename U>
class Node{
    private:
        U n_data;
    public:
        
        std::unique_ptr<Node<U>> next_node;
        
        Node():next_node(nullptr){};
        Node(U const& data_in):n_data(data_in){};
        Node(U const& data_in, std::unique_ptr<Node> n_node):n_data(data_in),next_node(std::move(n_node)){};
        Node(U&& data_in, std::unique_ptr<Node<U>> n_node):n_data(std::move(data_in)),next_node(std::move(n_node)){};
        U const& get_data(){return this->n_data;};

        
        friend std::ostream& operator<<(std::ostream& stream, Node<U> const& rhs){
            return stream << "Value: " << rhs.n_data;
        }
};