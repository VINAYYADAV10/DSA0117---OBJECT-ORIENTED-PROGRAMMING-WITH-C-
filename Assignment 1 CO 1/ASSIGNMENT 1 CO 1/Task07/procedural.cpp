// Task 7(a): procedural version - global variable and free functions
#include <iostream>

long long balance = 10000;                       // global: any code can change it
const long long MIN_BALANCE = 5000;

long long fare(int zone, bool peak) {
    long long b = (zone == 0) ? 1000 : (zone == 1) ? 2000 : 3000;
    return peak ? b + b * 20 / 100 : b;
}
bool canTravel(long long f) { return balance - f >= MIN_BALANCE; }
void deduct(long long f) { balance -= f; }       // forgets to check canTravel!

int main() {
    deduct(fare(2, true));  std::cout << "after Outer peak : " << balance << '\n';
    deduct(fare(2, true));  std::cout << "after Outer peak : " << balance << '\n';
    deduct(fare(2, true));  std::cout << "after Outer peak : " << balance << " (below Rs 50 limit - rule broken)\n";
    balance = -999;         std::cout << "any code can set : " << balance << '\n';
}
