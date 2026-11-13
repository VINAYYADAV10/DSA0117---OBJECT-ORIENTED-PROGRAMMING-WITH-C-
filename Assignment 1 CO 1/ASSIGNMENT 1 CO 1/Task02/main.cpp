// Task 2: tokens, keywords, identifiers and constants - one place for all fare values
#include <iostream>

#define OLD_SURCHARGE 20                       // macro: no type, no scope
constexpr int PEAK_SURCHARGE_PERCENT = 20;     // typed, scoped compile-time constant
constexpr long long MIN_BALANCE_PAISE = 5000;
const int RUNTIME_LIMIT = static_cast<int>(MIN_BALANCE_PAISE) + 0;  // const (may be runtime)

enum class Zone { Inner, Middle, Outer };      // scoped enumeration
enum OldZone { INNER, MIDDLE, OUTER };         // plain enum leaks names
constexpr int BASE_PAISE[] = {1000, 2000, 3000};

int main() {
    int fare = BASE_PAISE[static_cast<int>(Zone::Middle)];   // identifier, constant, punctuators
    std::cout << "Tokens in the line above: keyword(int) identifier(fare) operator(=) "
                 "constant(1000) punctuator(;)\n";
    std::cout << "constexpr surcharge = " << PEAK_SURCHARGE_PERCENT
              << ", macro surcharge = " << OLD_SURCHARGE << '\n';
    std::cout << "Middle fare (paise) = " << fare << '\n';

    int x = INNER;              // plain enum converts silently to int
    int y = OUTER;
    std::cout << "Plain enum: INNER == 0 ? " << (x == 0) << ", INNER == OUTER-2 ? " << (x == y - 2) << '\n';
    // int bad = Zone::Inner;   // ERROR with enum class: no implicit conversion
    // Zone z = 1;              // ERROR: int is not a Zone
    Zone z = Zone::Outer;
    std::cout << "enum class needs a cast: " << static_cast<int>(z) << '\n';
    std::cout << "sizeof(Zone)=" << sizeof(Zone) << " sizeof(BASE_PAISE)=" << sizeof(BASE_PAISE)
              << " RUNTIME_LIMIT=" << RUNTIME_LIMIT << '\n';
}
