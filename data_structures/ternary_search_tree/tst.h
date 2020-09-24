//tst.h
#ifndef TST_H
#define TST_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>


//simple node struct, represents a letter in a word, end_word is true if the node is the end of a word

typedef struct Node{
	char letter;
	bool end_word = false;
	struct Node* head;
	struct Node* lft_tail;
	struct Node* rght_tail; 
	struct Node* mid_tail;

	Node(const char& in_lttr):letter(in_lttr){}; //initalize node with a value
};


class tsTree{
	private:
		std::unique_ptr<Node> base;

	public:
		tsTree();
		tsTree(std::string word);
		
		void insert_word(std::string& word);
		std::string search(std::string);
		void print();
};


#endif
