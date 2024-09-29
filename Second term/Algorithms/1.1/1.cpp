#include <iostream>

using namespace std;

struct Node {
    int minNum;
    int maxNum;
    Node *left;
    Node *right;
    Node(int minValue, int maxValue) : minNum(minValue), maxNum(maxValue), left(nullptr), right(nullptr) {}
};

Node *buildTree(int minValue, int maxValue) {
    if (minValue >= maxValue) return nullptr;
    Node *root = new Node(minValue, maxValue);
    if (maxValue - minValue > 1) {
        int middleValue = (minValue + maxValue) / 2;
        root->left = buildTree(minValue, middleValue);
        root->right = buildTree(middleValue, maxValue);
    }
    return root;
}

int searchX(Node *&node, int value) {
    if(node == nullptr) return 0;
    int count = 0;
    if(node->minNum <= value && node->maxNum >= value) count++;
    return count + searchX(node->left, value) + searchX(node->right, value);
}

void printTree(Node *node) {
    if (node == nullptr) return;
    printTree(node->left);
    cout << "(" << node->minNum << ", " << node->maxNum << ") ";
    printTree(node->right);
}

int searchSum(Node *&node, int minValue, int maxValue) {
    if (node == nullptr || minValue >= maxValue) return 0;
    if(node->left != nullptr || node->right != nullptr) return searchSum(node->left, minValue, maxValue) + searchSum(node->right, minValue, maxValue);
    int sum = 0;
    if (node->maxNum <= maxValue && node->maxNum > minValue) sum += node->maxNum;
    if (node->minNum == minValue) sum += node->minNum;
    return sum;
}

int main() {
    int a, b;
    cout << "> ";
    cin >> a;
    cout <<  "> ";
    cin >> b;
    Node *root = buildTree(a, b);
    printTree(root);
    cout << endl;
    cout << "> ";
    cin >> a;
    cout << "Number of elements containing the number : " << searchX(root, a) << endl;
    cout << "> ";
    cin >> a;
    cout << "> ";
    cin >> b;
    cout << "Counting the sum of elements on the segment : " << searchSum(root, a, b) << endl;

    return 0;
}
