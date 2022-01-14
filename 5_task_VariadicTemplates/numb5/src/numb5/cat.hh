#include <iostream>
#include <array>
using namespace std;

/*template<typename T, long unsigned N, typename...Array>
auto cat( array<T,N>& first, Array&...arrays)->array<T,N*(sizeof...(arrays)+1)>
{
  T* C[sizeof ... (arrays)+1] = {first.data(), (arrays.data())...};
  array<T,N*(sizeof ...(arrays)+1)> concatenation;
  for (int i=0; i<sizeof...(arrays)+1;i++)
    for( int j = 0; j<N;j++)
      concatenation[i*N+j] = C[i][j];
  return concatenation;
}*/

template<typename T, long unsigned N>
auto cat(array < T, N>& value){
    return value;
}
template<typename T, long unsigned N, long unsigned M, typename... Args>
auto cat(array < T, N>& first, array < T, M>& second, Args&... args){
    array<T, N + M> x;
    for (size_t i = 0; i < N + M; i++) {
        if (i < N) {
            x[i] = first[i];
        }
        else {
            x[i] = second[i - N];
        }
     }
    return cat(x, args...);
}
