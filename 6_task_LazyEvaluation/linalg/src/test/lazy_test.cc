#include <gtest/gtest.h>
#include<iostream>
#include(linalg/linalg.hh>

using namespace std;

TEST(lazy_evaluatuion, unary_minus){
    using T = float;
    Vector<T> a{ 1, 2, 3 }, b{0, 0}, c{-1,-2,-3};
    Vector<T> d = -a;
    EXPECT_EQ(c, d);
    
    Vector<T> e = -b;
    EXPECT_EQ(b, e);
}

TEST(lazy_evaluatuion, sravnenie) {
        vector<float> x;
        vector<float> y = {2,1};
        vector<float> z = {2};
        x.push_back(2);
        EXPECT_EQ(z, x);
        x.push_back(1);
        EXPECT_EQ(y, x);
}
