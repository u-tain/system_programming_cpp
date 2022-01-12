#include <iostream>
#include <string.h>

using namespace std;

/*template <class First>
void make_vector(vector<char>& x, First first) {
return x.push_back(to_string(first));;
}
template <class First, class ... Other>
void make_vector(vector<char>& x, First first, Other... other)
{
    x.push_back(first);
    make_vector(x, other...);
}
*/

inline void message() {}
inline void message(ostream& streamOut) {} 
template<typename T>
void message(ostream& streamOut, const char *s, T value)
{
    streamOut<< value;
}
template<typename T, typename... Args>
void message(ostream& streamOut, const char *s, T value, Args... args)
{
    while (*s!="%") {
        if (*s == '\0')
            return;
            streamOut<<*s;
    };
        s++;
        streamOut<< value;
        message(streamOut, s,args...);
}
int main()
{
      message(cout, "% + % = %\n", 'a', 2, 3.0);
      return 0;
}           
