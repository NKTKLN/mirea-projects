#include <ctime>
#include <iostream>
using namespace std;

int main() {
    srand(time(0));
    int arraySize = rand() % 50;
    int *numbers = new int[arraySize];

    cout << "[ ";
    for (int index = 0; index < arraySize; ++index) {
        numbers[index] = rand() % 3; // 100
        cout << numbers[index] << " ";
    }
    cout << "] (" << arraySize << ")" << endl;

    bool hasTwoConsecutiveZeros = false;
    bool hasThreeConsecutiveZeros = false;
    int consecutiveZerosCount = 0;

    for (int index = 0; index < arraySize; ++index) {
        if (numbers[index] != 0) {
            consecutiveZerosCount = 0;
            continue;
        }

        if (consecutiveZerosCount == 1) {
            hasTwoConsecutiveZeros = true;
        }

        if (consecutiveZerosCount == 2) {
            hasThreeConsecutiveZeros = true;
            break;
        }

        ++consecutiveZerosCount;
    }

    cout << hasTwoConsecutiveZeros << " " << hasThreeConsecutiveZeros << endl;

    delete[] numbers;
    return 0;
}
