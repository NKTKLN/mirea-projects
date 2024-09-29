#include <iostream>

using namespace std;

class MyStack {
private:
    int lastIndex = -1;
    int numbers[100] = {};
public:
    void push(int n);
    void pop();
    void back();
    void size();
    void clear();
};

void MyStack::push(int n) {
    this->numbers[++this->lastIndex] = n;
}

void MyStack::pop() {
    if (lastIndex < 0) return; 
    MyStack::back();
    this->lastIndex--;
}

void MyStack::back() {
    cout << this->numbers[this->lastIndex] << endl;
}

void MyStack::size() {
    cout << this->lastIndex+1 << endl;
}

void MyStack::clear() {
    this->lastIndex = -1;
}
