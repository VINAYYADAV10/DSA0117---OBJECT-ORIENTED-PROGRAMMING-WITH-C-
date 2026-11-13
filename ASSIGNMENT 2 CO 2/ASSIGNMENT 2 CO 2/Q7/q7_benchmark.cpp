#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

struct Transaction { char type; double amount; };

// ORIGINAL : fixed array, shift left when full  (cost O(K) per transaction)
template <int K>
class ShiftAccount {
    double balance = 0; Transaction last[K]; int count = 0;
public:
    long long moves = 0;
    void deposit(double a)
    {
        balance += a;
        if (count == K) { for (int i = 1; i < K; ++i) last[i-1] = last[i]; moves += K - 1; --count; }
        last[count++] = {'D', a};
    }
    std::vector<Transaction> snapshot() const { return std::vector<Transaction>(last, last + count); }
};

// REDESIGN : circular buffer with a start index (cost O(1) per transaction)
template <int K>
class CircularAccount {
    double balance = 0; Transaction last[K]; int start = 0, count = 0;
public:
    long long moves = 0;                       // always 0 : nothing is ever shifted
    void deposit(double a)
    {
        balance += a;
        int pos = start + count; if (pos >= K) pos -= K;      // avoids '%' on the hot path
        last[pos] = {'D', a};
        if (count == K) { if (++start == K) start = 0; } else ++count;
    }
    std::vector<Transaction> snapshot() const
    {
        std::vector<Transaction> v; v.reserve(count);
        for (int i = 0; i < count; ++i) { int p = start + i; if (p >= K) p -= K; v.push_back(last[p]); }
        return v;
    }
};

template <typename Acc>
double timeIt(long long n, Acc& acc)
{
    double best = 1e18;
    for (int rep = 0; rep < 3; ++rep) {
        auto t0 = std::chrono::steady_clock::now();
        for (long long i = 0; i < n; ++i) acc.deposit((double)(i % 1000));
        auto t1 = std::chrono::steady_clock::now();
        best = std::min(best, std::chrono::duration<double, std::milli>(t1 - t0).count());
    }
    return best;
}
template <int K>
void test(long long n)
{
    ShiftAccount<K> s; CircularAccount<K> c;
    double ts = timeIt(n, s), tc = timeIt(n, c);
    auto a = s.snapshot(), b = c.snapshot();
    bool same = a.size() == b.size();
    for (size_t i = 0; same && i < a.size(); ++i) same = a[i].type == b[i].type && a[i].amount == b[i].amount;
    std::cout << "K=" << K << "\t shift: " << ts << " ms\t circular: " << tc
              << " ms\t speed-up x" << ts / tc << "\t identical statement: " << (same ? "yes" : "NO")
              << "\t moves/txn (shift): " << (double)s.moves / (3.0 * n) << '\n';
}
int main()
{
    const long long N = 2000000;
    std::cout << N << " transactions per run (best of 3)\n";
    test<10>(N); test<50>(N); test<500>(N); test<5000>(N / 10);
}
