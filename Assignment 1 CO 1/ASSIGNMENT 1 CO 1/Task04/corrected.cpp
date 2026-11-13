// Task 4 (corrected): brace initialisation and static_cast remove the surprises
#include <iostream>

int main() {
    int a{7}, b{2};
    double c{static_cast<double>(a) / b};          // intended real division
    // int x{3.7};                                 // ERROR: narrowing double -> int
    int x = static_cast<int>(3.7);                 // explicit, intended truncation
    char ch{static_cast<char>('A' + 2)};
    bool flag{true};                               // bool flag{5}; would be a narrowing error
    unsigned int u{1};
    int s{-1};
    bool smaller = s < static_cast<int>(u);        // compare as signed on purpose
    std::cout << c << ' ' << x << ' ' << ch << ' ' << flag << ' ' << std::boolalpha << smaller << '\n';
}
