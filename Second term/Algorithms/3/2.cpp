#include <iostream>

using namespace std;

class Heap {
private:
    int *data;
    int length;
    int lastIndex;

    void heapify(int index);
    void insertFix(int index);
    void swap(int firstIndex, int secondIndex);
public:
    Heap(int maxHeapLength);
    Heap(int* array, int arrayLength, int maxHeapLength);
    ~Heap();
    void print();
    int getMax();
    void deleteMax();
    void insert(int element);
    void merge(Heap *heap);
};

Heap::Heap(int maxHeapLength) {
    this->data = new int[maxHeapLength];
    this->length = maxHeapLength;
    this->lastIndex = -1;
}

Heap::Heap(int* array, int arrayLength, int maxHeapLength) {
    this->data = new int[maxHeapLength];
    this->length = maxHeapLength;
    this->lastIndex = arrayLength - 1;
    copy(array, array+arrayLength, this->data);
    
    for (int index = arrayLength / 2 - 1; index >= 0; index--)
        heapify(index);
}

Heap::~Heap() { delete[] this->data; }

void Heap::heapify(int index) {
    int largestIndex = index;
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;

    if (leftIndex <= this->lastIndex && this->data[leftIndex] > this->data[largestIndex])
        largestIndex = leftIndex;
    if (rightIndex <= this->lastIndex && this->data[rightIndex] > this->data[largestIndex])
        largestIndex = rightIndex;
    if (largestIndex == index) 
        return;

    swap(index, largestIndex);
    heapify(largestIndex);
}

void Heap::insertFix(int index) {
    int parentIndex = (index - 1) / 2;
    if (index <= parentIndex || this->data[parentIndex] >= this->data[index])
        return;
    
    swap(index, parentIndex);
    insertFix(parentIndex);
}

void Heap::swap(int firstIndex, int secondIndex) {
    int tempElement = this->data[firstIndex];
    this->data[firstIndex] = this->data[secondIndex];
    this->data[secondIndex] = tempElement;
}

void Heap::print() {
    for (int index = 0; index <= this->lastIndex; index++)
        cout << this->data[index] << " ";
    cout << endl;
}

int Heap::getMax() { 
    if (this->lastIndex == -1)
        return -1;
    return this->data[0];
}

void Heap::deleteMax() {
    if (this->lastIndex == -1)
        return;
    
    this->lastIndex--;
    this->data[0] = this->data[this->lastIndex+1];
    heapify(0);
}

void Heap::insert(int element) {
    this->lastIndex++;
    this->data[this->lastIndex] = element;
    insertFix(this->lastIndex);
}

void Heap::merge(Heap *heap) {
    copy(heap->data, heap->data+heap->lastIndex+1, this->data + this->lastIndex + 1);
    this->lastIndex += heap->lastIndex + 1;

    for (int index = (this->lastIndex + 1) / 2 - 1; index >= 0; index--)
        heapify(index);
}

int main() {
    int length = 10;
    int arr[] = {1, 3, 2, 4, 8, 7, 10, 14, 9, 16};
    int length2 = 9;
    int arr2[] = {6, 5, 11, 16, 17, 18, 20, 24, 29};

    Heap* heap = new Heap(arr, length, 100);
    Heap* heap2 = new Heap(arr2, length2, 100);

    heap->print();
    cout << "Max element: " << heap->getMax() << endl;
    cout << "Remove the max element." << endl;
    heap->deleteMax();
    heap->print();
    cout << "Insert element (19)." << endl;
    heap->insert(19);
    heap->print();
    cout << "Print heap №2." << endl;
    heap2->print();
    cout << "Merge heap and heap2." << endl;
    heap->merge(heap2);
    heap->print();

    delete heap;
    delete heap2;
    
    return 0;
}
