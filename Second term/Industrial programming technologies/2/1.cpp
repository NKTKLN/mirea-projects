#include <cmath>
#include <iostream>

using namespace std;

class Figure {
public:
	virtual double square() = 0;
};

class Triangle: public Figure {
private:
	double a, b, c;
public:
	Triangle(double a, double b, double c);
	double square();
};

class Rectangle: public Figure {
private:
	double a, b;
public:
	Rectangle(double a, double b);
	double square();
};

class Trapezoid: public Figure {
private:
	double a, b, h;
public:
	Trapezoid(double a, double b, double h);
	double square();
};

Triangle::Triangle(double a, double b, double c) {
	this->a = a;
	this->b = b;
	this->c = c;
}

double Triangle::square() {
	double p = (this->a + this->b + this->c)/ 2;
	return sqrt(p * (p - this->a) * (p - this->b) * (p - this->c));
}

Rectangle::Rectangle(double a, double b) {
	this->a = a;
	this->b = b;
}

double Rectangle::square() { return this->a * this->b; }

Trapezoid::Trapezoid(double a, double b, double h) {
	this->a = a;
	this->b = b;
	this->h = h;
}

double Trapezoid::square() { return (this->a + this->b) / 2 * this->h; }
