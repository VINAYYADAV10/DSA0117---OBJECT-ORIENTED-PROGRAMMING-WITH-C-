#include <iostream>
#include <vector>
#include <chrono>

int  highestIndex(const std::vector<int>& m)
{ int idx = 0; for (int i = 1; i < (int)m.size(); ++i) if (m[i] > m[idx]) idx = i; return idx; }
int* highestPtr(std::vector<int>& m)
{ int* p = &m[0]; for (auto& x : m) if (x > *p) p = &x; return p; }
int& highestRef(std::vector<int>& m)
{ int* p = &m[0]; for (auto& x : m) if (x > *p) p = &x; return *p; }

int main()
{
    std::vector<int> marks = {62, 78, 91, 55, 84};
    int i = highestIndex(marks);  marks[i] += 2;        // index version
    *highestPtr(marks) += 2;                            // pointer version
    highestRef(marks)  += 2;                            // reference version
    std::cout << "highest after three +2 : " << marks[2] << " (expected 97)\n";

    int idx = highestIndex(marks);
    int* p  = highestPtr(marks);
    int& r  = highestRef(marks);
    const int* oldBuffer = marks.data();
    marks.reserve(1000);                                // vector grows -> reallocation
    std::cout << "buffer moved      : " << std::boolalpha << (oldBuffer != marks.data()) << '\n';
    std::cout << "index still valid : " << marks[idx] << '\n';
    std::cout << "pointer valid?    : " << (p == &marks[idx]) << '\n';
    std::cout << "reference valid?  : " << (&r == &marks[idx]) << '\n';

    std::vector<int> big(5000000);
    for (size_t k = 0; k < big.size(); ++k) big[k] = (int)((k * 2654435761u) % 1000003);
    long long s = 0;
    auto t0 = std::chrono::steady_clock::now();
    for (int k = 0; k < 20; ++k) s += highestIndex(big);
    auto t1 = std::chrono::steady_clock::now();
    for (int k = 0; k < 20; ++k) s += *highestPtr(big);
    auto t2 = std::chrono::steady_clock::now();
    for (int k = 0; k < 20; ++k) s += highestRef(big);
    auto t3 = std::chrono::steady_clock::now();
    auto ms = [](auto a, auto b){ return std::chrono::duration<double, std::milli>(b - a).count(); };
    std::cout << "n=5,000,000 x20 : index " << ms(t0,t1) << " ms, pointer " << ms(t1,t2)
              << " ms, reference " << ms(t2,t3) << " ms (" << s << ")\n";
}
