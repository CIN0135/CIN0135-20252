#include <iostream>
#include <cstddef>
#include <cassert>
#include <string>
#include <random> // For random number generation

using namespace std;

template <typename T>
class Vector {
private:
    T *arr;
    size_t sz;
    size_t cap;

    void checkAndDouble();

public:
    Vector();
    ~Vector();
    size_t size() {
        return sz;
    }
    T& operator[](size_t pos) {
        return arr[pos];
    }
    template <typename U>
    friend ostream& operator<<(ostream& os, const Vector<U>& v);
    void append(const T& val);
    void insert(size_t pos, const T& val);

    void print(const char* name) const {
        for (size_t i = 0; i < sz; ++i) 
            std::cout << name << "[" << i << "]=" << arr[i] << "\n";
    }
};

template <typename T>
ostream& operator<<(ostream& os, const Vector<T>& v) {
    v.print("v");
    return os;
}

template <typename T>
Vector<T>::Vector() {
    cap = 1;
    sz = 0;
    arr = new T[cap];
}

template <typename T>
Vector<T>::~Vector() {
    delete[] arr;
}

template <typename T>
void Vector<T>::checkAndDouble() {
    if (sz < cap) return;
    size_t newCap = 2 * cap;
    T *newArr = new T[newCap];
    for (size_t i = 0 ; i < sz; ++i) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    cap = newCap;
}

template <typename T>
void Vector<T>::append(const T& val) {
    checkAndDouble();
    assert(sz < cap);
    arr[sz++] = val;
}

template <typename T>
void Vector<T>::insert(size_t pos, const T& val) {
    checkAndDouble();
    for (long i = sz; i > pos; i--) {
        arr[i] = arr[i-1];
    }
    arr[pos] = val;
    sz++;
}



template <typename T>
void printMe(const T& me) {
    cout << me << endl;
}

int main(int argc, char **argv) {
    int n = 5;
   /// std::stoi(argv[1]);

    Vector<string> v;
    for (size_t i = 0; i < n; ++i) {
        v.append("valor" + std::to_string(i));
    }

    cout << v[3] << endl;
    v[3] = 5;
    cout << v[3] << endl;
    
    int x = 10;
    printMe(x);
    double pi = 3.1415;
    printMe(pi);
    string s = "bbb";
    printMe(s);


    printMe(v);
}