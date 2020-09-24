#include "LL.h"
#include <gtest/gtest.h>

TEST(NodeAppendTest, AppendInput){
    int i = 0;
    int size = 3;
    List<int> ls(i);
    ASSERT_EQ(ls.get_size(), 1);
    for(; i < size-1; i++){
        ls.append(i);
    }
    ASSERT_EQ(ls.get_size(), size);
    ASSERT_FALSE(ls.get_size() == 0);
}


TEST(ConstructorTest, AllContstructors){
    int i = 0;
    List<int> ls(i);
    ASSERT_FALSE(ls.get_size() == 0);
}

TEST(NodeDeleteTest, CorretSize){
    int i = 0;
    List<int>* ls = new List<int>(i);
    
    //test full delete
    for(; i < 3; i++){
        ls->append(i);
    }
    for(; i >= 0; i--)
        ls->pop_last();
    ASSERT_EQ(ls->get_size(), 0);

    //test static vs temporary
    int a = 0, b = 1, c = 2;
    ls->append(a);
    ls->append(b);
    ls->append(c);
    ls->pop_last();
    ls->append(2);
    ls->append(a);
    ls->append(3);
    EXPECT_EQ(ls->get_size(), 5);
    ls->pop_last();
    ls->pop_last();
    EXPECT_EQ(ls->get_size(), 3);
    ls->pop_last();
    ls->pop_last();
    ls->pop_last();
    EXPECT_EQ(ls->get_size(), 0);
    delete ls;
}

TEST(NodeDeleteTest, inCorrectSize){
    List<int> list(0);
    EXPECT_FALSE(list.get_size() == 0);
    list.append(1);
    EXPECT_FALSE(list.get_size() == 0);
    EXPECT_FALSE(list.get_size() == 3);

}


int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}