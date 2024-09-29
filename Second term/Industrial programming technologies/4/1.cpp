#include <cmath>
#include <iostream>

using namespace std;

class Triangle {
  public:
    class WrongTriangleSideException {};
    double a, b, c;
    Triangle(double an, double bn, double cn) : a(an), b(bn), c(cn) {
        if (!exst_tr()) throw WrongTriangleSideException();
    }

    bool exst_tr();
    void show();
    double perimetr();
    double square();
};

bool Triangle::exst_tr() { return perimetr() - max(max(a, b), c) * 2 > 0; }

void Triangle::show() { cout << "A = " << a << ", B = " << b << ", C = " << c << endl; }

double Triangle::perimetr() { return a + b + c; }

double Triangle::square() {
    double p = perimetr() / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}
