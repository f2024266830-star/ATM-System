#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Transaction
{
    string info;
    Transaction* next;
};

class Stack
{
    Transaction* top;
public:
    Stack() { top = NULL; }

    void push(string s)
    {
        Transaction* t = new Transaction;
        t->info = s;
        t->next = top;
        top = t;
    }

    void display()
    {
        Transaction* temp = top;
        if (!temp)
        {
            cout << "No Transactions\n";
            return;
        }
        while (temp)
        {
            cout << temp->info << endl;
            temp = temp->next;
        }
    }
};

struct Account
{
    int accNo;
    int pin;
    double balance;
    Account* next;
};

class ATM
{
    Account* head;
    Stack history;

    string convert(double amt)
    {
        stringstream ss;
        ss << amt;
        return ss.str();
    }

public:
    ATM() { head = NULL; }

    void addAccount(int accNo, int pin, double balance)
    {
        Account* a = new Account;
        a->accNo = accNo;
        a->pin = pin;
        a->balance = balance;
        a->next = head;
        head = a;
    }

    Account* authenticate(int accNo, int pin)
    {
        Account* temp = head;
        while (temp)
        {
            if (temp->accNo == accNo && temp->pin == pin)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }

    void deposit(Account* acc, double amt)
    {
        acc->balance += amt;
        history.push("Deposited: " + convert(amt));
    }

    void withdraw(Account* acc, double amt)
    {
        if (acc->balance >= amt)
        {
            acc->balance -= amt;
            history.push("Withdrawn: " + convert(amt));
        }
        else
        {
            cout << "Insufficient Balance\n";
        }
    }

    void checkBalance(Account* acc)
    {
        cout << "Balance: " << acc->balance << endl;
        history.push("Balance Checked");
    }

    void showHistory()
    {
        history.display();
    }
};

int main()
{
    ATM atm;
    atm.addAccount(101, 1234, 5000);
    atm.addAccount(102, 4321, 8000);

    int accNo, pin;
    cout << "Enter Account Number: ";
    cin >> accNo;
    cout << "Enter PIN: ";
    cin >> pin;

    Account* user = atm.authenticate(accNo, pin);

    if (user == NULL)
    {
        cout << "Invalid Credentials\n";
        return 0;
    }

    int choice;
    double amount;

    do
    {
        cout << "\n1.Deposit\n2.Withdraw\n3.Check Balance\n4.Transaction History\n5.Exit\n";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter Amount: ";
            cin >> amount;
            atm.deposit(user, amount);
        }
        else if (choice == 2)
        {
            cout << "Enter Amount: ";
            cin >> amount;
            atm.withdraw(user, amount);
        }
        else if (choice == 3)
        {
            atm.checkBalance(user);
        }
        else if (choice == 4)
        {
            atm.showHistory();
        }

    } while (choice != 5);

    return 0;
}

