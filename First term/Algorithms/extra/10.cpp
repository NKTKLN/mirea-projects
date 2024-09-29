#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

void printNumbersInOrder(const string &filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Unable to open the file: " << filename << endl;
        return;
    }

    queue<int> singleDigitQueue;
    queue<int> doubleDigitQueue;

    int number;
    while (inputFile >> number) {
        if (number >= 10) {
            doubleDigitQueue.push(number);
        }
        else {
            singleDigitQueue.push(number);
        }
    }

    while (!singleDigitQueue.empty()) {
        cout << singleDigitQueue.front() << " ";
        singleDigitQueue.pop();
    }

    while (!doubleDigitQueue.empty()) {
        cout << doubleDigitQueue.front() << " ";
        doubleDigitQueue.pop();
    }

    inputFile.close();
}

int main() {
    string filename = "input.txt";
    printNumbersInOrder(filename);

    return 0;
}
