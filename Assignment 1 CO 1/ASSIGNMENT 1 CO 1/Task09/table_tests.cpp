// Alternative: table-driven tests - a new boundary case is one new row
#include <iostream>
#include <vector>
bool isPeak(int h, int m) { int t = h*60+m; return (t>=480&&t<600)||(t>=1020&&t<1200); }
struct Case { int h, m; bool expected; };
int main() {
    std::vector<Case> cases = {{7,59,false},{8,0,true},{9,59,true},{10,0,false},{16,59,false},{17,0,true},{19,59,true},{20,0,false},{0,0,false},{23,59,false}};
    int bad = 0;
    for (const Case& c : cases) if (isPeak(c.h, c.m) != c.expected) { ++bad; std::cout << "FAIL " << c.h << ':' << c.m << '\n'; }
    std::cout << cases.size() << " cases, " << bad << " failures\n";
}
