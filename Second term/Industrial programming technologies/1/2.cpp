#include <cmath>
#include <iostream>

using namespace std;

class Triangle {
public:
    double a, b, c;
    Triangle(double an, double bn, double cn) : a(an), b(bn), c(cn) {
        if (!Triangle::exst_tr()) {
            this->a = 3;
            this->b = 4;
            this->c = 5;
        }
    }

    bool exst_tr();
    void show();
    double perimetr();
    double square();
};

bool Triangle::exst_tr() {
    return Triangle::perimetr() - max(max(this->a, this->b), this->c) * 2 > 0;
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
