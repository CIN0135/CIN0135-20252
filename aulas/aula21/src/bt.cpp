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
    Node *n15 = new Node(15);
    Node *n13 = new Node(13, nullptr, n15);
    Node *n5 = new Node(5, n3, n7);
    Node *n11 = new Node(11, nullptr, n13);
    Node *n9 = new Node(9, n5, n11);

    return n9;
}

void visit(Node *root, int level=0) {
    for (int i=0; i < level; i++) std::cout << "  ";
    std::cout << root->val << std::endl;
}

void preOrder(Node *root, int level=0) 
{
    if (root == nullptr) {
        return;
    }
    visit(root, level);
    preOrder(root->left, level+1);
    preOrder(root->right, level+1);
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


void inOrder(Node *root, int level=0) 
{
    if (root == nullptr) {
        return;
    }
    inOrder(root->left, level+1);
    visit(root, level);
    inOrder(root->right, level+1);
}


int height(Node *root) {
    if (root == nullptr) return 0;
    int hl = height(root->left);
    int hr = height(root->right);
    return 1 + std::max(hl, hr);
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
    int h = height(root);
    std::cout << "height = " << h << std::endl;
}