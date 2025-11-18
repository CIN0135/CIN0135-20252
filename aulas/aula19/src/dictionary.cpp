#include <iostream>
#include <cassert>

using K = std::string;
using V = int;

ulong HashCode(K key) {
    ulong h = 0;
    ulong b = 128;
    ulong pow = 1;
    for (int i = 0; i < key.length(); i++) {
        h += (ulong)key[i] * pow;
        pow *= b;
    }
    return h;
}

class Dictionary {
    enum STATUS {
        FREE = 0,
        BUSY = 1,
        DEAD = 2
    };

    struct Entry {
        ulong k;
        K key;
        V val;
    };

    int sz;
    int nocc;
    int cap;
    
    STATUS *st;    
    Entry *arr;

    ulong hash(ulong k) {
        return k % cap;
    }

    void rehash() {
        Dictionary newTable(2*cap + 1);
        for (int i = 0 ; i < cap; i++) {
            if (st[i] == BUSY) {
                newTable.insert(arr[i].key, arr[i].val);
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
        V val;
    };

    Dictionary(int c = 11): sz{0}, nocc{0}, cap{c}
    {
        st = new STATUS[cap];
        for (int i = 0; i < cap; st[i++] = FREE);
        arr = new Entry[cap];
    }

    ~Dictionary() {
        delete[] st;
        delete[] arr;
    }

    int size() {
        return sz;
    }

    void insert(K key, V val) {
        if ((double)nocc/(double)cap > 0.5) {
            rehash();
        }
        ulong k = HashCode(key);
        ulong pos = hash(k);
        while (st[pos] != FREE) {
            if (st[pos] == BUSY && arr[pos].k == k && arr[pos].key == key) {
                std::cerr << "Duplicate insertion\n";
                return;
            }
            pos = (pos + 1) % cap;
        }
        assert(st[pos] == FREE);
        arr[pos] = Entry{k, key, val};
        st[pos] = BUSY;
        sz++;
        nocc++;
    }
   
    void remove(K key) {
        ulong k = HashCode(key);
        ulong pos = hash(k);
        int att = 1;
        while (st[pos] != FREE) {
            if (st[pos] == BUSY && arr[pos].k == k && arr[pos].key == key) {
                st[pos] = DEAD;
                sz--;
                return;
            }
            pos = (pos + 1) % cap;
            att++;
        }
        assert(st[pos] == FREE);
    }
    

    Result get(K key) {
        ulong k = HashCode(key);
        ulong pos = hash(k);
        int att = 1;
        while (st[pos] != FREE) {
            if (st[pos] == BUSY && arr[pos].k == k && arr[pos].key == key) {
                return {true, arr[pos].val};
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
    int *allkeys = new int[n];
    Dictionary ht;

    ht.insert("ana", 17);
    ht.insert("bob", 23);
    ht.insert("charles", 40);
    ht.insert("diana", 35);
    ht.insert("ed", 12);
    ht.insert("fred", 89);
    ht.insert("gustav", 64); 

    ht.insert("charles", 25);

    std::cout << "The age of charles is " << ht.get("charles").val << std::endl;

    delete[] allkeys;
}