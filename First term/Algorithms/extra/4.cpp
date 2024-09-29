#include <ctime>
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
    Node(int value) : data(value), next(nullptr) {}
};

Node *createList(int size) {
    if (size <= 0)
    {
        return nullptr;
    }
    Node *element = new Node(1);
    Node *head = element;
    for (int index = 0; index < size - 1; index++)
    {
        Node *new_node = new Node(index);
        element->next = new_node;
        element = new_node;
    }
    return head;
}

void printList(Node *head) {
    Node *ptr = head;
    while (ptr)
    {
        cout << ptr->data << " -> ";
        ptr = ptr->next;
    }
    cout << "nullptr" << endl;
}

int sumOfListElements(Node *head) {
    int sum = 0;
    while (head != nullptr)
    {
        sum += head->data;
        head = head->next;
    }
    return sum;
}

int main() {
    srand(time(0));

    Node *head = createList(10);

    printList(head);
    cout << sumOfListElements(head) << endl;
    return 0;
}
