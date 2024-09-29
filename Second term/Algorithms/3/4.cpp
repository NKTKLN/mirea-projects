#include <iostream>

using namespace std;

struct Node {
    int key;
    Node *left;
    Node *right;
    Node(int value) : key(value), left(nullptr), right(nullptr) {}
};

bool leftOrRight(Node *&node, int* depth = 0) {
    if (node == nullptr) return -1;

    int leftDepth = 0;
    int rightDepth = 0;
    leftOrRight(node->left, &leftDepth);
    leftOrRight(node->right, &rightDepth);

    *depth += 1 + min(leftDepth, rightDepth);
    return leftDepth > rightDepth;
}

void insert(Node *&node, int key) {
    if (node->left == nullptr) {
        node->left = new Node(key);
        return;
    }
    else if (node->right == nullptr) {
        node->right = new Node(key);
        return;
    }

    int temp = 0;
    insert((leftOrRight(node, &temp)) ? node->right : node->left, key);
}

int getKey(Node *&node) { return (node == nullptr) ? -1 : node->key; }

void printTree(Node *node) {
    if (node == nullptr) return;
    printTree(node->left);
    cout << node->key << " [" << getKey(node->left) << ", " << getKey(node->right) << "]" << endl;
    printTree(node->right);
}

bool isMinBinaryHeap(Node *&node) {
    if (node == nullptr) return true;

    if (node->left != nullptr && node->left->key < node->key) return false;
    if (node->right != nullptr && node->right->key < node->key) return false;

    return isMinBinaryHeap(node->left) && isMinBinaryHeap(node->right);
}

bool isMaxBinaryHeap(Node *&node) {
    if (node == nullptr) return true;
    
    if (node->left != nullptr && node->left->key > node->key) return false;
    if (node->right != nullptr && node->right->key > node->key) return false;

    return isMaxBinaryHeap(node->left) && isMaxBinaryHeap(node->right);
}

void checkForBinaryHeap(Node*& root) {
    if (isMaxBinaryHeap(root)) cout << "Max binary heap" << endl;
    else if (isMinBinaryHeap(root)) cout << "Min binary heap" << endl; 
    else cout << "Not a binary heap" << endl;
}

int main() {
    int value;
    int length;
    cout << "Enter array length: ";
    cin >> length;
    int* arr = new int[length];
    cout << "Enter elements: ";
    cin >> value;
    Node *root = new Node(value);
    for (int index = 1; index < length; index++) {
        cin >> value;
        insert(root, value);
    }

    printTree(root);
    checkForBinaryHeap(root);

    return 0;
}
