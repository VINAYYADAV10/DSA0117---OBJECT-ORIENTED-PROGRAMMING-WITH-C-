// Task 11: recommended final design + comparison with a configuration-file fare table
#include <array>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum class Zone { Inner = 0, Middle = 1, Outer = 2 };

namespace Rules {                                         // every rule value lives here only
    constexpr std::array<long long, 3> BASE_PAISE{1000, 2000, 3000};
    constexpr int  PEAK_SURCHARGE_PERCENT = 20;
    constexpr int  CONCESSION_PERCENT = 50;
    constexpr long long MIN_BALANCE_PAISE = 5000;
}
inline bool isPeak(int h, int m) { int t = h * 60 + m; return (t >= 480 && t < 600) || (t >= 1020 && t < 1200); }

long long fare(Zone z, bool peak, bool concession) {
    long long f = Rules::BASE_PAISE[static_cast<std::size_t>(z)];
    if (peak) f += f * Rules::PEAK_SURCHARGE_PERCENT / 100;
    if (concession) f -= f * Rules::CONCESSION_PERCENT / 100;
    return f;
}

class SmartCard {
    long long balance_;
public:
    explicit SmartCard(long long b) : balance_(b) {}
    bool canTravel(long long f) const { return f >= 0 && balance_ - f >= Rules::MIN_BALANCE_PAISE; }
    bool deduct(long long f) { if (!canTravel(f)) return false; balance_ -= f; return true; }
    long long balance() const { return balance_; }
};

// loads z fares from a text file; returns how many were read
std::size_t loadFares(const std::string& path, std::vector<long long>& out) {
    std::ifstream in(path); std::string line;
    while (std::getline(in, line)) { if (line.empty() || line[0] == '#') continue; out.push_back(std::stoll(line)); }
    return out.size();
}

int main() {
    // 1. final design in action
    SmartCard card(10000);
    long long f = fare(Zone::Outer, isPeak(18, 0), false);
    std::cout << "Outer, 18:00 fare = " << f << " paise, allowed = " << std::boolalpha << card.deduct(f)
              << ", balance = " << card.balance() << '\n';

    // 2. configuration-file alternative: read the three fares at start-up
    std::vector<long long> cfg;
    std::cout << "Fares read from fares.cfg: " << loadFares("fares.cfg", cfg) << " -> "
              << cfg[0] << ", " << cfg[1] << ", " << cfg[2] << '\n';

    // 3. start-up time for z = 3 and z = 100000 zone values (generated file)
    for (std::size_t z : {std::size_t(3), std::size_t(1000), std::size_t(100000)}) {
        { std::ofstream o("big.cfg"); for (std::size_t i = 0; i < z; ++i) o << (1000 + 10 * i) << '\n'; }
        std::vector<long long> v; v.reserve(z);
        auto t0 = std::chrono::steady_clock::now();
        loadFares("big.cfg", v);
        auto t1 = std::chrono::steady_clock::now();
        std::cout << "z = " << std::setw(6) << z << "  load time = " << std::fixed << std::setprecision(1)
                  << std::chrono::duration<double, std::micro>(t1 - t0).count() << " us, memory = "
                  << v.size() * sizeof(long long) << " bytes\n";
    }
    std::remove("big.cfg");
    std::cout << "Compiled-in table: 0 us start-up, " << sizeof(Rules::BASE_PAISE) << " bytes, but needs recompile to revise\n";
}
