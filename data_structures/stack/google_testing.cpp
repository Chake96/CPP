#include <gtest/gtest.h>
#include "stack.h"

#include <iostream>
#include <sstream>
#include <queue>

class StackTest: public ::testing::Test{
    protected:
        Stack<int> int_stack;      
        Stack<std::string> str_stack;
        std::string test_str = "test";
        int test_int = 0; 

        StackTest(){
           

        }
        virtual ~StackTest(){
        }

};


TEST_F(StackTest, EmptyTest){
    EXPECT_TRUE(int_stack.is_empty());
    int i = 0;
    Stack<int> a(i);
    EXPECT_FALSE(a.is_empty());
}

TEST_F(StackTest, PushPopTest){
    int_stack.push(test_int);
    EXPECT_FALSE(int_stack.is_empty());
    str_stack.push(test_str);
    EXPECT_FALSE(str_stack.is_empty());

    int_stack.pop();
    str_stack.pop();
    EXPECT_TRUE(int_stack.is_empty());
    EXPECT_TRUE(str_stack.is_empty());
}

TEST_F(StackTest, TopTest){
    int_stack.push(test_int);
    str_stack.push(test_str);
    EXPECT_TRUE(int_stack.top() == 0);
    EXPECT_TRUE(str_stack.top() == "test");

    //testing top failure
    int_stack.pop();
    int_stack.pop();
    int_stack.top();
}

TEST_F(StackTest, ostreamTest){
    int_stack.push(test_int);
    str_stack.push(test_str);
    std::stringstream expected_result;
    std::stringstream actual_result;
    actual_result << int_stack;
    expected_result  << "Node 0: [Value: 0]\n";
    EXPECT_EQ(expected_result.str(), actual_result.str());

    actual_result << str_stack;
    expected_result << "Node 0: [Value: test]\n";
    EXPECT_EQ(expected_result.str(), actual_result.str());
}


int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}