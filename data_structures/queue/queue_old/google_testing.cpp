#include <gtest/gtest.h>

#include "queue.h"
#include <string>
#include <sstream>

class QueueTest : public ::testing::Test{
    protected:
        int test_int = 0;
        std::string test_string = "test";
        Queue<int> int_q;
        Queue<std::string> str_q;


        QueueTest(){           
        }

        ~QueueTest(){

        }

};

TEST_F(QueueTest, Init1ArgTest){
    int pass_builtin = 1;
    Queue<int>* int_qpt = new Queue<int>(0);
    Queue<int>* int_qpt2 = new Queue<int>(pass_builtin);
    Queue<std::string>* str_qpt = new Queue<std::string>("test1");
    std::string test_2 = "test2";
    Queue<std::string>* str_qpt2 = new Queue<std::string>(test_2);
    delete int_qpt;
    delete int_qpt2;
    delete str_qpt;
    delete str_qpt2;
}

TEST_F(QueueTest, EmptyTest){
    EXPECT_TRUE(int_q.is_empty());
    EXPECT_TRUE(int_q.is_empty());
}


//tests push into various Queue<T>, 
TEST_F(QueueTest, PushTest){
    EXPECT_TRUE(int_q.is_empty());  
    EXPECT_TRUE(str_q.is_empty());  
    int_q.push(test_int);   
    str_q.push(test_string);
    EXPECT_FALSE(int_q.is_empty()); 
    EXPECT_FALSE(int_q.is_empty());
    int_q.push(test_int);   
    str_q.push(test_string);
    int_q.push(test_int);   
    str_q.push(test_string);
    EXPECT_FALSE(int_q.is_empty()); 
    EXPECT_FALSE(int_q.is_empty());
}

TEST_F(QueueTest, PopTest){
    Queue<int>* test_q = new Queue<int>(0);
    test_q->push(0);
    test_q->push(0);
    test_q->pop();
    EXPECT_FALSE(test_q->is_empty());
    test_q->pop();
    EXPECT_TRUE(test_q->is_empty());
    delete test_q;
}

TEST_F(QueueTest, PrintQueueTest){
    std::stringstream expected("0000000000\n");
    std::stringstream result("");
    for(int i = 0; i < 10; i++)
        int_q.push(test_int);
    result << int_q;
    EXPECT_EQ(result.str(), expected.str());    
}

TEST(NodeTest, PrintNode){
    Node<std::string> test("test");
    std::stringstream expected("Value: test ");
    std::stringstream result("");
    result << test;
    EXPECT_EQ(result.str(), expected.str());

}
int main(int argc, char** argv){

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}