
#include <iostream>
#include <utility>
#include <algorithm>
#include <cstddef>



template <class T>
class Vector {
private:
        T* arr = nullptr;
        int len;

public:
        Vector() {
                arr = nullptr;
                len = 0;
        }

        Vector(int size) {
                arr = new T[size];
                len = size;
        }

        ~Vector() {
                delete[] arr;
        }

        Vector(std::initializer_list<T> data) {
                len = data.size();
                if (len > 0) {
                        arr = new T[data.size()];
                        std:: copy(data.begin(), data.end(), arr);
                }
                else
                        arr = nullptr;
        }

        T& operator[] (unsigned long j) { return arr[j]; }
        const T& operator[] (unsigned long j) const { return arr[j]; }

        void push_back(T&& data)
        {
                T* result = new T[++len];
                for (int i = 0; i < len; i++)
                {
                        if (i != len - 1)
                                result[i] = std::move(arr[i]);
                        else
                        {
                                result[i] = std::move(data);
                                break;
                        }
                }
                delete[] arr;
                arr = result;
        }

        void push_back(const T& data) {
                T* result = new T[++len];
                for (int i = 0; i < len; i++)
                {
                        if (i != len - 1)
                                result[i] = std::move(arr[i]);
                        else
                        {
                                result[i] = std::move(data);
                                break;
                        }
                }
                delete[] arr;
                arr = result;
        }

        void pop_back() { erase(this->end() - 1); }

        void erase(const T* index1, const T* index2) {
                T* result = new T[len - (index2 - index1)];
                for (auto i = this->begin(); i != index1; i++) {
                        result[i - begin()] = std::move(arr[i - begin()]);
                }
                for (auto i = index2; i != end(); i++) {
                        result[i - begin() - (index2 - index1)] = std:: move(arr[i - begin()]);
                }
                len = len - (index2 - index1);
                delete[] arr;
                arr = result;
        }

        void erase(const T* index) {
                erase(index, index + 1);
        }

        T* begin() { return &arr[0]; }
        const T* begin() const { return &arr[0]; }

        T* end() { return &arr[len]; }
        const T* end() const {return &arr[len];}

        int size() const { return len; }

        void swap(Vector&& vec) {
                std::swap(len, vec.len);
                std::swap(arr, vec.arr);
        }

        Vector(Vector&& vec) {
                len = vec.size();
                arr = vec.arr;
                vec.arr = nullptr;
        }
        Vector(const Vector& vec) {
                len = vec.size();
                arr = new T[vec.size()];
                for (auto i = 0; i < vec.size(); i++) {
                        arr[i] = vec[i];
                }
        }

        bool operator ==(const Vector& vec) const {
                if (len != vec.len) { return false; }
                for (auto i = 0; i < len; i++) {
                        if (arr[i] != vec[i]) { return false; }
                }
                return true;
        }

        Vector& operator=(const Vector& vec) {
                Vector result(vec);
                this->swap(std::move(result));
                return *this;
        }

        Vector& operator=(Vector&& vec) {
                this->swap(std::move(vec));
                return *this;
        }
};

template <class T>
void swap(Vector<T> l, Vector<T> r) { l.swap(r); }
