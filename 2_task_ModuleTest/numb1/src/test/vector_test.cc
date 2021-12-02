#include <gtest/gtest.h>
#include <algorithm>
#include <cmath>
#include <fstream>
using namespace std;

TEST(vector, size) {
        vector<float> x;
        EXPECT_EQ(0u, x.size());
        x.push_back(1);
        EXPECT_EQ(1u, x.size());
}

TEST(vector, push_back) {
        vector<float> x;
        vector<float> y = {2,1};
        vector<float> z = {2};
        x.push_back(2);
        EXPECT_EQ(z, x);
        x.push_back(1);
        EXPECT_EQ(y, x);
}

TEST(vector, pop_back) {
        vector<float> x = {1, 2, 3, 4};
        vector<float> y = {1, 2, 3};
        x.pop_back();
        EXPECT_EQ(y, x);
        vector<float> z = {1, 2};
        x.pop_back();
        EXPECT_EQ(z, x);
}

TEST(vector, erase) {
        vector<float> x = {1,2,3,4};
        x.erase(x.begin()+1);
        vector<float> y = {1,3,4};
        EXPECT_EQ(y, x);
        x.erase(x.begin()+1, x.end());
        vector<float> z = {1};
        EXPECT_EQ(z, x);
}

TEST(vector, begin) {
        vector<float> x = {1,2,3,4};
        EXPECT_EQ({1}, *x.begin());
        x.erase(x.begin());
        EXPECT_EQ({2}, *x.begin());
}

TEST(vector, end) {
        vector<float> x = {1,2,3,4};
        EXPECT_EQ({4}, *(x.end()-1));
        x.erase(x.end()-1);
        EXPECT_EQ({3}, *(x.end()-1));
}

TEST(vector, vector_const_vector) {
        const vector<float> x = {1, 2};
        vector<float> y (x);
        EXPECT_EQ(x,y);
}

TEST(vector, vector_vector) {
        vector<float> x = {1,2,3,4};
        vector<float> y = {1,2,3,4};
        vector<float> z(move(x));
        EXPECT_EQ(y, z);
}

TEST(vector, oper_const_vector) {
        const vector<float> x{1,2,3};
        vector<float> y;
        y  = x;
        EXPECT_EQ(x,y);
}

TEST(vector, oper_vector) {
        vector<float> x{1,2,3,4};
        vector<float> y{1,2,3,4};
        vector<float> z;
        z = move(x);
        EXPECT_EQ(y,z);
}

//параметризированный тест
template <class T>
struct Erase_params {
        vector<T> elements;
        size_t start_index;
        size_t end_index;
        vector<T> result;
};
class sha1_test: public ::testing::TestWithParam<Erase_params<int>> {};

TEST_P(sha1_test, _){
        const Erase_params<int>& param = GetParam();
        vector<int> sha=param.elements;
        sha.erase(sha.begin()+param.start_index, sha.begin()+param.end_index);
        EXPECT_EQ(param.result, sha);
}

INSTANTIATE_TEST_CASE_P(
        _,
        sha1_test,
        ::testing::Values(
                Erase_params<int>{vector<int>{0,1,2,3,4,5,6,7},0, 4,vector<int> {4,5,6,7}
                })
);

//типизированные тесты
template <class T>
struct push_test: public :: testing::Test
{
        typedef T TypeParam;
};

typedef string type1;
typedef ofstream type2;
typedef ::testing::Types<type1,type2, float> MY_Types;
TYPED_TEST_CASE(push_test, MY_Types);

template<typename T>
T Data() {
        return 1.051;
}

template<>
type1 Data<type1>() {
        return "test";
}

template<>
type2 Data<type2>() {
        ofstream ostrm;
        return ostrm;
}

TYPED_TEST(push_test, vector) {
        vector<TypeParam> x;
        TypeParam y = Data<TypeParam>();
        x.push_back(move(y));
        EXPECT_EQ(1u, x.size());
}
