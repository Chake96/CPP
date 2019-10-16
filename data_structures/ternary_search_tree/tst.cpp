#include "tst.h"


tsTree::tsTree(){
}


tsTree::tsTree(std::string word){
}

//recursive
void tsTree::insert_word(std::string& i_word){
	Node n;
	if(i_word.empty()) return; //bounds checking & end of word
	else if(not this->base){
		n.letter = i_word.front();	
		this->base = std::make_unique<Node>(n);
	}else if(this->base){

	}else{

	}
	std::string n_word = i_word.erase(0,1);
	if(not n_word.empty()) this->insert_word(n_word);
}



std::string tsTree::search(std::string s_word){


	return s_word;	
}


void tsTree::print(){


}
