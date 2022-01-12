#include <iostream>
using namespase std;

template <class First>
void make_vector(vector<char>& x, First first) {
return x.push_back(first);;
}
template <class First, class ... Other>
void make_vector(vector<char>& x, First first, Other... other)
{
    x.push_back(first);
    make_vector(x, other...);
}

template<typename T, typename... Args>
void message(ostream& streamOut, const char *s, T value, Args... args)
{
    vector<char> list;
    make_vector(list, args...);
    if list.size()<
        
    
    i=0;
    while (*s) {
        if (*s == '%') {
            i+=1;
            if (*(s + 1) == '%') {
                ++s;
            }
            else {
                streamOut << value;
                s += 2; // работает только для спецификаторов формата из двух символов (напр. %d, %f ).Не будет работать с %5.4f
                message(s, args...); // вызов происходит даже когда *s == 0, чтобы обнаружить избыточные аргументы
                return;
            }
        }
        cout << *s++;
    }    
}
