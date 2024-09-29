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
    int getLength();
    int deleteMin();
    void insert(int element);
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

    if (leftIndex <= this->lastIndex && this->data[leftIndex] < this->data[largestIndex])
        largestIndex = leftIndex;
    if (rightIndex <= this->lastIndex && this->data[rightIndex] < this->data[largestIndex])
        largestIndex = rightIndex;
    if (largestIndex == index) 
        return;

    swap(index, largestIndex);
    heapify(largestIndex);
}

void Heap::insertFix(int index) {
    int parentIndex = (index - 1) / 2;
    if (index <= parentIndex || this->data[parentIndex] <= this->data[index])
        return;
    
    swap(index, parentIndex);
    insertFix(parentIndex);
}

void Heap::swap(int firstIndex, int secondIndex) {
    int tempElement = this->data[firstIndex];
    this->data[firstIndex] = this->data[secondIndex];
    this->data[secondIndex] = tempElement;
}

int Heap::getLength() { return this->lastIndex + 1; }

int Heap::deleteMin() {
    if (this->lastIndex == -1)
        return -1;
    
    int minElement = this->data[0];
    this->lastIndex--;
    this->data[0] = this->data[this->lastIndex+1];
    heapify(0);
    return minElement;
}

void Heap::insert(int element) {
    this->lastIndex++;
    this->data[this->lastIndex] = element;
    insertFix(this->lastIndex);
}

int main() {
    cout << "Array: [5, 4, 2, 8]" << endl;

    int length = 4;
    int arr[] = {5, 4, 2, 8};
    Heap* heap = new Heap(arr, length, 10);

    int spending = 0;
    int sumOfMinElements, firstMin, secondMin;
    while (heap->getLength() > 1) {
        firstMin = heap->deleteMin();
        secondMin = heap->deleteMin();
        sumOfMinElements = firstMin + secondMin;
        cout << firstMin << " + " << secondMin << " = " << sumOfMinElements << endl;
        spending += sumOfMinElements;
        heap->insert(sumOfMinElements);
    }
    cout << spending << endl;

    delete heap;

    return 0;
}
