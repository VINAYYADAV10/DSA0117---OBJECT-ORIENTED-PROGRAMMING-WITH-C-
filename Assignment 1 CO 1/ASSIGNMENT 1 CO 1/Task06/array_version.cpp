// Alternative: fare looked up from an array indexed by zone, with a fourth zone added
#include <iostream>
enum class Zone { Inner, Middle, Outer, Airport };
constexpr long long FARE[] = {1000, 2000, 3000, 6000};
long long fare(Zone z, bool peak) {
    long long f = FARE[static_cast<int>(z)];
    return peak ? f + f * 20 / 100 : f;
}
int main() { std::cout << "Airport peak = " << fare(Zone::Airport, true) << " paise (only the table changed)\n"; }
