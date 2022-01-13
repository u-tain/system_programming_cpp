#include <iostream>
#include <utility>
#include <algorithm>
#include <cstddef>

namespace Vektor {
	template <class T>
	class Vector {
		private:
            T* mass = nullptr;
            unsigned long len;
		
		public:
			Vector() {
				len = 0;
				mass = nullptr;
			}
			
			~Vector() { delete [] mass; }
			
			Vector(unsigned long size) {
				len = size;
				mass = new T[size];
			}
			
			Vector(std::initializer_list<T> sp) {
				len = sp.size();
				if (len > 0) {
					mass = new T[sp.size()];
					std::copy(sp.begin(), sp.end(), mass);
				} else { mass = nullptr; }
			}
			
			Vector(Vector&& vec){
				len = vec.size();
				mass = vec.mass;
				vec.mass = nullptr;
			}
			
			const T& operator[] (unsigned long j) const { return mass[j]; }
			
			T& operator[] (unsigned long j) { return mass[j]; }
			
			Vector(const Vector& vec) {
				len = vec.size();
				mass = new T[vec.size()];
				for (auto i = 0; i < vec.size(); i++) {
					mass[i] = vec[i];
				}
			}
			
			bool operator ==(const Vector &vec) const {
				if (len != vec.len) { return false; }
				for (auto i = 0; i < len; i++) {
					if (mass[i] != vec[i]) { return false; }
				}
				return true;
			}
			
			Vector& operator=(const Vector& vec) {
				vector curr(vec);
				this -> swap(curr);
				return *this; 
			}
			
			Vector& operator=(Vector&& vec) {
				this -> swap(vec);
				return *this;
			}
			
			T* begin() { return mass; }
			const T* begin() const { return mass; }
			
			T* end() { return (mass + len); }
			const T* end() const { return (mass + len); }
			
			unsigned long size() const { return len; }
			
			void push_back(const T& elem) {
				T* curr = new T[len + 1];
				for (auto i = 0; i < len; i++) {
					curr[i] = std::move(mass[i]);
				}
				curr[len] = std::move(elem);
				len = len + 1;
				delete [] mass; 
				mass = curr;
			}
        
			void push_back(T&& elem) {
				T* curr = new T[len + 1];
				for (auto i = 0; i < len; i++) {
					curr[i] = std::move(mass[i]);
				}
				curr[len] = std::move(elem);
				len = len + 1;
				delete [] mass;
				mass = curr;
			}
			
			
			void pop_back() { erase(this -> end() - 1); }
			
			void erase(const T* p_1, const T* p_2) {
				raz = p_2 - p_1
				T* curr = new T[len-raz];
				for(auto i = this -> begin(); i != p_1 ; i++) {
					curr[i - begin()] = std::move(mass[i - begin()]);
				}
				for(auto i = p_2; i != end() ; i++) {
					curr[i - begin()-(p_2 - p_1)] = std::move(mass[i - begin()]);
				}
				len = len - (p_2 - p_1); 
				delete [] mass;
				mass = curr;
			}
		
			void erase(const T* p) {
				erase(p, p + 1);
			}	
			
			void swap(Vector & vec) {
				std::swap(len, vec.len);
				std::swap(mass, vec.mass);
			}
	};

    template <class T>
    void swap(vector<T> lev, vector<T> prav) { lev.swap(prav); }
};
