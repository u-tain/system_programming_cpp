#include <gtest/gtest.h>
#include<iostream>
#include<numb5/message.hh>
#include<numb5/cat.hh>
#include<numb5/tie.hh>
#include <sstream>

using namespace std;

TEST(templates, messages){
        stringstream os;
        message(os, "% + % = %\n", 'a', 2, 3.0);
        string x;
        x = os.str();
        EXPECT_EQ(x, "a + 2 = 3\n");
  
        os.str("");
        message(os, "% + % = %\n", 'a', 2);
        string y;
        y = os.str();
        EXPECT_EQ(y, "a + 2 = %\n");
  
        os.str("");      
        message(os, "% + % = 5\n", 'a', 2, 3.0);
        string z;
        z = os.str();
        EXPECT_EQ(z, "a + 2 = 5\n");
  
        os.str("");      
        message(os, "% + % = %\n"); 
        string c;
        c = os.str();
        EXPECT_EQ(c, "% + % = %\n");
  
        os.str("");      
        message(os);
        string v;
        v = os.str();
        EXPECT_EQ(v, "");
  
        os.str("");
        message();
        string b;
        b = os.str();
        EXPECT_EQ(b, "");
}

TEST(templates, cat){
        array<float, 3> vec1{ 1.0f,2.0f,3.0f };
        array<float, 3> vec2{ 4.0f,5.0f,6.0f };
        array<float, 6> vec3 = cat(vec1, vec2);
        array<float, 6> vec4{ 1.0f,2.0f,3.0f,4.0f,5.0f,6.0f};
        EXPECT_EQ(vec3, vec4);
        
        array<float, 3> vec5= cat(vec1);
        EXPECT_EQ(vec5, vec1);
  
        array<float, 3> vec6 = { 7.0f,8.0f,9.0f };
        array<float, 9> vec7 = cat(vec1,vec2,vec6);
        array<float, 9> vec8{ 1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f};
        EXPECT_EQ(vec7, vec8);
        
        array<float, 3> vec9 = { 10.0f,11.0f,12.0f };
        array<float, 12> vec10 = cat(vec1,vec2,vec6,vec9);
        array<float, 12> vec11{ 1.0f,2.0f,3.0f,4.0f,5.0f,6.0f,7.0f,8.0f,9.0f,10.0f,11.0f,12.0f};
        EXPECT_EQ(vec10, vec11);
}
  
