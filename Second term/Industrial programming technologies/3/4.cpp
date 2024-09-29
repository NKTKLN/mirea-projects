#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

template <typename T>
class SuperFraction {
public:
    int a, b;

    SuperFraction();
    SuperFraction(T a, T b);
    void print();
};

template <typename T>
SuperFraction<T>::SuperFraction() {
    this->a = 0;
    this->b = 1;
}

template <typename T>
SuperFraction<T>::SuperFraction(T a, T b) {
    this->a = a;
    this->b = b;

    if (this->a == 0 && this->b == 0) return;
    if (this->a >= this->b) this->a %= this->b;
    if (this->a == 0) this->b = 1;

    int divisor = gcd(this->a, this->b);
    this->a /= divisor;
    this->b /= divisor;
}

template <typename T>
void SuperFraction<T>::print() { cout << this->a << "/" << this->b << endl; }

template <typename T>
class SuperExtraMegaWowOfFractions {
private:
    vector<SuperFraction<T>> data;
public:
    bool isEmpty();
    void append(SuperFraction<T> fraction);
    void exclude(SuperFraction<T> fraction);
    SuperFraction<T> sum();
};

template <typename T>
bool SuperExtraMegaWowOfFractions<T>::isEmpty() { return this->data.size() == 0; }

template <typename T>
void SuperExtraMegaWowOfFractions<T>::append(SuperFraction<T> fraction) {
    for (int index = 0; index < this->data.size(); index++)
        if (this->data[index].a == fraction.a && this->data[index].b == fraction.b) return;

    this->data.push_back(fraction);
}

template <typename T>
void SuperExtraMegaWowOfFractions<T>::exclude(SuperFraction<T> fraction) {
    for (int index = 0; index < this->data.size(); index++) {
        if (this->data[index].a == fraction.a && this->data[index].b == fraction.b) {
            this->data.erase(this->data.begin() + index);
            break;
        }
    }
}

template <typename T>
SuperFraction<T> SuperExtraMegaWowOfFractions<T>::sum() {
    if (isEmpty()) return SuperFraction(0, 0);

    int numerator = 0;
    int denominator = 1;
    for (int index = 0; index < this->data.size(); index++) {
        numerator = numerator * this->data[index].b + this->data[index].a * denominator;
        denominator *= this->data[index].b;
    }

    return SuperFraction(numerator, denominator);
}
