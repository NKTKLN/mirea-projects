#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    string name;
    vector<string> numbers;
    Node *left;
    Node *right;
    Node(string nameValue, string numberValue) {
        name = nameValue;
        numbers.push_back(numberValue);
        right = nullptr;
        left = nullptr;
    }
};

Node *insert(Node *&node, string name, string number) {
    if (node == nullptr) return new Node(name, number);
    if (node->name > name) {
        if (node->left == nullptr) node->left = new Node(name, number);
        else insert(node->left, name, number);
    }
    else if (node->name < name) {
        if (node->right == nullptr) node->right = new Node(name, number);
        else insert(node->right, name, number);
    }
    else node->numbers.push_back(number);

    return node;
}

Node *search(Node *&node, string name) {
    if (node == nullptr) return nullptr;
    if (node->name == name) return node;
    return search((node->name > name) ? node->left : node->right, name);
}

Node *getMax(Node *&node) {
    if (node == nullptr) return nullptr;
    if (node->right == nullptr) return node;
    return getMax(node->right);
}

Node *deleteNode(Node *&node, string name) {
    if (node == nullptr) return nullptr;
    else if (node->name > name) node->left = deleteNode(node->left, name);
    else if (node->name < name) node->right = deleteNode(node->right, name);
    else {
        if (node->left == nullptr || node->right == nullptr)
            node = (node->left == nullptr) ? node->right : node->left;
        else {
            Node *maxLeft = getMax(node->left);
            node->name = maxLeft->name;
            node->left = deleteNode(node->left, maxLeft->name);
        }
    }

    return node;
}

void printTree(Node *node) {
    if (node == nullptr) return;
    printTree(node->left);
    cout << node->name << ":" << endl;
    for (vector<string>::const_iterator number = node->numbers.begin(); number != node->numbers.end(); number++)
        cout << " * " << *number << endl;
    printTree(node->right);
}

int main() {
    srand(time(0));

    Node *root = nullptr;

    cout << "Phone book" << endl
         << "Use 'help' to output all available commands." << endl;
    while (true) {
        string inputCommand;
        cout << "> ";
        cin >> inputCommand;
        if (inputCommand == "help")
            cout << "Commands:" << endl
                 << " * help - output all available commands" << endl
                 << " * add - add a new record" << endl
                 << " * del-person - delete person" << endl
                 << " * del-number - delete phone number from a person" << endl
                 << " * search - output phone numbers for a particular person" << endl
                 << " * list - output all names and phone numbers for each person" << endl
                 << " * exit - exit the program" << endl;
        else if (inputCommand == "add") {
            string name, phoneNumber;
            cout << "Enter the person's name: ";
            cin >> name;
            cout << "Enter the person's phone number: ";
            cin >> phoneNumber;
            root = insert(root, name, phoneNumber);
            cout << "The phone number '" << phoneNumber << "' was successfully added to the person named '" << name << "'." << endl;
        }
        else if (inputCommand == "del-person") {
            string name;
            cout << "Enter the person's name: ";
            cin >> name;
            root = deleteNode(root, name);
            cout << "Person named '" << name << "' has been deleted." << endl;
        }
        else if (inputCommand == "del-number") {
            string name;
            cout << "Enter the person's name: ";
            cin >> name;
            Node *personNode = search(root, name);
            if (personNode == nullptr) {
                cout << "Person named '" << name << "' not found." << endl;
                continue;
            }
            string phoneNumber;
            cout << "Enter the person's phone number: ";
            cin >> phoneNumber;
            vector<string>::iterator position = find(personNode->numbers.begin(), personNode->numbers.end(), phoneNumber);
            if (position == personNode->numbers.end()) {
                cout << "The phone number '" << phoneNumber << "' of a person named '" << name << "' was not found." << endl;
                continue;
            }
            personNode->numbers.erase(position);
            cout << "The phone number '" << phoneNumber << "' of a person named '" << name << "' has been deleted." << endl;
        }
        else if (inputCommand == "search") {
            string name;
            cout << "Enter the person's name: ";
            cin >> name;
            Node *personNode = search(root, name);
            if (personNode == nullptr) {
                cout << "Person named '" << name << "' not found." << endl;
                continue;
            }
            cout << "The phone numbers of a person named '" << name << "':" << endl;
            for (vector<string>::const_iterator number = personNode->numbers.begin(); number != personNode->numbers.end(); number++)
                cout << " * " << *number << endl;
        }
        else if (inputCommand == "list") {
            cout << "List of all users and their phone numbers:" << endl;
            printTree(root);
        }
        else if (inputCommand == "exit") {
            cout << "Goodbye!" << endl;
            break;
        }
        else cout << "Unknown command." << endl;
    }

    return 0;
}
