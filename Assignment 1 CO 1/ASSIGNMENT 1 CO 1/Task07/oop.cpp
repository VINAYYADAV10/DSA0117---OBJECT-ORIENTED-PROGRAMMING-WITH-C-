// Task 7(b): object-oriented version - SmartCard protects its balance
#include <iostream>

enum class Zone { Inner, Middle, Outer };

class SmartCard {
    long long balance_;
    static constexpr long long MIN_BALANCE = 5000;   // the only place the rule lives
public:
    explicit SmartCard(long long b) : balance_(b < 0 ? 0 : b) {}
    bool canTravel(long long f) const { return f >= 0 && balance_ - f >= MIN_BALANCE; }
    bool deduct(long long f) { if (!canTravel(f)) return false; balance_ -= f; return true; }
    long long balance() const { return balance_; }
};

long long fare(Zone z, bool peak) {
    long long b = 0;
    switch (z) { case Zone::Inner: b = 1000; break; case Zone::Middle: b = 2000; break; case Zone::Outer: b = 3000; break; }
    return peak ? b + b * 20 / 100 : b;
}

int main() {
    SmartCard card(10000);
    for (int i = 1; i <= 3; ++i) {
        bool ok = card.deduct(fare(Zone::Outer, true));
        std::cout << "journey " << i << (ok ? " allowed" : " DENIED") << ", balance = " << card.balance() << '\n';
    }
    // card.balance_ = -5;   // compile-time ERROR: balance_ is private
}
