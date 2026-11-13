// Task 10: expected vs actual totals - double rupees vs integer paise, int overflow, timing
#include <chrono>
#include <climits>
#include <cstdint>
#include <iomanip>
#include <iostream>

constexpr long long BASE_PAISE[] = {1000, 2000, 3000};
constexpr double BASE_RUPEES[] = {10.0, 20.0, 30.0};

int main() {
    std::cout << std::fixed;
    std::cout << "Journey mix: zone = i%3, peak when i%4==0 (20% surcharge)\n\n";
    std::cout << std::left << std::setw(12) << "Journeys" << std::setw(20) << "paise total" << std::setw(24)
              << "double Rs total" << std::setw(18) << "difference (Rs)" << "fits int?\n";
    for (long long n : {20000LL, 500000LL, 3000000LL}) {
        long long p = 0; double r = 0.0;
        for (long long i = 0; i < n; ++i) {
            int z = static_cast<int>(i % 3); bool peak = (i % 4 == 0);
            long long f = BASE_PAISE[z]; if (peak) f += f * 20 / 100;
            double g = BASE_RUPEES[z]; if (peak) g *= 1.2;          // 1.2 is not exact in binary
            p += f; r += g;
        }
        double diff = r - p / 100.0;
        std::cout << std::left << std::setw(12) << n << std::setw(20) << p << std::setprecision(6) << std::setw(24) << r
                  << std::scientific << std::setprecision(3) << std::setw(18) << diff << std::fixed << (p <= INT_MAX ? "yes" : "NO (overflow)") << '\n';
    }

    std::cout << "\nMix B (Task 12 style): even journeys get 10% weekend discount and 50% concession, odd pay full\n";
    std::cout << std::left << std::setw(12) << "Journeys" << std::setw(20) << "paise total" << std::setw(24) << "double Rs total" << "difference (Rs)\n";
    for (long long n : {20000LL, 500000LL, 3000000LL}) {
        long long p = 0; double r = 0.0;
        for (long long i = 0; i < n; ++i) {
            int z = static_cast<int>(i % 3);
            long long f = BASE_PAISE[z]; double g = BASE_RUPEES[z];
            if (i % 2 == 0) { f = f * 90 / 100; f = f * 50 / 100; g = g * 0.9; g = g * 0.5; }
            p += f; r += g;
        }
        std::cout << std::left << std::setw(12) << n << std::setw(20) << p << std::setprecision(6) << std::setw(24) << r
                  << std::scientific << std::setprecision(3) << r - p / 100.0 << std::fixed << '\n';
    }

    // What an int accumulator would hold at 3,000,000 journeys (wraps modulo 2^32)
    std::uint32_t wrap = 0; long long exact = 0; float fl = 0.0f; double db = 0.0;
    for (long long i = 0; i < 3000000; ++i) {
        long long f = BASE_PAISE[i % 3]; if (i % 4 == 0) f += f * 20 / 100;
        wrap += static_cast<std::uint32_t>(f); exact += f; fl += static_cast<float>(f); db += static_cast<double>(f);
    }
    std::cout << "\nNetwork total, 3,000,000 journeys (paise):\n";
    std::cout << "  long long : " << exact << "  (correct)\n";
    std::cout << "  int (wrap): " << static_cast<std::int32_t>(wrap) << "  (OVERFLOW: wrong value)\n";
    std::cout << "  double    : " << std::setprecision(1) << db << "  (exact here: integers < 2^53)\n";
    std::cout << "  float     : " << fl << "  (loses precision)\n";

    // time per addition
    using clk = std::chrono::steady_clock;
    const long long N = 200000000LL;
    volatile std::int32_t vi = 0; volatile long long vl = 0; volatile double vd = 0;
    auto t0 = clk::now(); for (long long i = 0; i < N; ++i) vi = vi + 1;
    auto t1 = clk::now(); for (long long i = 0; i < N; ++i) vl = vl + 1;
    auto t2 = clk::now(); for (long long i = 0; i < N; ++i) vd = vd + 1.0;
    auto t3 = clk::now();
    auto ns = [&](auto a, auto b) { return std::chrono::duration<double, std::nano>(b - a).count() / N; };
    std::cout << "\nTime per addition over " << N << " additions (volatile, -O0 style):\n" << std::setprecision(3)
              << "  int       " << ns(t0, t1) << " ns   (4 bytes)\n"
              << "  long long " << ns(t1, t2) << " ns   (8 bytes)\n"
              << "  double    " << ns(t2, t3) << " ns   (8 bytes)\n";
}
