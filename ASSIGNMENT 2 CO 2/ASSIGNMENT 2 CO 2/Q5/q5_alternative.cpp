#include <iostream>
#include <string>
class TicketOffice {                    // one office per bus: two buses can run together
    int capacity, issued;
public:
    explicit TicketOffice(int cap) : capacity(cap), issued(0) {}
    int nextSeat() { return issued < capacity ? ++issued : 0; }
    int count() const { return issued; }
};
class BusTicket {
    int seat; std::string name;
public:
    BusTicket(const std::string& n, TicketOffice& office) : seat(office.nextSeat()), name(n) {}
    void print() const
    { std::cout << name << ": " << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting")) << '\n'; }
};
int main()
{
    TicketOffice bus1(2), bus2(2);
    BusTicket a("Asha", bus1), b("Bala", bus1), c("Chitra", bus1);
    BusTicket d("Dev", bus2), e("Esha", bus2);
    a.print(); b.print(); c.print(); d.print(); e.print();
    std::cout << "Bus1 issued: " << bus1.count() << ", Bus2 issued: " << bus2.count() << '\n';
}
