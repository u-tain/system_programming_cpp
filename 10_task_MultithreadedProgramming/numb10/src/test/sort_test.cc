#include <gtest/gtest.h>
#include<numb10/merge_sort.hh>
#include <thread>
#include <iostream>
#include <vector>

using namespace std;
TEST(merge, sort) {
        unsigned int threads_count = hardware_concurrency();
        vector<int> x;
        vector<int> y;
        vector<int> buff1;
        generate_int_array(x, 1000);
	for (int i = 0; i < 1000; ++i)
		y.push_back(x[i]);
                buff1.push_back(0);
        merge_sort(x, buff1, 1000, 0);
        merge_sort_multithread(y, buff1, threads_count);
        EXPECT_EQ(x, y);

}
