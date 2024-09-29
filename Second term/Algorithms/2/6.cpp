#include <iostream>

using namespace std;

struct Node {
    int key;
    int count;
    Node *left;
    Node *right;
    Node(int value) : key(value), left(nullptr), right(nullptr), count(1) {}
};

Node *getMax(Node *&node) {
    if (node == nullptr) return nullptr;
    if (node->right == nullptr) return node;
    return getMax(node->right);
}

Node *rightRotate(Node *node) {
    Node *buffer = node->left;
    node->left = buffer->right;
    buffer->right = node;
    return buffer;
}

Node *leftRotate(Node *node) {
    Node *buffer = node->right;
    node->right = buffer->left;
    buffer->left = node;
    return buffer;
}

void insertNode(Node *node, int key) {
    if (node->key > key) {
        if (node->left == nullptr) node->left = new Node(key);
        else insertNode(node->left, key);
    }
    else if (node->key < key) {
        if (node->right == nullptr) node->right = new Node(key);
        else insertNode(node->right, key);
    }
    else node->count++;
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
    return node;
}

Node *splay(Node *root, int key) {
    if (root == nullptr || root->key == key) return root;

    if (root->key > key) {
        if (root->left == nullptr) return root;
        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key); 
            root = rightRotate(root);
        } 
        else if (root->left->key < key) {
            root->left->right = splay(root->left->right, key); 
            if (root->left->right != nullptr) root->left = leftRotate(root->left); 
        }

        return (root->left == nullptr) ? root : rightRotate(root); 
    }
    
    if (root->right == nullptr) return root;
    if (root->right->key > key) {
        root->right->left = splay(root->right->left, key); 
        if (root->right->left != nullptr) root->right = rightRotate(root->right);
    } 
    else if (root->right->key < key) {
        root->right->right = splay(root->right->right, key); 
        root = leftRotate(root);
    }

    return (root->right == nullptr) ? root : leftRotate(root); 
}

void searchNodeValue(Node *&root, const int key) {
    root = splay(root, key);
}

void insertNodeValue(Node *&root, const int key) {
    insertNode(root, key);
    root = splay(root, key);
}

void deleteNodeValue(Node *&root, const int key) {
    root = splay(deleteNode(root, key), key);
}

// ============================================= //

int getKey(Node *&node) {
    if (node == nullptr) return -1;
    return node->key;
}

void printTree(Node *&node) {
    if (node == nullptr) return;
    printTree(node->left);
    cout << node->key << " (" << node->count << ") [" << getKey(node->left) 
         << ", " << getKey(node->right) << "]" << endl;
    printTree(node->right);
}

Node *generateRandomTree(int countOfNodes) {
    Node *root = new Node(rand() % 100);
    for (; countOfNodes > 0; countOfNodes--) insertNodeValue(root, rand() % 100);
    return root;
}

// ============================================= //

int main() {
    srand(13);

    Node *root = generateRandomTree(10);
    printTree(root);
    cout << "root: " << root->key << endl;

    cout << endl << "Search (8)" << endl;
    searchNodeValue(root, 8);
    printTree(root);
    cout << "root: " << root->key << endl;

    cout << endl << "Insert (73)" << endl;
    insertNodeValue(root, 73);
    printTree(root);
    cout << "root: " << root->key << endl;

    cout << endl  << "Delete (38)"<< endl;
    deleteNodeValue(root, 38);
    printTree(root);
    cout << "root: " << root->key << endl;
    
    return 0;
}
