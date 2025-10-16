#include <iostream>
#include <cassert>



class LinkedList {

private:

    struct Node {
        int val;
        Node* next;
    };

    Node *head;
    size_t sz;

public:

    LinkedList();
    ~LinkedList();

    size_t size() { // inline
        return sz;
    }
    void print();
    int at(size_t pos);

    int operator[](size_t pos) {
        return at(pos);
    }

    size_t find(int value);
    void insert(size_t pos, int value);
    void remove(size_t pos);

};

LinkedList::LinkedList() 
{
    head = new Node;
    head->val = -1;
    head->next = nullptr;
    sz = 0;
}

LinkedList::~LinkedList() 
{
    Node *cur = head;
    Node *next;
    while (cur!=nullptr) {
        next = cur->next;
        delete cur;
        cur = next;
    }
}

void LinkedList::print() 
{
    Node *cur = head;
    size_t i = 0;
    //while ( (*cur).next != nullptr ) {
    while ( cur->next != nullptr ) {
        std::cout << "list[" << i++ << "] = " << cur->next->val << std::endl;
        cur = cur->next;
    }
}

// retorna uma copia do elemento da lista na posicao pos
// pre-condicao: pos < tamanho da lista
int LinkedList::at(size_t pos)
{
    assert(pos < size());
    Node *cur = head;
    size_t i = 0;
    while ( i < pos && cur->next != nullptr ) {
        cur = cur->next;
        i++;
    }
    return cur->next->val;
}

// retorna a posicao da primeira ocorrencia de value na lista, se houver
// ou o tamanho da lista se não houver.
size_t LinkedList::find(int value) 
{
    Node *cur = head;
    size_t i = 0;
    while ( cur->next != nullptr && cur->next->val != value ) {
        cur = cur->next;
        i++;
    }
    return i;
}


// insere um novo nó de valor value na posiçao pos
// pos = 0 --> insere no inicio da lista
// pos >= tam. da lista --> insere no final
void LinkedList::insert(size_t pos, int value)
{
    // passo 1
    Node *cur = head;
    size_t i = 0;
    while ( i < pos && cur->next != nullptr ) {
        cur = cur->next;
        i++;
    }
    // passo 2
    Node *newNode = new Node;
    newNode->val = value;
    // passo 3
    newNode->next = cur->next;
    cur->next = newNode;
    sz++;
}

// remove nó da posição pos
void LinkedList::remove(size_t pos) 
{
    // passo 1
    Node *cur = head;
    size_t i = 0;
    while ( i < pos && cur->next != nullptr ) {
        cur = cur->next;
        i++;
    }
    Node *toDie = cur->next;
    assert(toDie);
    cur->next = toDie->next;
    delete toDie;
    sz--;
}


void doSomething() 
{
    LinkedList list; // cria lista vazia


    size_t size = 0; // insere 0, 10, 20, 30, 30
    for (int v = 0; v < 50; v += 10) {
        list.insert(size, v);
        size++;
    }

    list.insert(3, 25); // insere 25 entre 20 e 30
    
    std::cout << list[2] << std::endl;

    list.remove(4); // remove 30

    list.print();
}


LinkedList *doSomethingElse() 
{
    LinkedList *list = new LinkedList(); // cria lista vazia


    size_t size = 0; // insere 0, 10, 20, 30, 30
    for (int v = 0; v < 50; v += 10) {
        list->insert(size, v);
        size++;
    }

    list->insert(3, 25); // insere 25 entre 20 e 30

    list->remove(4); // remove 30

    return list;
}

int main() {
    doSomething();
    LinkedList *l  = doSomethingElse();
    //....


    l->print();

    std::cout << "bye" << std::endl;
    delete l;
}