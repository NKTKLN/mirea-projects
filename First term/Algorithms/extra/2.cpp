#include <ctime>
#include <iostream>
using namespace std;

int main() {
    // srand(time(0));
    int arraySize = rand() % 50;
    int *numbers = new int[arraySize];

    cout << "[ ";
    for (int index = 0; index < arraySize; ++index) {
        numbers[index] = rand() % 100;
        cout << numbers[index] << " ";
    }
    cout << "] (" << arraySize << ")" << endl;

    int divisibleByFiveCount = 0;
    int divisibleByFiveSum = 0;

    for (int index = 0; index < arraySize; ++index) {
        if (numbers[index] % 5 == 0 && numbers[index] % 7 != 0) {
            divisibleByFiveSum += numbers[index];
            ++divisibleByFiveCount;
        }
    }

    cout << divisibleByFiveCount << " " << divisibleByFiveSum << endl;

    delete[] numbers;
    return 0;
}
