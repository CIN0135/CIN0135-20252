#include <iostream>
#include <cstddef>
#include <cassert>
#include <string>
#include <random> // For random number generation

class Vector {
private:
    int *arr;
    size_t sz;
    size_t cap;

    void checkAndDouble();

public:
    Vector();
    ~Vector();
    size_t size() {
        return sz;
    }
    int operator[](size_t pos) {
        return arr[pos];
    }
    void append(int val);
    void insert(size_t pos, int val);

    void print(const char* name) {
        for (size_t i = 0; i < sz; ++i) 
            std::cout << name << "[" << i << "]=" << arr[i] << "\n";
    }
};


Vector::Vector() {
    cap = 1;
    sz = 0;
    arr = new int[cap];
}

Vector::~Vector() {
    delete[] arr;
}

void Vector::checkAndDouble() {
    if (sz < cap) return;
    size_t newCap = 2 * cap;
    int *newArr = new int[newCap];
    for (size_t i = 0 ; i < sz; ++i) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    cap = newCap;
}

void Vector::append(int val) {
    checkAndDouble();
    assert(sz < cap);
    arr[sz++] = val;
}

void Vector::insert(size_t pos, int val) {
    checkAndDouble();
    for (long i = sz; i > pos; i--) {
        arr[i] = arr[i-1];
    }
    arr[pos] = val;
    sz++;
}

int _main(int argc, char **argv) {
    size_t n = std::stoi(argv[1]);
    Vector v;
    for (size_t i = 0; i < n; ++i) {
        v.append(i);
    }
    //v.print("v");
    return 0;   
}

int main(int argc, char **argv) {
    int n = std::stoi(argv[1]);

    // Create a random device to seed the engine
    std::random_device rd; 

    // Create a Mersenne Twister engine seeded with the random device
    std::mt19937 gen(rd()); 

    // Define a uniform integer distribution for numbers between 1 and 100
    std::uniform_int_distribution<> distrib(0, n); 

    // Generate and print a random number


    Vector v;
    for (size_t i = 0; i < n; ++i) {
        int j = v.size()?rand()%v.size():0;
        v.insert(i, j);
    }
}