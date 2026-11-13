// Task 5: peak check, surcharge and concession expressions
#include <iostream>

constexpr int SURCHARGE_PERCENT = 20;
constexpr int CONCESSION_PERCENT = 50;

bool isPeakHour(int hour) { return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20); }
bool isPeakTable(int hour) {                      // alternative: lookup table
    static constexpr bool PEAK[24] = {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0};
    return PEAK[hour];
}
long long withSurcharge(long long base, bool peak) { return peak ? base + base * SURCHARGE_PERCENT / 100 : base; }
long long withConcession(long long fare, bool student, bool senior) {
    return (student || senior) ? fare - fare * CONCESSION_PERCENT / 100 : fare;
}

int main() {
    bool ok = true;
    for (int h = 0; h < 24; ++h) ok = ok && (isPeakHour(h) == isPeakTable(h));
    std::cout << "range-check and table agree for all 24 hours: " << std::boolalpha << ok << '\n';
    for (int h : {7, 8, 9, 10, 16, 17, 19, 20})
        std::cout << "hour " << h << " peak? " << isPeakHour(h) << '\n';
    long long f = withSurcharge(3000, true);
    std::cout << "Outer peak fare = " << f << " paise; student = " << withConcession(f, true, false) << " paise\n";

    int i = 5;
    i = i++ + 1;                      // BAD: modifies i twice (undefined before C++17 rules; unspecified result style)
    int j = 5; j++; j = j + 1;        // clear version
    std::cout << "bad style i=" << i << ", clear style j=" << j << '\n';
    int m = 7; m += 3 * 2;            // compound assignment: m = m + (3*2)
    std::cout << "m += 3*2 -> " << m << '\n';
}
