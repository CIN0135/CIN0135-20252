#include <iostream>
#include <cassert>

class HashTable {
    enum STATUS {
        FREE = 0,
        BUSY = 1,
        DEAD = 2
    };

    int sz;
    int nocc;
    int cap;
    
    STATUS *st;    
    int *arr;

    int hash(int key) {
        return key % cap;
    }

    void rehash() {
        HashTable newTable(2*cap + 1);
        for (int i = 0 ; i < cap; i++) {
            if (st[i] == BUSY) {
                newTable.insert(arr[i]);
            }
        }
        delete[] st;
        delete[] arr;
        arr = newTable.arr;
        st = newTable.st;
        assert (sz == newTable.sz);
        cap = newTable.cap;

        newTable.arr = nullptr;
        newTable.st = nullptr;
    }

public:
    struct Result {
        bool contains;
        int attempts;
    };

    HashTable(int c = 11): sz{0}, nocc{0}, cap{c}
    {
        st = new STATUS[cap];
        for (int i = 0; i < cap; st[i++] = FREE);
        arr = new int[cap];
    }

    ~HashTable() {
        delete[] st;
        delete[] arr;
    }

    int size() {
        return sz;
    }

    void insert(int key) {
        if ((double)nocc/(double)cap > 0.5) {
            rehash();
        }
        int pos = hash(key);
        while (st[pos] != FREE) {
            pos = (pos + 1) % cap;
        }
        assert(st[pos] == FREE);
        arr[pos] = key;
        st[pos] = BUSY;
        sz++;
        nocc++;
    }
   
    void remove(int key) {
        int pos = hash(key);
        int att = 1;
        while (st[pos] != FREE) {
            if (st[pos] == BUSY && arr[pos] == key) {
                st[pos] = DEAD;
                sz--;
                return;
            }
            pos = (pos + 1) % cap;
            att++;
        }
        assert(st[pos] == FREE);
    }
    

    Result get(int key) {
        int pos = hash(key);
        int att = 1;
        while (st[pos] != FREE) {
            if (st[pos] == BUSY && arr[pos] == key) {
                return {true, att};
            }
            pos = (pos + 1) % cap;
            att++;
        }
        assert(st[pos] == FREE);
        return {false, att};
    }
};




int main() {
    int n = 100;
    int univ = 100000;
    int *allkeys = new int[n];
    HashTable ht;

    for (int i = 0; i < n; i++) {
        int key = rand() % univ;
        ht.insert(key);
        allkeys[i] = key;
    }

    for (int i = 0; i < n; i+=4) {
        ht.remove(allkeys[i]);
    }

    int nsucc = 0, succ = 0;
    int nfail = 0, fail = 0;

    for (int i = 0; i < n; i++) {
        int key = allkeys[i];
        auto res = ht.get(key);

        std::cout << "HT " 
            << (res.contains?"contains ":"DOES NOT contain ") 
            << key 
            << "(attempts = " << res.attempts << ")" 
            << std::endl;

        if (res.contains) {
            nsucc++;
            succ += res.attempts;
        } else {
            nfail++;
            fail += res.attempts;
        }
        
        key = rand() % univ;
        res = ht.get(key);

        std::cout << "HT " 
            << (res.contains?"contains ":"DOES NOT contain ") 
            << key 
            << "(attempts = " << res.attempts << ")" 
            << std::endl;

        if (res.contains) {
            nsucc++;
            succ += res.attempts;
        } else {
            nfail++;
            fail += res.attempts;
        }
    }

    std::cout << "# success = " << nsucc << std::endl;
    std::cout << "avg att succ = " << (double)succ/nsucc << std::endl;
    std::cout << "# fails = " << nfail << std::endl;
    std::cout << "avg att fail = " << (double)fail/nfail << std::endl;


    delete[] allkeys;
}