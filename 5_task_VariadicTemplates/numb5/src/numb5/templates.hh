#include <iostream>
using namespase std;

template<typename T, typename... Args>
void message(const char *s, T value, Args... args)
{
    while (*s) {
        if (*s == '%') {
            if (*(s + 1) == '%') {
                ++s;
            }
            else {
                cout << value;
                s += 2; // работает только для спецификаторов формата из двух символов (напр. %d, %f ).Не будет работать с %5.4f
                message(s, args...); // вызов происходит даже когда *s == 0, чтобы обнаружить избыточные аргументы
                return;
            }
        }
        cout << *s++;
    }    
}
