#include <iostream>
#include <string>

using namespace std;

struct T {
    string _name;
    T(string name) {
        _name = name;
    }
    void hello() {
        cout << "Hello " << _name <<  endl;
    }
};

void func(T &r) {
    r._name = "Modified " + r._name;
}

void func2(const T &r) {
    cout << "func 2" << r._name << endl;
}

int main() {
    T ana("Ana");
    T bob("Bob");

    T* p = &ana;
    p->hello();

    p = &bob;
    p->hello();

    T& r = ana;
    r.hello();

    r = bob;
    r.hello();

    func(ana);
    r.hello();
    
    func2(bob);
    r.hello();
}