#include "Tree.h"


Tree::Tree(){
	this->head = nullptr;
}

Tree::Tree(Node<T>& header):head(header){}

Tree::Tree(Tree<T>& tree):head(tree.head), childer(tree.children){}

Tree::~Tree(){
	if(head) delete head;
}
