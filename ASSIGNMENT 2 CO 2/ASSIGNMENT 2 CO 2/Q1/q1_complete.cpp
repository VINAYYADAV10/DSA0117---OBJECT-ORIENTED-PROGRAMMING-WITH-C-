#include <iostream>
void applyByValue(long long fee, int percent)
{
    fee -= fee * percent / 100;   // changes only the local copy
}
void applyConcession(long long& fee, int percent)
{
    // TODO 1 (completed): call by reference, integer arithmetic
    fee -= fee * percent / 100;
}
int main()
{
    long long hostelFee = 45000;
    applyByValue(hostelFee, 10);
    std::cout << "after call by value : " << hostelFee << '\n';
    applyConcession(hostelFee, 10);
    std::cout << "after call by reference: " << hostelFee << '\n';
}
