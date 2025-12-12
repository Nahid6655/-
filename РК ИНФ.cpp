#include <iostream>
#include <string>

using namespace std;

// Базовый класс
class BankAccount {
protected:
    int accountNumber;
    string ownerName;
    double balance;

public:
    BankAccount(int accNum, const string& owner, double bal = 0.0)
        : accountNumber(accNum), ownerName(owner), balance(bal) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. New balance: " << balance << endl;
        } else {
            cout << "Invalid deposit amount.\n";
        }
    }

    void withdraw(double amount) {
        if (amount <= balance && amount > 0) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: " << balance << endl;
        } else {
            cout << "Insufficient funds or invalid amount.\n";
        }
    }

    void display() const {
        cout << "Account Number: " << accountNumber
             << "\nOwner: " << ownerName
             << "\nBalance: " << balance << "\n";
    }
};

// Производный класс
class SavingsAccount : public BankAccount {
private:
    double interestRate; // в процентах, например 5 означает 5%

public:
    SavingsAccount(int accNum, const string& owner, double bal, double rate)
        : BankAccount(accNum, owner, bal), interestRate(rate) {}

    void applyInterest() {
        double interest = balance * (interestRate / 100);
        balance += interest;
        cout << "Interest applied: " << interest
             << "\nNew balance: " << balance << endl;
    }
};

int main() {
    // Создание обычного банковского счёта
    BankAccount acc1(1001, "Ivan Petrov", 500.0);
    acc1.display();
    acc1.deposit(200.0);
    acc1.withdraw(150.0);

    cout << "\n";

    // Создание сберегательного счёта
    SavingsAccount sav1(2001, "Anna Ivanova", 1000.0, 5.0);
    sav1.display();
    sav1.deposit(500.0);
    sav1.applyInterest();
    sav1.withdraw(300.0);

    return 0;
}
