#include <string>
#include <iostream>

using namespace std;

struct heapnode {
    int key;
    string data;
};

class Heap {
private:
    struct heapnode *data;
    int length;
    int lastIndex;

    void heapify(int index);
    void insertFix(int index);
    void swap(int firstIndex, int secondIndex);
public:
    Heap(int maxHeapLength);
    ~Heap();
    void print();
    struct heapnode *deleteMax();
    void insert(int priority, string name);
    struct heapnode *search(int priority, string name);
    void edit(struct heapnode *node, int newPriority, string newName);
};

Heap::Heap(int maxHeapLength) {
    this->data = new struct heapnode[maxHeapLength];
    this->length = maxHeapLength;
    this->lastIndex = -1;
}

Heap::~Heap() { delete[] this->data; }

void Heap::heapify(int index) {
    int largestIndex = index;
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;

    if (leftIndex <= this->lastIndex && this->data[leftIndex].key > this->data[largestIndex].key)
        largestIndex = leftIndex;
    if (rightIndex <= this->lastIndex && this->data[rightIndex].key > this->data[largestIndex].key)
        largestIndex = rightIndex;
    if (largestIndex == index) 
        return;

    swap(index, largestIndex);
    heapify(largestIndex);
}

void Heap::insertFix(int index) {
    int parentIndex = (index - 1) / 2;
    if (index <= parentIndex || this->data[parentIndex].key >= this->data[index].key)
        return;
    
    swap(index, parentIndex);
    insertFix(parentIndex);
}

void Heap::swap(int firstIndex, int secondIndex) {
    struct heapnode tempElement = this->data[firstIndex];
    this->data[firstIndex] = this->data[secondIndex];
    this->data[secondIndex] = tempElement;
}

struct heapnode *Heap::search(int priority, string name) {
    for (int index = 0; index <= this->lastIndex; index++)
        if (this->data[index].data == name && this->data[index].key == priority)
            return &this->data[index];
    return nullptr;
}

struct heapnode *Heap::deleteMax() {
    if (this->lastIndex == -1) return nullptr;
    
    this->lastIndex--;
    swap(0, this->lastIndex+1);
    heapify(0);
    return &this->data[this->lastIndex+1];
}

void Heap::insert(int priority, string name) {
    this->lastIndex++;
    this->data[this->lastIndex].key = priority;
    this->data[this->lastIndex].data = name;
    insertFix(this->lastIndex);
}

void Heap::edit(struct heapnode *node, int newPriority, string newName) {
    node->data = newName;
    node->key = newPriority;
    heapify(0);
}

void Heap::print() {
    for (int index = 0; index <= this->lastIndex; index++)
        cout << "[" << this->data[index].key << "] " << this->data[index].data << endl;
}

int main() {
    Heap* heap = new Heap(100);
    struct heapnode* trash = new heapnode[100];
    struct heapnode *node;
    int lastTrashIndex = -1;
    string command;
    string name;
    int priority;

    while (true) {
        cout << "> ";
        cin >> command;

        if (command == "add") {
            cout << "Enter task name: ";
            getline(cin >> ws, name);
            cout << "Enter task priority: ";
            cin >> priority;
            heap->insert(priority, name);
        }
        else if (command == "execute") {
            node = heap->deleteMax();
            if (node == nullptr) {
                cout << "No tasks." << endl;
                continue;
            }
            trash[++lastTrashIndex] = *node;
            cout << trash[lastTrashIndex].data << endl;
        }
        else if (command == "list") {
            cout << "Tasks:" << endl;
            heap->print();
            for (int index = 0; index <= lastTrashIndex; index++)
                cout << "[" << trash[index].key << "] " << trash[index].data << " (completed)" << endl;
        }
        else if (command == "edit") {
            cout << "Enter task name: ";
            getline(cin >> ws, name);
            cout << "Enter task priority: ";
            cin >> priority;

            node = heap->search(priority, name);
            if (node == nullptr) {
                cout << "Task not found." << endl;
                continue;
            }

            cout << "Enter new task name: ";
            getline(cin >> ws, name);
            cout << "Enter new task priority: ";
            cin >> priority;
            heap->edit(node, priority, name);
        }
        else if (command == "exit") break;
    }

    delete heap;
    delete[] trash;
    delete node;
    
    return 0;
}
