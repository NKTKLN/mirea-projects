#include <iostream>

using namespace std;

class Heap {
private:
    int *data;
    int length;
    int lastIndex;

    void heapify(int index);
    void swap(int firstIndex, int secondIndex);
public:
    Heap(int* array, int arrayLength);
    int* getArray();
    void heapSort();
};

Heap::Heap(int* array, int arrayLength) {
    this->data = array;
    this->length = arrayLength - 1;
    this->lastIndex = arrayLength - 1;
    
    for (int index = arrayLength / 2 - 1; index >= 0; index--)
        heapify(index);
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

void Heap::swap(int firstIndex, int secondIndex) {
    int tempElement = this->data[firstIndex];
    this->data[firstIndex] = this->data[secondIndex];
    this->data[secondIndex] = tempElement;
}

int* Heap::getArray() { return this->data; }

void Heap::heapSort() {
    if (this->lastIndex == 0) return;
    swap(0, this->lastIndex--);
    heapify(0);
    heapSort();
}

void pyramidalSorting(int *array, int length) {
    Heap* heap = new Heap(array, length);
    heap->heapSort();
    array = heap->getArray();
}

void printArray(int *array, int length) {
    for (int index = 0; index < length; index++)
        cout << array[index] << " ";
    cout << endl;
}

int main() {
    int length;
    cout << "Enter array length: ";
    cin >> length;
    
    int* array = new int[length];
    cout << "Enter elements: ";
    for (int index = 0; index < length; index++)
        cin >> array[index];

    printArray(array, length);
    pyramidalSorting(array, length);
    printArray(array, length);

    delete[] array;
    
    return 0;
}
