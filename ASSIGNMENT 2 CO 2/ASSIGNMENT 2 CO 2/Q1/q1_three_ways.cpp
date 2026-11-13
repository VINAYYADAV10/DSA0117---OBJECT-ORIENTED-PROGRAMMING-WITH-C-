#include <iostream>
#include <chrono>

// 1. call by value : parameter is a copy on the callee's stack
void concessionValue(long long fee, int percent)
{
    fee -= fee * percent / 100;
    std::cout << "  inside value fn : " << fee << '\n';
}
// 2. call by reference : parameter is an alias of the caller's variable
void concessionRef(long long& fee, int percent) { fee -= fee * percent / 100; }
// 3. call by pointer : parameter is a copy of the ADDRESS of the caller's variable
void concessionPtr(long long* fee, int percent)
{
    if (fee) *fee -= *fee * percent / 100;
}
// Design decision : return the new fee (pure function, composable)
long long concessionReturn(long long fee, int percent)
{
    return fee - fee * percent / 100;
}

struct Student { char name[64]; int marks[50]; long long fee; };

__attribute__((noinline)) long long readByValue(Student s)          { return s.fee + s.marks[0]; }
__attribute__((noinline)) long long readByRef(Student& s)           { return s.fee + s.marks[0]; }
__attribute__((noinline)) long long readByConstRef(const Student& s){ return s.fee + s.marks[0]; }

int main()
{
    long long f1 = 45000, f2 = 45000, f3 = 45000;
    concessionValue(f1, 10);
    concessionRef(f2, 10);
    concessionPtr(&f3, 10);
    std::cout << "stored fee after value   : " << f1 << '\n';
    std::cout << "stored fee after ref     : " << f2 << '\n';
    std::cout << "stored fee after pointer : " << f3 << '\n';

    long long fee = 45000;      // merit 10%, sports 15%, single parent 25%
    long long inPlace = fee;
    concessionRef(inPlace, 10); concessionRef(inPlace, 15); concessionRef(inPlace, 25);
    long long returned = concessionReturn(concessionReturn(concessionReturn(fee, 10), 15), 25);
    std::cout << "three concessions in place : " << inPlace  << '\n';
    std::cout << "three concessions returned : " << returned << " (original still " << fee << ")\n";

    std::cout << "sizeof(long long) = " << sizeof(long long)
              << ", sizeof(Student) = " << sizeof(Student) << " bytes\n";

    Student s{"Asha", {90}, 45000};
    const int N = 20000000;
    long long sum = 0;
    auto t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) { s.fee = i; sum += readByValue(s); }
    auto t1 = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) { s.fee = i; sum += readByRef(s); }
    auto t2 = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) { s.fee = i; sum += readByConstRef(s); }
    auto t3 = std::chrono::steady_clock::now();
    auto ms = [](auto a, auto b){ return std::chrono::duration<double, std::milli>(b - a).count(); };
    std::cout << "20,000,000 calls  by value: " << ms(t0,t1) << " ms, by ref: " << ms(t1,t2)
              << " ms, by const ref: " << ms(t2,t3) << " ms (checksum " << sum << ")\n";
}
