#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

class Fraction {
public:
    int a, b;

    Fraction();
    Fraction(int a, int b);
    void print();
};

Fraction::Fraction() {
    this->a = 0;
    this->b = 1;
}

Fraction::Fraction(int a, int b) {
    this->a = a;
    this->b = b;

    if (this->a == 0 && this->b == 0) return;
    if (this->a >= this->b) this->a %= this->b;
    if (this->a == 0) this->b = 1;

    int divisor = gcd(this->a, this->b);
    this->a /= divisor;
    this->b /= divisor;
}

void Fraction::print() { cout << this->a << "/" << this->b << endl; }

class SetOfFractions {
private:
    vector<Fraction> data;
public:
    bool isEmpty();
    void append(Fraction fraction);
    void exclude(Fraction fraction);
    Fraction sum();
};

bool SetOfFractions::isEmpty() { return this->data.size() == 0; }

void SetOfFractions::append(Fraction fraction) {
    for (int index = 0; index < this->data.size(); index++)
        if (this->data[index].a == fraction.a && this->data[index].b == fraction.b) return;

    this->data.push_back(fraction);
}

void SetOfFractions::exclude(Fraction fraction) {
    for (int index = 0; index < this->data.size(); index++) {
        if (this->data[index].a == fraction.a && this->data[index].b == fraction.b) {
            this->data.erase(this->data.begin() + index);
            break;
        }
    }
}

Fraction SetOfFractions::sum() {
    if (isEmpty()) return Fraction(0, 0);

    int numerator = 0;
    int denominator = 1;
    for (int index = 0; index < this->data.size(); index++) {
        numerator = numerator * this->data[index].b + this->data[index].a * denominator;
        denominator *= this->data[index].b;
    }

    return Fraction(numerator, denominator);
}
