#include <gtest/gtest.h>
#include "Tree.h"

#include <iostream>

class TreeTest: public ::testing:Test{
	protected:
		Tree<int> int_tree;
		const int test_int = 0;

		TreeTest(){

		}

		~TreeTest() override{

		}

		void SetUp() override{
		}

		void TearDown() override{
			if(!int_tree->children.empty()){
				for(auto child:int_tree->children){
					delete child;
				}
			}
			if(!int_tree.head){
				delete int_tree.head;
			}
		}
};

TEST_F(TreeTest, TreeConstructor){
	int_tree = new Tree(new Node<int>(test_int));

}


int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
