#include <gtest/gtest.h>
#include<iostream>
#include<linalg/linalg.hh>

using namespace std;

TEST(lazy_evaluatuion, unary_minus){
        using T = float;
        Vector<T> a{ 1, 2, 3 }, b{0, 0}, c{-1,-2,-3};
        EXPECT_EQ(c, -a);
        EXPECT_EQ(b, -b);
}

TEST(lazy_evaluatuion, sravnenie) {
        Vector<float> a{ 1, 2, 3 }, b{ 4,5,6 }, c{ 7,8,9 }, d{1,12,3};
        Vector<int> e{1,1,1}, v{0,0,0}, x{1,0,1};
        EXPECT_EQ(e, a<b);
        EXPECT_EQ(v, c<b);
        EXPECT_EQ(v, a<a);
        EXPECT_EQ(x, d<b);                                                                                     
}

TEST(lazy_evaluatuion, Bin_minus) {
        using T = float;
        Vector<T> a{ 1, 2, 3 }, b{ 4,5,6 }, c{ 7,8,9 }, e{3,3,3}, v{0,0,0}, q{-3,-3,-3};
        EXPECT_EQ(q, a-b);
        EXPECT_EQ(e, c-b);
        EXPECT_EQ(v, a-a);
}

TEST(lazy_evaluatuion, ternarm_oper) {
        using T = float;
        Vector<T> a{ 1, 2, 3 }, b{ 4,5,6 }, c{ 7,8,9 };
        EXPECT_EQ(where(a < b, b, c), b);
        EXPECT_EQ(where(c < b, b, c), c);
        EXPECT_EQ(where(c < c, b, c), c);
}
