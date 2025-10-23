#include <iostream>
#include <cassert>



class LinkedList {

private:

    struct Node {
        int val;
        Node* next;
    };

    Node *head, *tail;
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

    void append(int value);
};


LinkedList::LinkedList() 
{
    head = new Node;
    head->val = -1;
    head->next = nullptr;
    tail = head;
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

    if (cur == tail) {
        tail = newNode;
    }

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
    if (toDie == tail) {
        tail = cur;
    }
    cur->next = toDie->next;
    delete toDie;
    sz--;
}

void LinkedList::append(int value) {
    tail->next = new Node{value, nullptr};
    tail = tail->next;
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

int main(int argc, char **argv) {
    size_t n = std::stoi(argv[1]);
    LinkedList l;
    for (size_t i = 0; i < n; ++i) {
        int j = (l.size())?rand()%l.size():0;
        l.insert(i, j);
    }
    size_t i = std::stoi(argv[2]);
    std::cout << l.at(i);
}