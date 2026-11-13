// Task 9: complete fare logic with validation and tests
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum class Zone { Inner = 0, Middle = 1, Outer = 2 };

constexpr long long BASE_PAISE[] = {1000, 2000, 3000};
constexpr int  PEAK_SURCHARGE_PERCENT = 20;
constexpr int  CONCESSION_PERCENT = 50;
constexpr long long MIN_BALANCE_PAISE = 5000;

bool isPeak(int hour, int minute) {
    int t = hour * 60 + minute;
    return (t >= 8 * 60 && t < 10 * 60) || (t >= 17 * 60 && t < 20 * 60);
}
bool validZone(int z) { return z >= 0 && z <= 2; }

long long fare(Zone z, bool peak, bool concession) {
    long long f = BASE_PAISE[static_cast<int>(z)];
    if (peak) f += f * PEAK_SURCHARGE_PERCENT / 100;
    if (concession) f -= f * CONCESSION_PERCENT / 100;
    return f;
}

class SmartCard {
    long long balance_;
public:
    explicit SmartCard(long long b) : balance_(b) {}
    bool canTravel(long long f) const { return balance_ - f >= MIN_BALANCE_PAISE; }
    bool deduct(long long f) { if (!canTravel(f)) return false; balance_ -= f; return true; }
    bool recharge(long long amt) { if (amt <= 0) return false; balance_ += amt; return true; }
    long long balance() const { return balance_; }
};

std::string money(long long p) {
    std::ostringstream o;
    o << "Rs " << p / 100 << '.' << std::setw(2) << std::setfill('0') << p % 100;
    return o.str();
}

// parse "zone hour" text safely; returns false on bad input
bool parseJourney(const std::string& line, int& zone, int& hour) {
    std::istringstream in(line);
    if (!(in >> zone >> hour)) return false;
    return validZone(zone) && hour >= 0 && hour <= 23;
}

int main() {
    int pass = 0, fail = 0;
    auto check = [&](const std::string& name, long long expected, long long actual) {
        bool ok = expected == actual;
        (ok ? pass : fail)++;
        std::cout << std::left << std::setw(46) << name << std::right << std::setw(7) << expected
                  << std::setw(8) << actual << "   " << (ok ? "PASS" : "FAIL") << '\n';
    };
    std::cout << std::left << std::setw(46) << "Test case" << std::right << std::setw(7) << "Expect"
              << std::setw(8) << "Actual" << "   Result\n" << std::string(72, '-') << '\n';

    // A. normal journeys in each zone, off-peak and peak (paise)
    check("Inner off-peak 12:00", 1000, fare(Zone::Inner, isPeak(12,0), false));
    check("Inner peak 08:30", 1200, fare(Zone::Inner, isPeak(8,30), false));
    check("Middle off-peak 14:00", 2000, fare(Zone::Middle, isPeak(14,0), false));
    check("Middle peak 18:00", 2400, fare(Zone::Middle, isPeak(18,0), false));
    check("Outer off-peak 21:00", 3000, fare(Zone::Outer, isPeak(21,0), false));
    check("Outer peak 17:30", 3600, fare(Zone::Outer, isPeak(17,30), false));
    check("Student Outer peak 17:30", 1800, fare(Zone::Outer, true, true));
    // B. boundaries
    check("Boundary 08:00 is peak (Inner)", 1200, fare(Zone::Inner, isPeak(8,0), false));
    check("Boundary 10:00 is off-peak (Inner)", 1000, fare(Zone::Inner, isPeak(10,0), false));
    check("Boundary 17:00 is peak (Inner)", 1200, fare(Zone::Inner, isPeak(17,0), false));
    check("Boundary 20:00 is off-peak (Inner)", 1000, fare(Zone::Inner, isPeak(20,0), false));
    check("Boundary 07:59 off-peak", 0, isPeak(7,59));
    check("Boundary 19:59 peak", 1, isPeak(19,59));
    {   SmartCard c(6000);   // Rs 60, fare Rs 10 -> leaves exactly Rs 50
        check("Leaves exactly Rs 50 -> allowed", 1, c.canTravel(1000));
        SmartCard d(5999);
        check("Leaves Rs 49.99 -> denied", 0, d.canTravel(1000)); }
    // C. invalid input
    int z = 0, h = 0;
    check("Unknown zone '5 9' rejected", 0, parseJourney("5 9", z, h));
    check("Letters for hour '1 ab' rejected", 0, parseJourney("1 ab", z, h));
    check("Hour 24 rejected", 0, parseJourney("1 24", z, h));
    check("Valid '2 18' accepted", 1, parseJourney("2 18", z, h));
    { SmartCard c(10000); check("Negative recharge rejected", 0, c.recharge(-500));
      check("Balance unchanged after bad recharge", 10000, c.balance()); }
    // D. five journeys calculated by hand: total = 1000+2400+3000+3600+1200 = 11200
    SmartCard card(50000);
    struct J { Zone z; int h, m; } js[] = {{Zone::Inner,10,0},{Zone::Middle,8,30},{Zone::Outer,12,0},{Zone::Outer,17,0},{Zone::Inner,19,59}};
    long long total = 0;
    for (const J& j : js) { long long f = fare(j.z, isPeak(j.h, j.m), false); if (card.deduct(f)) total += f; }
    check("5 journeys hand total (Rs 112.00)", 11200, total);
    check("Balance after 5 journeys (Rs 388.00)", 38800, card.balance());

    std::cout << std::string(72, '-') << "\nPassed " << pass << ", failed " << fail << "\n";
    std::cout << "Example money format: " << money(11200) << "  " << money(1205) << '\n';
    return fail == 0 ? 0 : 1;
}
