// Task 8: safe input with cin.fail()/clear()/ignore() and formatted output
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

bool echoInput = false;                          // --echo: print values read from a file/pipe
int readInt(const char* prompt, int lo, int hi) {
    int v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v && v >= lo && v <= hi) { if (echoInput) std::cout << v << '\n'; return v; }
        if (std::cin.eof()) { std::cout << "\nend of input\n"; return lo; }
        if (std::cin.fail()) {                         // letters typed instead of numbers
            std::cin.clear();                          // reset the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad line
            std::cout << "  invalid number, try again\n";
        } else {
            std::cout << "  out of range (" << lo << ".." << hi << "), try again\n";
        }
    }
}
std::string money(long long paise) {              // "Rs 36.00" built with <iomanip>
    std::ostringstream o;
    o << "Rs " << paise / 100 << '.' << std::setw(2) << std::setfill('0') << paise % 100;
    return o.str();
}
int main(int argc, char**) {
    echoInput = argc > 1;
    const long long base[] = {1000, 2000, 3000};
    long long balance = 10000;
    std::cout << "=== Namma Metro Gate ===\n";
    int n = readInt("Number of journeys (1-3): ", 1, 3);
    int zs[3], hs[3];
    for (int i = 0; i < n; ++i) {
        zs[i] = readInt("Zone (0=Inner 1=Middle 2=Outer): ", 0, 2);
        hs[i] = readInt("Hour (0-23): ", 0, 23);
    }
    std::cout << '\n' << std::left << std::setw(4) << "No" << std::setw(8) << "Zone" << std::setw(7) << "Hour"
              << std::right << std::setw(12) << "Fare" << std::setw(14) << "Balance" << '\n';
    for (int i = 1; i <= n; ++i) {
        int zone = zs[i - 1], hour = hs[i - 1];
        bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
        long long f = base[zone]; if (peak) f += f * 20 / 100;
        std::cout << std::left << std::setw(4) << i << std::setw(8) << zone << std::setw(7) << hour << std::right;
        if (balance - f >= 5000) { balance -= f; std::cout << std::setw(12) << money(f) << std::setw(14) << money(balance); }
        else std::cout << std::setw(12) << "DENIED" << std::setw(14) << money(balance);
        std::cout << '\n';
    }
    std::cout << std::fixed << std::setprecision(2) << "Closing balance (double view): " << balance / 100.0 << '\n';
}
