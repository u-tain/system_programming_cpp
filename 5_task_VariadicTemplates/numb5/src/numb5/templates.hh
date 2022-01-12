#include <iostream>
using namespase std;

template<typename T, typename... Args>
void message(ostream& streamOut, const char *s, T value, Args... args)
{
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
