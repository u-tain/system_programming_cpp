#include <iostream>
#include <string>
#include<array>

using namespace std;
template<typename First, typename... Last>
  struct Tie{
    int N;
    int M = sizeof...(Last)+1;
    First* new_array[sizeof...(Last)+1];
    Tie(First& first, Last&...last){
        N = first.size();
        new_array[0] = &first;
        First* array_last[sizeof...(Last)] = {&last ...};
        for(int i =0; i<sizeof...(Last); i++)
            new_array[i+1] = array_last[i];
    }
    template<class T, int K>
    void operator=(const array<T,K>& rhs){
        if (K==M*N)
            for (int i = 0; i<M;i++)
                for (int j = 0; j<N; j++)
                    (*new_array[i])[j] = rhs[i*N+j];
    }
};
template<typename First, typename... Last>
auto tie(First& first, Last&... last)-> Tie<First, Last...>{
    return Tie<First, Last...>(first, last...);
}
