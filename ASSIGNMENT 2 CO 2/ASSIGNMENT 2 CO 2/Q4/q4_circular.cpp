#include <iostream>
#include <iomanip>

struct Transaction { char type; double amount; };

class SavingsAccount {
    static const int MAX = 10;
    int         accNo;
    double      balance;
    Transaction last[MAX];
    int         start;                // index of the oldest transaction
    int         count;
    void record(char t, double amt)
    {
        int pos = (start + count) % MAX;     // next free slot (or the oldest when full)
        last[pos].type = t; last[pos].amount = amt;
        if (count == MAX) start = (start + 1) % MAX;   // overwrite oldest: O(1)
        else              ++count;
    }
public:
    SavingsAccount(int no, double opening) : accNo(no), balance(opening), start(0), count(0) {}
    void deposit(double amt) { balance += amt; record('D', amt); }
    bool withdraw(double amt);
    void miniStatement() const;
};
bool SavingsAccount::withdraw(double amt)
{
    if (amt > balance) return false;
    balance -= amt; record('W', amt); return true;
}
void SavingsAccount::miniStatement() const
{
    std::cout << "Mini-statement for account " << accNo << '\n';
    for (int i = 0; i < count; ++i) {
        const Transaction& t = last[(start + i) % MAX];
        std::cout << std::setw(3) << i + 1 << ". "
                  << (t.type == 'D' ? "Deposit   " : "Withdrawal")
                  << std::setw(9) << t.amount << '\n';
    }
    std::cout << "Balance: " << balance << '\n';
}
int main()
{
    SavingsAccount acc(1001, 5000);
    for (int i = 1; i <= 8; ++i) acc.deposit(i * 100);
    acc.withdraw(250); acc.withdraw(300); acc.deposit(1000);
    if (!acc.withdraw(100000)) std::cout << "Withdrawal of 100000 refused\n";
    acc.withdraw(50);
    acc.miniStatement();
}
