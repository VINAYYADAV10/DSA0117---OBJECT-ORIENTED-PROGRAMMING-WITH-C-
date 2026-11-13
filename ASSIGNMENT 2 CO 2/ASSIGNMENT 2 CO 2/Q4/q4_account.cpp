#include <iostream>
#include <iomanip>

struct Transaction { char type; double amount; };   // 'D' deposit, 'W' withdrawal

class SavingsAccount {
    static const int MAX = 10;        // change to 50 for the 50-transaction requirement
    int         accNo;
    double      balance;
    Transaction last[MAX];            // private: only the class keeps it consistent
    int         count;                // number of valid transactions (0..MAX)

    void record(char t, double amt)   // defined inside the class (implicitly inline)
    {
        if (count == MAX) {           // 11th transaction: shift left, discard the oldest
            for (int i = 1; i < MAX; ++i) last[i - 1] = last[i];
            --count;
        }
        last[count].type = t;
        last[count].amount = amt;
        ++count;
    }
public:
    SavingsAccount(int no, double opening) : accNo(no), balance(opening), count(0) {}
    void   deposit(double amt) { balance += amt; record('D', amt); }   // inside
    bool   withdraw(double amt);                                       // outside
    void   miniStatement() const;                                      // outside
    double getBalance() const { return balance; }
};

bool SavingsAccount::withdraw(double amt)
{
    if (amt > balance) return false;           // insufficient funds: nothing recorded
    balance -= amt;
    record('W', amt);
    return true;
}
void SavingsAccount::miniStatement() const
{
    std::cout << "Mini-statement for account " << accNo << '\n';
    for (int i = 0; i < count; ++i)
        std::cout << std::setw(3) << i + 1 << ". "
                  << (last[i].type == 'D' ? "Deposit   " : "Withdrawal")
                  << std::setw(9) << last[i].amount << '\n';
    std::cout << "Balance: " << balance << '\n';
}

int main()
{
    SavingsAccount acc(1001, 5000);
    for (int i = 1; i <= 8; ++i) acc.deposit(i * 100);   // 100 .. 800
    acc.withdraw(250);
    acc.withdraw(300);
    acc.deposit(1000);
    if (!acc.withdraw(100000)) std::cout << "Withdrawal of 100000 refused\n";
    acc.withdraw(50);                                     // 12th accepted transaction
    acc.miniStatement();                                  // only the last 10 are shown
}
