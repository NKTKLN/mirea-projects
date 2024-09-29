#include <ctime>
#include <iostream>

using namespace std;

struct Node {
    int key;
    int count;
    Node *left;
    Node *right;
    int height;
    Node(int value) : key(value), left(nullptr), right(nullptr), height(0), count(1) {}
};

int getHeight(Node *node) {
    return (node == nullptr) ? -1 : node->height;
}

void updateHeight(Node *&node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

int getBalance(Node *node) {
    return (node == nullptr) ? 0 : getHeight(node->right) - getHeight(node->left);
}

void insert(Node *&node, int key) {
    if (node->key > key) {
        if (node->left == nullptr) node->left = new Node(key);
        else insert(node->left, key);
    }
    else if (node->key < key) {
        if (node->right == nullptr) node->right = new Node(key);
        else insert(node->right, key);
    }
    else node->count++;

    updateHeight(node);
}

void printTree(Node *node) {
    if (node == nullptr) return;
    printTree(node->left);
    cout << node->key << " (" << node->count << ") " << "[" << getBalance(node) << "] | ";
    printTree(node->right);
}

Node *generateRandomTree(int countOfNodes) {
    Node *root = new Node(rand() % 100);
    for (; countOfNodes > 0; countOfNodes--)
        insert(root, rand() % 100);
    return root;
}

int main() {
    srand(time(0));

    cout << "[] - balance | () - count" << endl << endl;

    Node *root = generateRandomTree(10);
    printTree(root);
    cout << endl;

    return 0;
}
