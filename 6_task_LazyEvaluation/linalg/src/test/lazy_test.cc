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
        using T = int;
        Vector<float> a{ 1, 2, 3 }, b{ 4,5,6 }, c{ 7,8,9 }, e{1,1,1}, v{0,0,0};
        Vector<T> d = a<b;
        EXPECT_EQ(e, d);
    
        Vector<T> n = c<b;
        EXPECT_EQ(v, n);
    
        Vector<T> m = a<a;
        EXPECT_EQ(v, m);
}

TEST(lazy_evaluatuion, Bin_minus) {
        using T = float;
        Vector<T> a{ 1, 2, 3 }, b{ 4,5,6 }, c{ 7,8,9 }, e{3,3,3}, v{0,0,0}, q{-3,-3,-3};
        Vector<T> d = a-b;
        EXPECT_EQ(q, d);
    
        Vector<T> n = c-b;
        EXPECT_EQ(e, n);
    
        Vector<T> m = a-a;
        EXPECT_EQ(v, m);
}

TEST(lazy_evaluatuion, ternarm_oper) {
        using T = float;
        Vector<T> a{ 1, 2, 3 }, b{ 4,5,6 }, c{ 7,8,9 };
        Vector<T> d(where(a < b, b, c));
        EXPECT_EQ(b, d);
    
        Vector<T> e(where(c < b, b, c));
        EXPECT_EQ(e, c);
    
        Vector<T> n(where(c < c, b, c));
        EXPECT_EQ(n, c);
}
