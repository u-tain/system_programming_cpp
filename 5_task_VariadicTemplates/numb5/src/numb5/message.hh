#include <iostream>
#include <string.h>

using namespace std;
inline void message() {}
inline void message(ostream& streamOut) {}
void  message(ostream& streamOut, const char* s) {
    streamOut << s;
}
template<typename T>
void message(ostream& streamOut, const char *s, T value)
{
    streamOut<< value;
}
template<typename T, typename... Args>
void message(ostream& streamOut, const char *s, T value, Args... args)
{
    while (*s) {
        if (*s == '\0')
            return;
        if (*s =='%'){
            if (value == '\n'){
                streamOut<<*s++;}
            s++;
            streamOut<< value;
            message(streamOut, s,args...,'\n');
            return;
        }
        streamOut<<*s++;
    };
}
