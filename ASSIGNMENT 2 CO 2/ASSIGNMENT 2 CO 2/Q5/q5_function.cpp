#include <iostream>
#include <string>
class BusTicket {
    static int issued;
    static const int CAPACITY = 3;
    int seat; std::string name;
public:
    explicit BusTicket(const std::string& n) : seat(0), name(n)
    { if (issued < CAPACITY) seat = ++issued; }
    ~BusTicket() { std::cout << "  (ticket of " << name << " destroyed)\n"; }
    static int count() { return issued; }
    void print() const
    { std::cout << name << ": " << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting")) << '\n'; }
};
int BusTicket::issued = 0;

void book(const std::string& a, const std::string& b)
{
    BusTicket t1(a), t2(b);            // automatic objects
    t1.print(); t2.print();
}                                       // both destroyed here, count NOT reduced
int main()
{
    book("Asha", "Bala");
    std::cout << "Issued after call 1: " << BusTicket::count() << '\n';
    book("Chitra", "Dev");
    std::cout << "Issued after call 2: " << BusTicket::count() << '\n';
}
