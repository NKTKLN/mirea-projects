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

void swap(Node *&first, Node *&second) {
    int firstKey = first->key;
    first->key = second->key;
    second->key = firstKey;
}

void rightRotate(Node *&node) {
    swap(node, node->left);
    Node *buffer = node->right;
    node->right = node->left;
    node->left = node->right->left;
    node->right->left = node->right->right;
    node->right->right = buffer;
    updateHeight(node->right);
    updateHeight(node);
}

void leftRotate(Node *&node) {
    swap(node, node->right);
    Node *buffer = node->left;
    node->left = node->right;
    node->right = node->left->right;
    node->left->right = node->left->left;
    node->left->left = buffer;
    updateHeight(node->left);
    updateHeight(node);
}

void balanceTree(Node *&node) {
    int balance = getBalance(node);
    if (balance == -2) {
        if (getBalance(node->left) == 1) leftRotate(node->left);
        rightRotate(node);
    }
    else if (balance == 2) {
        if (getBalance(node->right) == -1) rightRotate(node->right);
        leftRotate(node);
    }
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
    balanceTree(node);
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
    cout << "root height: " << root->height << endl;
    cout << "root key: " << root->key << endl;

    return 0;
}
