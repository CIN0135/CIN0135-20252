#include <iostream>
#include <cassert>


struct Node {
    int val;
    Node* next;
};


void listPrint(Node *head) 
{
    Node *cur = head;
    size_t i = 0;
    //while ( (*cur).next != nullptr ) {
    while ( cur->next != nullptr ) {
        std::cout << "list[" << i++ << "] = " << cur->next->val << std::endl;
        cur = cur->next;
    }
}

size_t listSize(Node *head)
{
    Node *cur = head;
    size_t size = 0;
    while ( cur->next != nullptr ) {
        cur = cur->next;
        size++;
    }
    return size;
}

// retorna uma copia do elemento da lista na posicao pos
// pre-condicao: pos < tamanho da lista
int listAt(Node *head, size_t pos)
{
    assert(pos < listSize(head));
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
size_t listFind(Node *head, int value) 
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
void listInsert(Node *head, size_t pos, int value)
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
}

// cria nova lista vazia
Node *listNew() 
{
    Node *head = new Node;
    head->next = nullptr;
    return head;
}

int main() 
{
    Node *head = listNew();
    size_t size = 0;
    for (int v = 0; v < 50; v += 10) {
        listInsert(head, size, v);
        size++;
    }

    listInsert(head, 3, 25);

    listPrint(head);
}