
#include <iostream>
#include <queue>

class NTree {

    struct Node {
        int val;
        Node *firstChd;
        Node *sibling;

        // return i-th child of this node
        // or nullptr if such node doesn't exist
        Node *chd(int i) {
            Node *ret = firstChd;
            for (int j = 0; ret && j < i; j++)
                ret = ret->sibling;
            return ret;
        }

        // add new child node with value v to this node
        void addChd(int v) {
            if (!firstChd) {
                firstChd = new Node{v, nullptr, nullptr};
                return;
            }
            Node *cur = firstChd;
            while (cur->sibling) {
                cur = cur->sibling;
            }            
            cur->sibling = new Node{v, nullptr, nullptr};
        }

        void print(int level=0) {
            for (int i = 0; i < level; i++)
                std::cout << "    " ;
            std::cout << this->val << std::endl;
            for (Node *cur = firstChd; cur; cur = cur->sibling) {
                cur->print(level + 1);
            }
        } 

    };


public:
    
    Node *root;

    NTree() {
        root = new Node{0, nullptr, nullptr};
        root->addChd(1);
        root->addChd(2);
        Node *n1 = root->chd(0);
        n1->addChd(3);
        n1->addChd(4);
        n1->addChd(5);
        Node *n2 = root->chd(1);
        n2->addChd(6);
        Node *n4 = n1->chd(1);
        n4->addChd(7);
        n4->addChd(8);

    }

    void print() {
        if (root) root->print();
    }

    void bfs() {
        std::queue<Node *> q;
        if (root) q.push(root);
        while (q.size()) {
            Node *n = q.front();
            q.pop();
            std::cout << n->val << std::endl;
            for (Node *cur = n->firstChd; cur; cur = cur->sibling) {
                q.push(cur);
            }
        }
    }

};


int main() {
    NTree t;
    t.print();
    std::cout << "------------ BFS ------------\n";
    t.bfs();

}