#include <iostream>
using namespase std;

template <class First, class... Other>
void make_vector(First first, Other... other)
{
    
  
  cout << first;
  print(other...);
}

template <class T, class ... Args>
T make_vector(Args&& ... args) {
return T(std::forward<Args>(args)...);
}

template<typename T, typename... Args>
void message(ostream& streamOut, const char *s, T value, Args... args)
{
    make<vector<char>>(3, 'a'); // {'a', 'a', 'a'}
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
