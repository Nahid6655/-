#include <iostream>
#include <string>
using namespace std;

// ================================
// Класс BankAccount
// ================================
class BankAccount {
protected:
    int accountNumber;
    string ownerName;
    double balance;

public:
    // Конструктор
    BankAccount(int number, const string& owner, double initialBalance = 0.0)
        : accountNumber(number), ownerName(owner), balance(initialBalance) {}

    // Метод пополнения
    void deposit(double amount) {
        balance += amount;
        cout << "Deposited " << amount << ". New balance: " << balance << endl;
    }

    // Метод снятия
    virtual void withdraw(double amount) {
        if (amount > balance) {
            cout << "Error: insufficient funds!\n";
        } else {
            balance -= amount;
            cout << "Withdrawn " << amount << ". New balance: " << balance << endl;
        }
    }

    // Показ баланса
    double getBalance() const {
        return balance;
    }
};

// ================================
// Класс SavingsAccount (наследник)
// ================================
class SavingsAccount : public BankAccount {
private:
    double interestRate; // процентная ставка

public:
    SavingsAccount(int number, const string& owner, double rate, double initialBalance = 0.0)
        : BankAccount(number, owner, initialBalance), interestRate(rate) {}

    // Метод начисления процентов
    void applyInterest() {
        double interest = balance * interestRate;
        balance += interest;
        cout << "Interest added: " << interest << ". New balance: " << balance << endl;
    }
};

// ================================
// main()
// ================================
int main() {
    cout << "===== BANK ACCOUNT DEMO =====\n\n";

    // Обычный банковский счет
    BankAccount acc1(101, "Ivan Ivanov", 500);
    cout << "Created BankAccount for Ivan Ivanov\n";
    acc1.deposit(200);
    acc1.withdraw(100);
    cout << endl;

    // Накопительный счёт
    SavingsAccount sav1(202, "Anna Smirnova", 0.05, 1000);
    cout << "Created SavingsAccount for Anna Smirnova\n";
    sav1.deposit(500);
    sav1.applyInterest();
    sav1.withdraw(300);

    return 0;
}
