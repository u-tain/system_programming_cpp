#include <iostream>
using namespace std;

template<typename T, long unsigned N, typename...Array>
auto cat(array<T,N>& first, Array&...arrays)->array<T,N*sizeof...(aarays)+1>
{
