#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

class Time {
    int h, m;
public:
    Time(int hh = 0, int mm = 0) : h(hh), m(mm) {}
    // Design 1 : friend functions (inline keyword, defined in class)
    friend inline int minutesBetweenInline(const Time& a, const Time& b)
    { int x = a.h*60+a.m, y = b.h*60+b.m; return x > y ? x - y : y - x; }
    // Design 1b : same friend, forbidden from inlining
    friend __attribute__((noinline)) int minutesBetweenNoInline(const Time& a, const Time& b)
    { int x = a.h*60+a.m, y = b.h*60+b.m; return x > y ? x - y : y - x; }
    // Design 2 : member function
    int minutesTo(const Time& b) const
    { int x = h*60+m, y = b.h*60+b.m; return x > y ? x - y : y - x; }
    // Design 3 : public getters
    int getH() const { return h; }
    int getM() const { return m; }
};
int viaGetters(const Time& a, const Time& b)
{ int x = a.getH()*60+a.getM(), y = b.getH()*60+b.getM(); return x > y ? x - y : y - x; }

template <typename F>
double run(const std::vector<Time>& t, F f, long long& sink)
{
    double best = 1e18;
    for (int rep = 0; rep < 5; ++rep) {
        long long s = 0;
        auto t0 = std::chrono::steady_clock::now();
        for (int i = 0; i < 10000000; ++i) s += f(t[i & 1023], t[(i * 7 + 3) & 1023]);
        auto t1 = std::chrono::steady_clock::now();
        best = std::min(best, std::chrono::duration<double, std::milli>(t1 - t0).count());
        sink += s;
    }
    return best;
}
int main()
{
    std::vector<Time> t;
    for (int i = 0; i < 1024; ++i) t.emplace_back((i * 13) % 24, (i * 29) % 60);
    long long sink = 0;
    std::cout << "10,000,000 calls (best of 5), ms:\n";
    std::cout << "friend, inline      : " << run(t, [](const Time& a, const Time& b){ return minutesBetweenInline(a,b); }, sink) << '\n';
    std::cout << "friend, noinline    : " << run(t, [](const Time& a, const Time& b){ return minutesBetweenNoInline(a,b); }, sink) << '\n';
    std::cout << "member minutesTo    : " << run(t, [](const Time& a, const Time& b){ return a.minutesTo(b); }, sink) << '\n';
    std::cout << "public getters      : " << run(t, [](const Time& a, const Time& b){ return viaGetters(a,b); }, sink) << '\n';
    std::cout << "checksum " << sink << '\n';
}
