#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace std;

class Complex {
    double re, im;
public:
    Complex() : re(0), im(0) {}
    Complex(double real) : re(real), im(0) {}
    Complex(double real, double imag) : re(real), im(imag) {}

    Complex operator+(const Complex& z) const {
        return {re + z.re, im + z.im};
    }

    Complex operator-(const Complex& z) const {
        return {re - z.re, im - z.im};
    }

    Complex operator*(const Complex& z) const {
        return {re * z.re - im * z.im, re * z.im + im * z.re};
    }

    Complex operator/(const Complex& z) const {
        double d = z.re * z.re + z.im * z.im;
        if (d == 0.0) throw domain_error("division by zero impedance");
        return {(re * z.re + im * z.im) / d,
                (im * z.re - re * z.im) / d};
    }

    bool operator==(const Complex& z) const {
        const double eps = 1e-9;
        return abs(re - z.re) < eps && abs(im - z.im) < eps;
    }

    double magnitude() const { return sqrt(re * re + im * im); }

    friend ostream& operator<<(ostream& os, const Complex& z) {
        return os << z.re << (z.im < 0 ? " - j" : " + j") << abs(z.im);
    }
};

int main() {
    const double R = 10.0, XL = 5.0, XC = 10.0;
    Complex resistor(R, 0), inductor(0, XL), capacitor(0, -XC);

    Complex series = resistor + inductor + capacitor;
    Complex parallel = (resistor * inductor) / (resistor + inductor);

    cout << "Series impedance: " << series << '\n';
    cout << "Series magnitude: " << series.magnitude() << '\n';
    cout << "Parallel R-L: " << parallel << '\n';

    try {
        Complex invalid = resistor / Complex(0, 0);
        cout << invalid << '\n';
    } catch (const domain_error& e) {
        cout << "Error: " << e.what() << '\n';
    }
}