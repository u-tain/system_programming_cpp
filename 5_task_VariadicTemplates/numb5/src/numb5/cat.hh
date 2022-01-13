#include <iostream>
using namespace std;

template<typename T, long unsigned N, typename...Array>
auto cat(array<T,N>& first, Array&...arrays)->array<T,N*sizeof...(aarays)+1>
{
  T* C[sizeof ... (arrays)+1] = {first.data(), (arrays.data())...};
  array<T,N*(sizeof ...(arrays)+1)> concatenation;
  for (int i=0; i<sizeof...(arrays)+1;i++)
    for( int j = 0; j<N;j++)
      concatenation[i*N+j] = C[i][j];
  return concatenation;
