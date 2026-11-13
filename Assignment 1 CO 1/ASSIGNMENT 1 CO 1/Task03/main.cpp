// Task 3: data types, sizeof, limits, double-vs-integer money, overflow
#include <climits>
#include <cfloat>
#include <iomanip>
#include <iostream>

int main() {
    std::cout << std::left << std::setw(26) << "Type (use)" << std::setw(8) << "sizeof" << "Range\n";
    std::cout << std::setw(26) << "bool (peak flag)" << std::setw(8) << sizeof(bool) << "false/true\n";
    std::cout << std::setw(26) << "char (concession code)" << std::setw(8) << sizeof(char) << int(CHAR_MIN) << " to " << int(CHAR_MAX) << '\n';
    std::cout << std::setw(26) << "int (zone no., hour)" << std::setw(8) << sizeof(int) << INT_MIN << " to " << INT_MAX << '\n';
    std::cout << std::setw(26) << "unsigned (journey count)" << std::setw(8) << sizeof(unsigned) << "0 to " << UINT_MAX << '\n';
    std::cout << std::setw(26) << "long long (paise)" << std::setw(8) << sizeof(long long) << LLONG_MIN << " to " << LLONG_MAX << '\n';
    std::cout << std::setw(26) << "float" << std::setw(8) << sizeof(float) << "+-" << FLT_MAX << " (~7 digits)\n";
    std::cout << std::setw(26) << "double (not for money)" << std::setw(8) << sizeof(double) << "+-" << DBL_MAX << " (~15 digits)\n";

    std::cout << "\n-- Precision problem: add Rs 0.10 one million times --\n";
    double rupees = 0.0; long long paise = 0;
    for (int i = 0; i < 1000000; ++i) { rupees += 0.10; paise += 10; }
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "double rupees : " << rupees << "\n";
    std::cout << "integer paise : " << paise / 100 << '.' << std::setw(2) << std::setfill('0') << paise % 100 << std::setfill(' ') << "\n";
    std::cout << "error (double): " << rupees - 100000.0 << "\n";
    std::cout << "0.1+0.2==0.3 ? " << std::boolalpha << (0.1 + 0.2 == 0.3) << "\n";

    std::cout << "\n-- Growth of rounding error with n fares of Rs 0.10 --\n";
    for (long long n : {1000LL, 10000LL, 100000LL, 1000000LL, 10000000LL, 100000000LL}) {
        double s = 0; for (long long i = 0; i < n; ++i) s += 0.10;
        std::cout << std::setw(10) << n << "  error = " << std::scientific << std::setprecision(3) << s - n * 0.10 << "\n";
    }

    std::cout << std::fixed << "\n-- Does int hold a day's network collection? --\n";
    long long network = 3000000LL * 3600;   // worst case: 3,000,000 journeys at Rs 36.00 (paise)
    std::cout << "worst-case daily total (paise) = " << network << "\n";
    std::cout << "INT_MAX                        = " << INT_MAX << "\n";
    std::cout << "fits in int ? " << (network <= INT_MAX) << "  fits in long long ? " << (network <= LLONG_MAX) << "\n";
}
