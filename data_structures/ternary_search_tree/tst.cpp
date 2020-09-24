#include "tst.h"

tsTree::tsTree(){
}


tsTree::tsTree(std::string word){
}

void tsTree::insert_word(std::string& i_word){
	if(i_word.empty()) return; //bounds check

	Node n(i_word.front());
	std::string n_word = i_word.erase(0,1);
	
	//initalizing the tree, else recursively insert using helper function
	if(not this->base){
		this->base = std::make_unique<Node>(n);
		//print out from bottom
	}else{
		if(not n_word.empty()) this->insert_word(n_word);
	}

}


std::string tsTree::search(std::string s_word){


	return s_word;	
}


void tsTree::print(){
	if(this->base == nullptr){
		std::cout << "Dictionary is Empty\n";
		return;
	}
	
	//printing first word
	Node* temp = this->base->mid_tail;
	int count = 0;
	while(temp != nullptr){
		std::cout << count++ << " " <<  temp->letter;
		temp = temp->mid_tail;
	}
	std::cout << std::endl;


}
