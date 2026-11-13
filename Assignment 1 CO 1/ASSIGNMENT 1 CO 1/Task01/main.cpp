// Task 1: objects identified from the Namma Metro fare problem (skeleton + demo)
#include <iostream>

enum class Zone { Inner, Middle, Outer };

class FareTable {                       // knowledge: base fares (single place)
public:
    static constexpr int BASE_PAISE[] = {1000, 2000, 3000};
    static constexpr int PEAK_PERCENT = 20;
    long long fare(Zone farthest, bool peak) const {
        long long f = BASE_PAISE[static_cast<int>(farthest)];
        if (peak) f += f * PEAK_PERCENT / 100;
        return f;
    }
};

class SmartCard {                       // encapsulation: balance is private
    long long balance_;                 // paise
public:
    static constexpr long long MIN_BALANCE = 5000;
    explicit SmartCard(long long b) : balance_(b) {}
    bool canTravel(long long f) const { return balance_ - f >= MIN_BALANCE; }
    bool deduct(long long f) {
        if (!canTravel(f)) return false;
        balance_ -= f;
        return true;
    }
    long long balance() const { return balance_; }
};

class Journey {                         // one trip: a zone, a time, a fare
public:
    Zone farthest; int hour; int minute;
    Journey(Zone z, int h, int m) : farthest(z), hour(h), minute(m) {}
    bool peak() const {
        int t = hour * 60 + minute;
        return (t >= 8 * 60 && t < 10 * 60) || (t >= 17 * 60 && t < 20 * 60);
    }
};

int main() {
    FareTable table;
    SmartCard card(10000);                                  // Rs 100.00
    Journey j(Zone::Outer, 18, 30);
    long long f = table.fare(j.farthest, j.peak());
    std::cout << "Fare (paise): " << f << '\n';
    std::cout << "Journey allowed: " << std::boolalpha << card.deduct(f) << '\n';
    std::cout << "Balance (paise): " << card.balance() << '\n';
    std::cout << "Can travel again with Rs 20 fare: " << card.canTravel(2000) << '\n';
    std::cout << "sizeof(SmartCard) = " << sizeof(SmartCard) << " bytes, sizeof(long long) = " << sizeof(long long) << " bytes\n";
}
