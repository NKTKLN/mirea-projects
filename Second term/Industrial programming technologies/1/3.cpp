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
    bool is_similar(Triangle & t2);
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

bool Triangle::is_similar(Triangle & t2) {
    double max_t1 = max(max(this->a, this->b), this->c);
    double max_t2 = max(max(t2.a, t2.b), t2.c);
    double min_t1 = min(min(this->a, this->b), this->c);
    double min_t2 = min(min(t2.a, t2.b), t2.c);
    double mid_t1 = Triangle::perimetr() - max_t1 - min_t1;
    double mid_t2 = t2.perimetr() - max_t2 - min_t2;
    return max_t1 / max_t2 == min_t1 / min_t2 && max_t1 / max_t2 == mid_t1 / mid_t2;
}
