#include <ctime>
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

void rightRotate(Node *&root, Node *&node) {
    Node *leftChild = node->left;
    node->left = leftChild->right;
    
    if(node->left != nullptr) node->left->parent = node;

    leftChild->parent = node->parent;

    if(node->parent == nullptr) root = leftChild;
    else if(node == node->parent->left) node->parent->left = leftChild;
    else node->parent->right = leftChild;

    leftChild->right = node;
    node->parent = leftChild;
}

void leftRotate(Node *&root, Node *&node) {
    Node *rightChild = node->right;
    node->right = rightChild->left;
    
    if(node->right != nullptr) node->right->parent = node;

    rightChild->parent = node->parent;

    if(node->parent == nullptr) root = rightChild;
    else if(node == node->parent->left) node->parent->left = rightChild;
    else node->parent->right = rightChild;

    rightChild->left = node;
    node->parent = rightChild;
}

void fixRulesAfterInsertion(Node *&root, Node*& node) {
    Node* parent = nullptr;
    Node* grandParent = nullptr;
    while (node != root && getColor(node) == RED && getColor(node->parent) == RED) {
        parent = node->parent;
        grandParent = parent->parent;
        if(parent == grandParent->left) {
            Node* uncle = grandParent->right;
            if(getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandParent, RED);
                node = grandParent;
            }
            else {
                if(node == parent->right) {
                    leftRotate(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                rightRotate(root, grandParent);
                const bool color = grandParent->color;
                grandParent->color = parent->color;
                parent->color = color;
                node = parent;
            }
        }
        else {
            Node* uncle = grandParent->left;
            if(getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandParent, RED);
                node = grandParent;
            }
            else {
                if(node == parent->left) {
                        rightRotate(root, parent);
                        node = parent;
                        parent = node->parent;
                }
                leftRotate(root, grandParent);
                const bool color = grandParent->color;
                grandParent->color = parent->color;
                parent->color = color;
                node = parent;
            }
        }
    }
    setColor(root, BLACK);
}

void insertNode(Node *&root, Node *&node) {
    if (root == nullptr) {
        root = node;
        return;
    }

    if (node->key < root->key) {
        insertNode(root->left, node);
        root->left->parent = root;
    }
    else if (node->key >= root->key) {
        insertNode(root->right, node);
        root->right->parent = root;
    }
}

void insertNodeValue(Node *&root, const int key) {
    Node *node = new Node(key);
    insertNode(root, node);
    fixRulesAfterInsertion(root, node);
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

int getChildrenCount(Node *&node) {
    int count = 0;
    if (node->left != nullptr) count++;
    if (node->right != nullptr) count++;
    return count;
}

Node *getChildOrMock(Node*& node) {
    return node->left != nullptr ? node->left : node->right;
}

void transplantNode(Node *&root, Node *&toNode, Node *&fromNode) {
    if (toNode == root) root = toNode;
    else if (toNode == toNode->parent->left) toNode->parent->left = fromNode;
    else toNode->parent->right = fromNode;
    fromNode->parent = toNode->parent;
}

void fixRulesAfterRemoval(Node *&root, Node *&node) {
    if (node == nullptr) return;

    if (node == root) {
        root = nullptr;
        return;
    }

    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node *child = node->left != nullptr ? node->left : node->right;
        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr) child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        } else {
            node->parent->right = child;
            if (child != nullptr) child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
    } else {
        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        setColor(ptr, BLACK);
        while (ptr != root && getColor(ptr) == BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    leftRotate(root, parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if(getColor(parent) == RED) setColor(parent, BLACK);
                        else setColor(parent, BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rightRotate(root, sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        leftRotate(root, parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rightRotate(root, parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED) setColor(parent, BLACK);
                        else setColor(parent, BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            leftRotate(root, sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rightRotate(root, parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left) node->parent->left = nullptr;
        else node->parent->right = nullptr;
        delete(node);
        setColor(root, BLACK);
    }
}

Node *deleteNode(Node *&node, int key) {
    if (node == nullptr) return nullptr;
    if (node->key > key) return deleteNode(node->left, key);
    if (node->key < key) return deleteNode(node->right, key);
    if (node->left == nullptr || node->right == nullptr) return node;
    
    Node *minRight = getMin(node->right);
    node->key = minRight->key;
    return deleteNode(node->right, minRight->key);
}

void deleteNodeValue(Node *&root, const int key) {
    Node* node = deleteNode(root, key);
    fixRulesAfterRemoval(root, node);
}

void printTree(Node *node) {
    if (node == nullptr) return;
    printTree(node->left);
    cout << node->key << " (" << ((node->color == RED) ? "RED" : "BLACK") << ")"<< endl;
    printTree(node->right);
}

Node *generateRandomTree(int countOfNodes) {
    Node *root = nullptr;
    for (; countOfNodes > 0; countOfNodes--) insertNodeValue(root, rand() % 100);  
    return root;
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
    cout << "Checking for rules: ";
    if (blackHeight(root) != 0) 
        cout << "Correct" << endl;
    else 
        cout << "Incorrect" << endl;
}

int main() {
    srand(time(0));
    
    Node *root = generateRandomTree(10);
    printTree(root);
    checkRedBlackTreeProperties(root);
    cout << "rm " << root->key << endl;
    deleteNodeValue(root, root->key);
    printTree(root);
    checkRedBlackTreeProperties(root);

    return 0;
}
