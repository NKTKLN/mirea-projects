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

Node *search(Node *&node, int key) {
    if (node == nullptr) return nullptr;
    if (node->key == key) return node;
    return search((node->key > key) ? node->left : node->right, key);
}

Node *getMin(Node *&node) {
    if (node == nullptr) return nullptr;
    if (node->left == nullptr) return node;
    return getMin(node->left);
}

Node *getMax(Node *&node) {
    if (node == nullptr) return nullptr;
    if (node->right == nullptr) return node;
    return getMax(node->right);
}

Node *deleteNode(Node *&node, int key) {
    if (node == nullptr) return nullptr;
    else if (node->key > key) node->left = deleteNode(node->left, key);
    else if (node->key < key) node->right = deleteNode(node->right, key);
    else if (node->key == key && node->count != 1) node->count--;
    else {
        if (node->left == nullptr || node->right == nullptr)
            node = (node->left == nullptr) ? node->right : node->left;
        else {
            Node *maxLeft = getMax(node->left);
            node->key = maxLeft->key;
            node->left = deleteNode(node->left, maxLeft->key);
        }
    }
    if (node != nullptr) updateHeight(node);
    return node;
}

void printTree(Node *node) {
    if (node == nullptr) return;
    printTree(node->left);
    cout << node->key << " (" << node->count << ") ";
    printTree(node->right);
}

Node *generateRandomTree(int countOfNodes) {
    Node *root = new Node(rand() % 100);
    for (; countOfNodes > 0; countOfNodes--) insert(root, rand() % 100);
    return root;
}

int main() {
    srand(time(0));

    Node *root = generateRandomTree(10);
    cout << "root: " << root->key << endl;
    printTree(root);
    cout << endl;
    insert(root, 9);
    cout << "root: " << root->key << endl;
    printTree(root);
    cout << endl;
    cout << "height: " << root->height + 1 << endl;
    Node *buffer = search(root, 9);
    cout << buffer << endl;
    cout << "root: " << root->key << endl;
    root = deleteNode(root, 9);
    printTree(root);
    cout << endl;

    return 0;
}
