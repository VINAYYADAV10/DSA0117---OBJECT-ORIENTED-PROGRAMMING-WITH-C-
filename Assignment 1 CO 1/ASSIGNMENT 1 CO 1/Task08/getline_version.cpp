// Alternative: getline + stoi inside try/catch
#include <iostream>
#include <string>
int readInt(const char* prompt, int lo, int hi) {
    std::string line;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) return lo;
        try {
            size_t pos = 0;
            int v = std::stoi(line, &pos);
            if (pos != line.size()) throw std::invalid_argument("trailing");   // rejects "12abc"
            if (v < lo || v > hi) throw std::out_of_range("range");
            return v;
        } catch (const std::exception&) { std::cout << "  invalid, try again\n"; }
    }
}
int main() {
    int a = readInt("Hour (0-23): ", 0, 23);
    int b = readInt("Zone (0-2): ", 0, 2);
    std::cout << "hour=" << a << " zone=" << b << '\n';
}
