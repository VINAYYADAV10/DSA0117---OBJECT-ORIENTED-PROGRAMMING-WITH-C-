// Task 12-A/B evidence: adding Airport to the ORIGINAL design (enum + array + switch)
#include <iostream>
enum class Zone { Inner, Middle, Outer, Airport };          // edit 1: enum value added
constexpr int BASE_PAISE[] = {1000, 2000, 3000};            // edit 2 forgotten: no 4th entry!
long long fare(Zone z, bool peak) {
    long long base = 0;
    switch (z) {                                            // edit 3 forgotten: no case for Airport
        case Zone::Inner:  base = BASE_PAISE[0]; break;
        case Zone::Middle: base = BASE_PAISE[1]; break;
        case Zone::Outer:  base = BASE_PAISE[2]; break;
    }
    if (peak) base += base * 20 / 100;
    return base;
}
int main() { std::cout << "Airport fare from old design = " << fare(Zone::Airport, false) << " paise (should be 6000)\n"; }
