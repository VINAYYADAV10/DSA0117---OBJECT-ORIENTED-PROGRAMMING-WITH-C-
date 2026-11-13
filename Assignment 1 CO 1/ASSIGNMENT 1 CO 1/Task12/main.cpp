// Task 12-C: revised (MODIFIED) design - fare table by zone, separate discount rule, Pass class
#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

enum class Zone { Inner = 0, Middle = 1, Outer = 2, Airport = 3 };
constexpr std::size_t ZONE_COUNT = 4;

namespace Rules {
    constexpr std::array<long long, ZONE_COUNT> BASE_PAISE{1000, 2000, 3000, 6000};
    constexpr int PEAK_SURCHARGE_PERCENT = 20;
    constexpr int WEEKEND_DISCOUNT_PERCENT = 10;
    constexpr int CONCESSION_PERCENT = 50;
    constexpr long long MIN_BALANCE_PAISE = 5000;
}
static_assert(Rules::BASE_PAISE[ZONE_COUNT - 1] > 0, "fare table must have an entry for every zone");
inline bool isPeak(int h, int m) { int t = h * 60 + m; return (t >= 480 && t < 600) || (t >= 1020 && t < 1200); }

struct Journey { Zone zone; int hour, minute; bool weekend; bool concession; int day; };

// Separate rule: peak surcharge and weekend discount NEVER combine (peak wins).
long long applyTimeRule(long long base, bool peak, bool weekend) {
    if (peak) return base + base * Rules::PEAK_SURCHARGE_PERCENT / 100;
    if (weekend) return base - base * Rules::WEEKEND_DISCOUNT_PERCENT / 100;
    return base;
}
long long fare(const Journey& j) {
    long long f = applyTimeRule(Rules::BASE_PAISE[static_cast<std::size_t>(j.zone)], isPeak(j.hour, j.minute), j.weekend);
    if (j.concession) f -= f * Rules::CONCESSION_PERCENT / 100;
    return f;
}

class Pass {                                               // monthly pass: unlimited in two chosen zones
    std::array<bool, ZONE_COUNT> zones_{};
    int from_, to_;
public:
    Pass(Zone a, Zone b, int fromDay, int toDay) : from_(fromDay), to_(toDay) {
        zones_[static_cast<std::size_t>(a)] = true; zones_[static_cast<std::size_t>(b)] = true; }
    bool covers(Zone z, int day) const { return day >= from_ && day <= to_ && zones_[static_cast<std::size_t>(z)]; }
};

class SmartCard {
    long long balance_;
    const Pass* pass_ = nullptr;
public:
    explicit SmartCard(long long b) : balance_(b) {}
    void attach(const Pass* p) { pass_ = p; }
    bool travel(const Journey& j, long long& charged) {
        if (pass_ && pass_->covers(j.zone, j.day)) { charged = 0; return true; }   // pass: free, no balance check
        long long f = fare(j);
        if (balance_ - f < Rules::MIN_BALANCE_PAISE) { charged = 0; return false; }
        balance_ -= f; charged = f; return true;
    }
    long long balance() const { return balance_; }
};

int main() {
    int pass = 0, fail = 0;
    auto check = [&](const std::string& name, long long expect, long long actual) {
        bool ok = expect == actual; (ok ? pass : fail)++;
        std::cout << std::left << std::setw(50) << name << std::right << std::setw(6) << expect << std::setw(7) << actual
                  << "  " << (ok ? "PASS" : "FAIL") << '\n'; };
    std::cout << std::left << std::setw(50) << "Case" << std::right << std::setw(6) << "Expect" << std::setw(7) << "Actual" << "  Result\n"
              << std::string(70, '-') << '\n';
    //                           zone         h   m  weekend conc  day
    check("Airport weekday off-peak 12:00",      6000, fare({Zone::Airport,12, 0,false,false,1}));
    check("Airport weekday peak 18:00 (Rs 72)",  7200, fare({Zone::Airport,18, 0,false,false,1}));
    check("Outer weekend off-peak 12:00 (10% off)", 2700, fare({Zone::Outer,12, 0,true, false,6}));
    check("Outer weekend PEAK 18:00 (no discount)", 3600, fare({Zone::Outer,18, 0,true, false,6}));
    check("Weekend boundary 10:00 off-peak Inner",   900, fare({Zone::Inner,10, 0,true, false,6}));
    check("Weekend boundary 08:00 peak Inner",      1200, fare({Zone::Inner, 8, 0,true, false,6}));
    check("Student Airport weekend off-peak",       2700, fare({Zone::Airport,12,0,true, true, 6}));
    check("Original 3 zones unchanged: Middle peak", 2400, fare({Zone::Middle,9,0,false,false,1}));

    Pass monthly(Zone::Inner, Zone::Middle, 1, 30);
    SmartCard card(5500);                                  // only Rs 55: normal Outer fare would be denied
    card.attach(&monthly);
    long long c = 0;
    check("Pass: Inner journey allowed (charged 0)", 1, card.travel({Zone::Inner,9,0,false,false,5}, c));
    check("Pass: charged amount", 0, c);
    check("Pass: Middle peak allowed on low balance", 1, card.travel({Zone::Middle,18,0,false,false,6}, c));
    check("Pass: Outer not covered, Rs 30 leaves Rs 25 -> denied", 0, card.travel({Zone::Outer,12,0,false,false,7}, c));
    check("Pass expired on day 31 -> Inner denied", 0, card.travel({Zone::Inner,12,0,false,false,31}, c));
    check("Balance untouched by pass journeys", 5500, card.balance());
    std::cout << std::string(70, '-') << "\nPassed " << pass << ", failed " << fail << '\n';

    // timing: switch-style vs table-style lookup is irrelevant to correctness; measure the final fare()
    auto t0 = std::chrono::steady_clock::now();
    volatile long long sink = 0;
    const long long N = 20000000;
    for (long long i = 0; i < N; ++i) sink = sink + fare({static_cast<Zone>(i & 3), static_cast<int>(i % 24), 0, (i & 7) == 0, false, 1});
    auto t1 = std::chrono::steady_clock::now();
    std::cout << "fare() cost: " << std::fixed << std::setprecision(2)
              << std::chrono::duration<double, std::nano>(t1 - t0).count() / N << " ns per journey\n";
    return fail == 0 ? 0 : 1;
}
