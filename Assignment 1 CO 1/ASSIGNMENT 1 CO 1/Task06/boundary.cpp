// Task 6 extension: journeys at exactly 10:00 AM and 8:00 PM (and 8:00, 17:00)
#include <iostream>

bool isPeak(int hour, int minute) {
    int t = hour * 60 + minute;                       // minutes since midnight
    return (t >= 8 * 60 && t < 10 * 60) || (t >= 17 * 60 && t < 20 * 60);
}
int main() {
    struct T { int h, m; } tests[] = {{7,59},{8,0},{9,59},{10,0},{16,59},{17,0},{19,59},{20,0}};
    std::cout << std::boolalpha;
    for (auto t : tests)
        std::cout << t.h << ':' << (t.m < 10 ? "0" : "") << t.m << " peak = " << isPeak(t.h, t.m) << '\n';
}
