#include <map>
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

Node* createList(int size) {
    if (size <= 0) {
        return nullptr;
    }

    Node* element = new Node(1);
    Node* head = element;

    for (int index = 0; index < size - 1; index++) {
        Node* new_node = new Node(index);
        element->next = new_node;
        element = new_node;
    }

    return head;
}

void printList(Node* head) {
    Node* ptr = head;
    while (ptr) {
        cout << ptr->data << " -> ";
        ptr = ptr->next;
    }
    cout << "nullptr" << endl;
}

bool areListsEqual(Node* head1, Node* head2) {
    Node* ptr1 = head1;
    Node* ptr2 = head2;

    while (ptr1 && ptr2) {
        if (ptr1->data != ptr2->data) {
            return false;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    return ptr1 == ptr2;
}

bool doAllElementsExist(Node* head1, Node* head2) {
    map<int, bool> m;
    Node* ptr = head2;

    while (ptr) {
        m[ptr->data] = true;
        ptr = ptr->next;
    }

    ptr = head1;

    while (ptr) {
        if (!m[ptr->data]) {
            return false;
        }
        ptr = ptr->next;
    }

    return true;
}

bool hasDuplicateElements(Node* head) {
    map<int, bool> m;
    Node* ptr = head;

    while (ptr) {
        if (m[ptr->data]) {
            return true;
        }

        m[ptr->data] = true;
        ptr = ptr->next;
    }

    return false;
}

void moveToLast(Node*& head) {
    Node* newHead = head->next;
    Node* ptr = head;

    while (ptr->next != nullptr) {
        ptr = ptr->next;
    }

    head->next = nullptr;
    ptr->next = head;

    head = newHead;
}

void moveToFirst(Node*& head) {
    Node* ptr = head;

    while (ptr->next->next != nullptr) {
        ptr = ptr->next;
    }

    Node* newHead = ptr->next;
    ptr->next = nullptr;
    newHead->next = head;

    head = newHead;
}

void appendList(Node*& head1, Node* head2) {
    Node* ptr = head1;

    while (ptr->next != nullptr) {
        ptr = ptr->next;
    }

    ptr->next = head2;
}

void reverseList(Node*& head) {
    Node* newHead = nullptr;
    Node* ptr = head;

    while (ptr) {
        Node* nextPtr = ptr->next;
        ptr->next = newHead;
        newHead = ptr;
        ptr = nextPtr;
    }

    head = newHead;
}

void keepDistinctElements(Node*& head) {
    map<int, bool> m;
    Node* newHead = nullptr;
    Node* ptr = head;
    Node* prev = nullptr;

    while (ptr) {
        if (!m[ptr->data]) {
            m[ptr->data] = true;

            if (!newHead) {
                newHead = ptr;
            }

            if (prev) {
                prev->next = ptr;
            }

            prev = ptr;
        }

        ptr = ptr->next;
    }

    if (prev) {
        prev->next = nullptr;
    }

    head = newHead;
}

int main() {
    srand(time(0));

    Node* list1 = createList(10);
    Node* list2 = createList(10);
    appendList(list2, new Node(10));

    printList(list1);
    printList(list2);

    cout << areListsEqual(list1, list2) << endl;
    cout << doAllElementsExist(list1, list2) << endl;
    cout << hasDuplicateElements(list1) << endl;

    moveToLast(list1);
    printList(list1);

    moveToFirst(list1);
    printList(list1);

    appendList(list1, list2);
    printList(list1);

    reverseList(list1);
    printList(list1);

    keepDistinctElements(list1);
    printList(list1);

    return 0;
}
