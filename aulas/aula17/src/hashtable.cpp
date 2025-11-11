#include "list.hpp"
#include <iostream>


class HashTable {

private:
    int sz; //n
    int cap; //m
    double max_load = 0.7;
    LinkedList *table;

    int hash(int key) {
        return key % cap;
    }

    void check_and_double() {
        double lf = (double)sz / (double)cap;
        if (lf > max_load) {
            // dobra e move os elementos
        }
    }

public:

    HashTable(int m=7): sz{0}, cap{m} {
        table = new LinkedList[cap];
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(int key) 
    {
        check_and_double();
        int i = hash(key);
        if (query(key)) return;
        table[i].insert(0, key);
    }

    bool query(int key) 
    {
        int i = hash(key);
        return table[i].find(key) < table[i].size();
    }

};

using namespace std;

int main() 
{
    int universe = 1 << 11;    
    int n = 100;
    HashTable ht;
    LinkedList allks;

    for (int i = 0 ; i < n; i++) {
        int k = rand() % universe;
        allks.append(k);
        ht.insert(k);
    }

    for (int i = 0; i < allks.size(); i++) {
        int k = allks[i];
        bool contains = ht.query(k);
        cout << "ht " <<  (contains?"contains ":"NOT contains ") << k << endl;
        k = rand() % universe;
        contains = ht.query(k);
        cout << "ht " <<  (contains?"contains ":"NOT contains ") << k << endl;
    }

}



