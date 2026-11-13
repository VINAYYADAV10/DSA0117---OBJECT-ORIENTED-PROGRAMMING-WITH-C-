// Alternative: public balance - the rule can be broken by any part of the program
#include <iostream>
struct BadCard { long long balance; };
int main() {
    BadCard c{10000};
    c.balance -= 9990;                       // legal, but leaves Rs 0.10
    c.balance = -500;                        // legal, negative balance
    std::cout << "balance = " << c.balance << " (invariants broken)\n";
}
