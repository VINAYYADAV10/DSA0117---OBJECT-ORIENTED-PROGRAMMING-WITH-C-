#include <iostream>
#include <deque>
#include <iomanip>

struct Transaction { char type; double amount; };
class SavingsAccount {
    static const std::size_t MAX = 10;
    int accNo; double balance; std::deque<Transaction> last;
    void record(char t, double a)
    {
        if (last.size() == MAX) last.pop_front();   // O(1)
        last.push_back({t, a});                     // O(1)
    }
public:
    SavingsAccount(int no, double op) : accNo(no), balance(op) {}
    void deposit(double a) { balance += a; record('D', a); }
    bool withdraw(double a) { if (a > balance) return false; balance -= a; record('W', a); return true; }
    void miniStatement() const
    {
        std::cout << "Mini-statement for account " << accNo << '\n';
        int i = 1;
        for (const auto& t : last)
            std::cout << std::setw(3) << i++ << ". " << (t.type == 'D' ? "Deposit   " : "Withdrawal")
                      << std::setw(9) << t.amount << '\n';
        std::cout << "Balance: " << balance << '\n';
    }
};
int main()
{
    SavingsAccount acc(1001, 5000);
    for (int i = 1; i <= 8; ++i) acc.deposit(i * 100);
    acc.withdraw(250); acc.withdraw(300); acc.deposit(1000);
    acc.withdraw(50);
    acc.miniStatement();
}
