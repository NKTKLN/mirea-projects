#include <iostream>

using namespace std;

int main() {
    int* arr;
    int temp;
    int size = 10;
    int shift = 23;

    arr = new int[size];
    for (int index = 0; index < size; ++ index) {
        arr[index] = index;
        cout << arr[index] << " ";
    }
    cout << endl;
    
    shift %= size;
    for (int count = 0; count < shift; ++count) {
        temp = arr[9];
        for (int index = size-1; index > 0; --index)
            arr[index] = arr[index-1];
        arr[0] = temp;
    }

    for (int index = 0; index < size; ++index)
        cout << arr[index] << " ";
    cout << endl;

    return 0;
}
