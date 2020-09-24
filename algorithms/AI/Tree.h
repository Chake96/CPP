#ifndef TREE_H
#define TREE_H

#include <vector>

template<typename T>
class tree: public Node{
	private:
		Node<T>* head;
		std::vector<Node<T>> children;
	
	public:
		Tree();
		Tree(Node<T>& node);
		virtual ~Tree();
		Node<T>* get_head(){return this->head;}

} Tree;
