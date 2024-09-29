#include <ctime>
#include <iostream>
using namespace std;

int main() {
    srand(time(0));
    int arraySize = rand() % 50;
    int *numbers = new int[arraySize];

    cout << "[ ";
    for (int index = 0; index < arraySize; ++index) {
        numbers[index] = rand() % 10;
        cout << numbers[index] << " ";
    }
    cout << "] (" << arraySize << ")" << endl;

    bool isDescending = true;
    int previousNumber = numbers[0];

    for (int index = 0; index < arraySize; ++index) {
        if (numbers[index] >= previousNumber) {
            isDescending = false;
            break;
        }
        previousNumber = numbers[index];
    }

    cout << isDescending << endl;

    delete[] numbers;
    return 0;
}

