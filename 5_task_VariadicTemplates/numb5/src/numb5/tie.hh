
#include <iostream>
using namespace std;
template<temolate First, tipename...Last>
  struct Tie{
    int N;
  int M = sizeof...(Last)+1;
  First* new_aray[sizeof...(Last)+1];
  Tie(First& first, Last&...last){
  N = first.size();
  new_array[0] = &first;
  First* array_last[sizeof..(Last)] = {&last ...};
  for(int i =0; i<sizeof...(Last); i++)
      new_array[i+1] = array_last[i];
  }
 template<class T, long unsignet int K>
  
