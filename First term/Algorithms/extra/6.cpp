#include <ctime>
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

Node* constructList(int size) {
    if (size <= 0) {
        return nullptr;
    }

    Node* element = new Node(rand() % 100 + 1);
    Node* head = element;

    for (int i = 0; i < size - 1; i++) {
        Node* new_node = new Node(rand() % 100 + 1);
        element->next = new_node;
        element = new_node;
    }

    return head;
}

bool isListEmpty(Node* head) {
    return (head == nullptr);
}

int countOfListElements(Node* head) {
    int count = 0;
    while (head != nullptr) {
        ++count;
        head = head->next;
    }
    return count;
}

void addElementToHead(Node*& head, int value) {
    Node* element = new Node(value);
    element->next = head;
    head = element;
}

void addElementToLast(Node*& head, int value) {
    Node* element = new Node(value);
    Node* ptr = head;

    while (ptr) {
        if (ptr->next == nullptr) {
            ptr->next = element;
            break;
        }
        ptr = ptr->next;
    }
}

void addElementToN(Node*& head, int value, int index) {
    Node* element = new Node(value);
    Node* ptr = head;

    while (ptr) {
        --index;

        if (index < 0) {
            element->next = head;
            break;
        }

        if (index == 0) {
            element->next = ptr->next;
            ptr->next = element;
            break;
        }

        ptr = ptr->next;
    }
}

void printList(Node* head) {
    Node* ptr = head;
    while (ptr) {
        cout << ptr->data << " -> ";
        ptr = ptr->next;
    }
    cout << "nullptr" << endl;
}

Node* copyListExceptFirst(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return nullptr;
    }

    Node* newHead = new Node(head->next->data);
    Node* current = newHead;
    Node* original = head->next->next;

    while (original) {
        current->next = new Node(original->data);
        current = current->next;
        original = original->next;
    }

    return newHead;
}

int main() {
    srand(time(0));
    Node* numbers = nullptr;

    cout << isListEmpty(numbers) << endl;

    numbers = constructList(10);
    printList(numbers);

    addElementToHead(numbers, 1);
    printList(numbers);

    addElementToLast(numbers, 10);
    printList(numbers);

    addElementToN(numbers, 5, 5);
    printList(numbers);

    Node* newList = copyListExceptFirst(numbers);
    printList(newList);

    cout << countOfListElements(numbers) << endl;

    return 0;
}
