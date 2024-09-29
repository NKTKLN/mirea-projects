#include <cmath>
#include <iostream>

using namespace std;

class Triangle {
public:
    double a, b, c;

    bool exst_tr();
    void set(double a1, double b1, double c1);
    void show();
    double perimetr();
    double square();
};

bool Triangle::exst_tr() {
    return Triangle::perimetr() - max(max(this->a, this->b), this->c) * 2 > 0;
}

void Triangle::set(double a1, double b1, double c1) {
    this->a = a1;
    this->b = b1;
    this->c = c1;
}

void Triangle::show() {
    cout << "A = " << this->a << ", B = " << this->b << ", C = " << this->c << endl;
}

double Triangle::perimetr() {
    return this->a + this->b + this->c;
}

double Triangle::square() {
    double p = Triangle::perimetr() / 2;
    return sqrt(p * (p - this->a) * (p - this->b) * (p - this->c));
}
