#include <iostream>

struct Node {
    int val;
    Node *left;
    Node *right;

    Node(int v, Node *l=nullptr, Node *r=nullptr): val{v}, left{l}, right{r} {
    }
};

Node *buildExampleBT() {

    Node *n3 = new Node(3);
    Node *n7 = new Node(7);
    Node *n13 = new Node(13);
    Node *n5 = new Node(5, n3, n7);
    Node *n11 = new Node(11, nullptr, n13);
    Node *n9 = new Node(9, n5, n11);

    return n9;
}

void visit(Node *root) {
    std::cout << root->val << std::endl;
}

void preOrder(Node *root) 
{
    if (root == nullptr) {
        return;
    }
    visit(root);
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(Node *root) 
{
    if (root == nullptr) {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    visit(root);
}


void inOrder(Node *root) 
{
    if (root == nullptr) {
        return;
    }
    inOrder(root->left);
    visit(root);
    inOrder(root->right);
}

int main() {
    Node *root = buildExampleBT();

    std::cout << "PRE" << std::endl;
    preOrder(root);
    std::cout << "POS" << std::endl;
    postOrder(root);
    std::cout << "IN" << std::endl;
    inOrder(root);

    // do something with root
    /*
    9
        5
            3
            7
        11
            -
            13
    */
      
}