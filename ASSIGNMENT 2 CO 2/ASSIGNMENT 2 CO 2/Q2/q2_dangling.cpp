#include <iostream>
int& bad()
{
    int local = 42;
    return local;          // reference to a local variable
}
int main()
{
    int& r = bad();        // r refers to a destroyed object
    std::cout << r << '\n';// undefined behaviour
}
