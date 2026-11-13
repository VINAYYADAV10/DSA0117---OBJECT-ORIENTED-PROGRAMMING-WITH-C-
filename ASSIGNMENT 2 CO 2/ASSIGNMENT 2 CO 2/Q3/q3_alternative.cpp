#include <iostream>
#include <iomanip>
// Alternative 1 : ONE function taking a Parcel with optional fields
struct Parcel2
{
    double kg      = 0;
    bool   fragile = false;
    bool   express = false;
    bool   insured = false;
};
double chargeP(const Parcel2& p)
{ return 50.0 * p.kg + (p.fragile ? 15 : 0) + (p.express ? 40 : 0) + (p.insured ? 20 : 0); }

// Alternative 2 : function template (one body for any numeric weight type)
template <typename W>
double chargeT(W weight, bool express = false)
{ return 50.0 * static_cast<double>(weight) + (express ? 40 : 0); }

int main()
{
    std::cout << std::fixed << std::setprecision(2);
    Parcel2 p; p.kg = 2.5; p.insured = true;
    std::cout << chargeP(p) << '\n';
    std::cout << chargeT(2) << ' ' << chargeT(2.5) << ' ' << chargeT(2.0f, true) << '\n';
}
