#include <gtest/gtest.h>
#include<numb10/merge_sort.hh>
#include <thread>
#include <iostream>
#include <vector>


TEST(merge, sort) {
        unsigned int threads_count =thread::hardware_concurrency();
        vector<int> x;
        vector<int> y;
        vector<int> buff1;
        generate_int_array(x, 1000);
        for (int i = 0; i < 1000; ++i){
                y.push_back(x[i]);
                buff1.push_back(0);
        }
        merge_sort(x, buff1, 1000, 0);
        merge_sort_multithread(y, buff1, threads_count);
        EXPECT_EQ(x, y);

        vector<int> z;
        vector<int> c;
        vector<int> buff2;
        generate_int_array(z, 10000);
        for (int i = 0; i < 10000; ++i){
                c.push_back(z[i]);
                buff2.push_back(0);
        }
        merge_sort(z, buff2, 10000, 0);
        merge_sort_multithread(c, buff2, threads_count);
        EXPECT_EQ(z, c);
	
        vector<int> q;
        vector<int> w;
        vector<int> buff3;
        generate_int_array(q, 100000);
        for (int i = 0; i < 100000; ++i){
                w.push_back(q[i]);
                buff3.push_back(0);
        }
        merge_sort(q, buff3, 100000, 0);
        merge_sort_multithread(w, buff3, threads_count);
        EXPECT_EQ(q, w);

        vector<int> e;
        vector<int> r;
        vector<int> buff4;
        generate_int_array(e, 1000000);
        for (int i = 0; i < 1000000; ++i){
                r.push_back(e[i]);
                buff4.push_back(0);
        }
        merge_sort(e, buff4, 1000000, 0);
        merge_sort_multithread(r, buff4, threads_count);
        EXPECT_EQ(e, r);
	
	vector<int> n;
        vector<int> m;
        vector<int> buff5;
        generate_int_array(n, 10000000);
        for (int i = 0; i < 10000000; ++i){
                m.push_back(n[i]);
                buff5.push_back(0);
        }
        merge_sort(n, buff5, 10000000, 0);
        merge_sort_multithread(m, buff5, threads_count);
        EXPECT_EQ(n, m);
}
