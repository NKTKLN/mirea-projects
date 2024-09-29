#include <iostream>

using namespace std;

class Heap {
private:
    int *data;
    int length;
    int lastIndex;

    void swap(int firstIndex, int secondIndex);
    void heapify(int index);
public:
    Heap(int maxHeapLength);
    Heap(int* array, int arrayLength, int maxHeapLength);
    ~Heap();
    void print();
};

Heap::Heap(int maxHeapLength) {
    this->data = new int[maxHeapLength];
    this->length = maxHeapLength;
    this->lastIndex = 0;
}

Heap::Heap(int* array, int arrayLength, int maxHeapLength) {
    this->data = new int[maxHeapLength];
    this->length = maxHeapLength;
    this->lastIndex = arrayLength - 1;
    copy(array, array+arrayLength, this->data);
    
    for (int index = this->lastIndex / 2; index >= 0; index--)
        heapify(index);
}

Heap::~Heap() { delete[] this->data; }

void Heap::swap(int firstIndex, int secondIndex) {
    int tempElement = this->data[firstIndex];
    this->data[firstIndex] = this->data[secondIndex];
    this->data[secondIndex] = tempElement;
}

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

void Heap::print() {
    for (int index = 0; index <= this->lastIndex; index++)
        cout << this->data[index] << " ";
    cout << endl;
}

int main() {
    int length;
    cout << "Enter array length: ";
    cin >> length;
    
    int* arr = new int[length];
    cout << "Enter elements: ";
    for (int index = 0; index < length; index++)
        cin >> arr[index];

    Heap* heap = new Heap(arr, length, 100);
    heap->print();

    delete heap;

    return 0;
}
