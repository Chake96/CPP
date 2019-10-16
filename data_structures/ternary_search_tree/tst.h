//tst.h
#ifndef TST_H
#define TST_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>


//simple node struct, represents a letter in a word, end_word is true if the node is the end of a word
typedef struct node{
	char letter;
	bool end_word = false;
	std::shared_ptr<node> head;
	std::shared_ptr<node> lft_tail, rght_tail, mid_tail;
}Node;


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
