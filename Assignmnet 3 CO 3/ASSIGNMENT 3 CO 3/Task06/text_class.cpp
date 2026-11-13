#include <cstring>
#include <iostream>
using namespace std;

class Text {
    char* data;
public:
    Text(const char* s = "") {
        data = new char[strlen(s) + 1];
        strcpy(data, s);
    }

    Text(const Text& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
        cout << "[copy] ";
    }

    Text& operator=(const Text& other) {
        if (this == &other) return *this;
        char* fresh = new char[strlen(other.data) + 1];
        strcpy(fresh, other.data);
        delete[] data;
        data = fresh;
        return *this;
    }

    ~Text() { delete[] data; }

    Text operator+(const Text& other) const {
        size_t n = strlen(data) + strlen(other.data);
        char* temp = new char[n + 1];
        strcpy(temp, data);
        strcat(temp, other.data);
        Text result(temp);
        delete[] temp;
        return result;
    }

    bool operator==(const Text& other) const {
        return strcmp(data, other.data) == 0;
    }

    bool operator!=(const Text& other) const { return !(*this == other); }

    friend ostream& operator<<(ostream& os, const Text& t) {
        return os << t.data;
    }
};

int main() {
    Text a("Hello "), b("C++"), c("!");
    Text message = a + b + c;
    cout << '\n' << message << '\n';

    Text empty;
    cout << "empty=[" << empty << "]\n";

    message = message;
    cout << boolalpha << (message != a) << '\n';
}