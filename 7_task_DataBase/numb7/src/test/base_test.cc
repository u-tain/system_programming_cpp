#include <gtest/gtest.h>
#include <algorithm>
#include <numb7/database.hh>

using namespace std;

TEST(database,first){
        vector<Account> v = LoadData(10, 20, 30, 40, 50);  
        auto res1 = task_1(v); 
        EXPECT_EQ(20, res1.size());
  
        vector<Account> b = LoadData(100, 150, 200, 250, 300);  
        auto res2 = task_1(b); 
        EXPECT_EQ(150, res2.size());
}
TEST(database,second){
        vector<Account> v = LoadData(10, 20, 30, 40, 50);  
        auto res1 = task_2(v); 
        EXPECT_EQ(150, res1.size());
  
        vector<Account> b = LoadData(100, 200, 300, 400, 500);  
        auto res2 = task_2(b); 
        EXPECT_EQ(1000, res2.size());
}
TEST(database,third){
        vector<Account> v = LoadData(10, 20, 30, 40, 50);  
        auto res1 = task_3(v); 
        EXPECT_EQ(10, res1["/bin/sh"]);
        EXPECT_EQ(20, res1["/bin/bash"]);
        EXPECT_EQ(30, res1["/bin/ksh"]);
        EXPECT_EQ(40, res1["/bin/csh"]);
        EXPECT_EQ(50, res1["/bin/tcsh"]);
  
        vector<Account> b = LoadData(100, 150, 200, 250, 300);  
        auto res2 = task_3(b); 
        EXPECT_EQ(100, res2["/bin/sh"]);
        EXPECT_EQ(150, res2["/bin/bash"]);
        EXPECT_EQ(200, res2["/bin/ksh"]);
        EXPECT_EQ(250, res2["/bin/csh"]);
        EXPECT_EQ(300, res2["/bin/tcsh"]);
  
        vector<Account> n = LoadData(10, 15, 20, 0, 30);  
        auto res3 = task_3(n); 
        EXPECT_EQ(10, res3["/bin/sh"]);
        EXPECT_EQ(15, res3["/bin/bash"]);
        EXPECT_EQ(20, res3["/bin/ksh"]);
        EXPECT_EQ(0, res3["/bin/csh"]);
        EXPECT_EQ(30, res3["/bin/tcsh"]);
}
TEST(database,fourth){
        vector<Account> v = LoadData(10, 20, 30, 40, 50,4);  
        auto res1 = task_4(v); 
        EXPECT_EQ(4, res1.size());
  
        vector<Account> b = LoadData(100, 200, 300, 400, 500,25);  
        auto res2 = task_4(b); 
        EXPECT_EQ(25, res2.size());
}
