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

    Fraction operator+(const Fraction &fraction) { 
        return Fraction(this->a * fraction.b + this->b * fraction.a, this->b * fraction.b);
    }
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

template <typename T> 
T superSum(T a, T b) { return a + b; } 
 
template <typename T, int N> 
T superSum(T (&a)[N]) { 
    T sum = 0;
    int count = sizeof(a) / sizeof(a[0]); 

    for (int index = 0; index < count; index++)
        sum = superSum(sum, a[index]); 

    return sum; 
} 
