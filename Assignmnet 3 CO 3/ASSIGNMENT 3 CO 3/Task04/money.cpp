#include <iomanip>
#include <iostream>
using namespace std;

class Money {
    long long paise;
public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    Money operator+(const Money& other) const {
        Money result;
        result.paise = paise + other.paise;
        return result;
    }

    Money operator-(const Money& other) const {
        Money result;
        result.paise = paise - other.paise;
        return result;
    }

    Money& operator+=(const Money& other) {
        paise += other.paise;
        return *this;
    }

    bool operator==(const Money& other) const {
        return paise == other.paise;
    }

    bool operator<(const Money& other) const {
        return paise < other.paise;
    }

    friend ostream& operator<<(ostream& os, const Money& m) {
        long long whole = m.paise / 100;
        long long cents = m.paise % 100;
        if (cents < 0) cents = -cents;
        return os << "Rs " << whole << '.' << setw(2) << setfill('0')
                  << cents << setfill(' ');
    }
};

int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    cout << c << '\n';
    cout << boolalpha << (c == Money(200)) << '\n';

    Money x(0, 75), y(0, 50);
    cout << (x + y) << '\n';
    cout << (Money(1, 0) - Money(2, 0)) << '\n';
}