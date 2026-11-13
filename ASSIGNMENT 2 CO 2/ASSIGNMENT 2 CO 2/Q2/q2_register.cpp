#include <iostream>
#include <vector>

int& highest(int m[], int n)                  // return by reference
{
    int idx = 0;
    for (int i = 1; i < n; ++i) if (m[i] > m[idx]) idx = i;
    return m[idx];
}
const int& highestConst(const int m[], int n) // return by const reference
{
    int idx = 0;
    for (int i = 1; i < n; ++i) if (m[i] > m[idx]) idx = i;
    return m[idx];
}
int highestCopy(const int m[], int n)         // return by value (copy)
{
    int idx = 0;
    for (int i = 1; i < n; ++i) if (m[i] > m[idx]) idx = i;
    return m[idx];
}
void print(const int m[], int n)
{
    for (int i = 0; i < n; ++i) std::cout << m[i] << ' ';
    std::cout << '\n';
}
int main()
{
    int marks[5] = {62, 78, 91, 55, 84};
    std::cout << "original            : "; print(marks, 5);

    highest(marks, 5) += 2;                    // moderation applied directly
    std::cout << "after highest()+=2  : "; print(marks, 5);

    highest(marks, 5) = 95;                    // call on the LEFT of =
    std::cout << "after highest()=95  : "; print(marks, 5);

    int copy = highestCopy(marks, 5);
    copy += 5;                                 // changes only the copy
    std::cout << "after copy += 5     : "; print(marks, 5);

    const int& cr = highestConst(marks, 5);    // read-only view
    // cr += 1;   // error: assignment of read-only reference 'cr'
    std::cout << "const reference read: " << cr << '\n';

    // ---- Changed condition : std::vector that grows ----
    std::vector<int> v = {62, 78, 91};
    int& r = v[2];
    const int* before = v.data();
    std::cout << "\ncapacity before growth: " << v.capacity() << '\n';
    for (int i = 0; i < 10; ++i) v.push_back(50 + i);   // forces reallocation
    const int* after = v.data();
    std::cout << "capacity after growth : " << v.capacity() << '\n';
    std::cout << "buffer moved          : " << std::boolalpha << (before != after) << '\n';
    std::cout << "r still refers to v[2]: " << (&r == &v[2]) << "  (false => r is dangling)\n";
}
