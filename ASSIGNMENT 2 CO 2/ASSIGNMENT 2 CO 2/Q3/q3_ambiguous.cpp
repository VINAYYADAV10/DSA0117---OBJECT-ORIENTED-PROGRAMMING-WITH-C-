#include <iostream>
double charge(double weight)               { return weight * 50; }
double charge(double weight, bool express) { return weight * 50 + (express ? 40 : 0); }
double charge(double weight, bool express = false, bool insured = false)
{ return weight * 50 + (express ? 40 : 0) + (insured ? 20 : 0); }
int main()
{
    std::cout << charge(2.5) << '\n';          // ambiguous: overload 1 or 3 ?
    std::cout << charge(2.5, true) << '\n';    // ambiguous: overload 2 or 3 ?
}
