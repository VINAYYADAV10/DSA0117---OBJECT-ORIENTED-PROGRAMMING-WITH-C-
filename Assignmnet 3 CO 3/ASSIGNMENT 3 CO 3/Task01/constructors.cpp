#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class Book {
    string title, author;
    int copies;

    static int validCopies(int n) {
        if (n < 0) throw invalid_argument("copies cannot be negative");
        return n;
    }
public:
    Book() : Book("Untitled", "Unknown", 0) {}
    explicit Book(const string& t) : Book(t, "Unknown", 1) {}
    Book(const string& t, const string& a, int n)
        : title(t), author(a), copies(validCopies(n)) {}

    void display() const {
        cout << title << " | " << author << " | copies: " << copies << '\n';
    }
};

int main() {
    Book empty;
    Book donated("C++ Basics");
    Book full("Object Oriented Programming", "B. Stroustrup", 5);
    empty.display();
    donated.display();
    full.display();

    try {
        Book invalid("Bad record", "Unknown", -2);
    } catch (const invalid_argument& e) {
        cout << "Rejected: " << e.what() << '\n';
    }
}