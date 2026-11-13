#include <iostream>
#include <iomanip>

struct Parcel { double kg; bool fragile; };

// weight in grams (int)
double charge(int grams, bool express = false, bool insured = false)
{
    std::cout << "[grams version]  ";
    return 50.0 * grams / 1000 + (express ? 40 : 0) + (insured ? 20 : 0);
}
// weight in kilograms (double)
double charge(double kg, bool express = false, bool insured = false)
{
    std::cout << "[kg version]     ";
    return 50.0 * kg + (express ? 40 : 0) + (insured ? 20 : 0);
}
// a Parcel object (fragile parcels pay a Rs 15 handling fee)
double charge(const Parcel& p, bool express = false, bool insured = false)
{
    std::cout << "[Parcel version] ";
    return 50.0 * p.kg + (p.fragile ? 15 : 0) + (express ? 40 : 0) + (insured ? 20 : 0);
}

int main()
{
    std::cout << std::fixed << std::setprecision(2);
    Parcel p{3.0, true};
    double r;
    r = charge(2);               std::cout << r << "  <- charge(2)\n";
    r = charge(2.0f);            std::cout << r << "  <- charge(2.0f)\n";
    r = charge(2.5);             std::cout << r << "  <- charge(2.5)\n";
    r = charge(2500, true);      std::cout << r << "  <- charge(2500, true)\n";
    r = charge(p);               std::cout << r << "  <- charge(p)\n";
    r = charge(2.5, true, true); std::cout << r << "  <- charge(2.5, true, true)\n";
}
