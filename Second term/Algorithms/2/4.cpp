#include <iostream>
#define RED true
#define BLACK false

using namespace std;

struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;
    bool color;
    Node(int value) : key(value), left(nullptr), right(nullptr), color(RED) {}
};

bool getColor(Node *node) {
    if (node == nullptr) return BLACK;
    return node->color;
}

void setColor(Node *node, bool color) {
    if (node == nullptr) return;
    node->color = color;
}

void insert(Node *&root, Node *&node, int key) {
    if (root == nullptr) {
        root = new Node(key);
        setColor(root, BLACK);
        return;
    }

    if (node->key > key) {
        if (node->left == nullptr) {
            node->left = new Node(key);
            setColor(node->left, !getColor(node));
        }
        else insert(root, node->left, key);
    }
    else if (node->key <= key) {
        if (node->right == nullptr) {
            node->right = new Node(key);
            setColor(node->right, !getColor(node));
        }
        else insert(root, node->right, key);
    }

    setColor(root, BLACK);
}

void printTree(Node *node) {
    if (node == nullptr) return;
    printTree(node->left);
    cout << node->key << " (" << ((node->color == RED) ? "RED" : "BLACK") << ") " << endl;
    printTree(node->right);
}

int blackHeight(Node* node) {
    if (node == nullptr) return 1;
    int leftHeight = blackHeight(node->left);
    int rightHeight = blackHeight(node->right);
    
    if (leftHeight != rightHeight) return 0;
    if (leftHeight == 0 || rightHeight == 0) return 0;
    if (getColor(node) == BLACK) leftHeight++;

    return leftHeight;
}

void checkRedBlackTreeProperties(Node* root) {
    if (blackHeight(root) != 0) 
        cout << "Correct" << endl;
    else 
        cout << "Incorrect" << endl;
}

int main() {
    Node *root = nullptr;
    insert(root, root, 13);
    insert(root, root, 8);
    insert(root, root, 17);
    insert(root, root, 15);
    insert(root, root, 25);
    insert(root, root, 22);
    insert(root, root, 27);
    insert(root, root, 1);
    insert(root, root, 11);
    insert(root, root, 6);

    printTree(root);
    cout << endl;
    cout << "Checking for rules: ";
    checkRedBlackTreeProperties(root);

    cout << "Add 7" << endl;

    insert(root, root, 7);
    cout << "Checking for rules: ";
    checkRedBlackTreeProperties(root);
    
    return 0;
}
