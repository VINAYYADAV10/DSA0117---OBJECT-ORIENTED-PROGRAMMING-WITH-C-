#include <iostream>
class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};
int minutesBetween(const Time& a, const Time& b)
{
    // TODO 1 (completed)
    int ta = a.h * 60 + a.m;
    int tb = b.h * 60 + b.m;
    return ta > tb ? ta - tb : tb - ta;
}
bool earlier(const Time& a, const Time& b)
{
    // TODO 2 (completed)
    return a.h * 60 + a.m < b.h * 60 + b.m;
}
int main()
{
    Time departure(9, 45), arrival(13, 10);
    std::cout << minutesBetween(departure, arrival) << ' '
              << std::boolalpha << earlier(arrival, departure) << '\n';

    // correctness checks
    Time a(11, 59), b(12, 1), c(12, 0), d(12, 0);
    std::cout << "11:59 vs 12:01 -> " << minutesBetween(a, b) << ' ' << earlier(a, b) << ' ' << earlier(b, a) << '\n';
    std::cout << "12:00 vs 12:00 -> " << minutesBetween(c, d) << ' ' << earlier(c, d) << ' ' << earlier(d, c) << '\n';
    Time e(0, 0), f(23, 59);
    std::cout << "00:00 vs 23:59 -> " << minutesBetween(e, f) << ' ' << earlier(e, f) << '\n';
}
