#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class BankAccount {
private:
    string name;
    int accountNum;
    double balance;

public:
    BankAccount(string n, int ac, double bal) : name(n), accountNum(ac), balance(bal) {}

    string getName() const { return name; }
    int getAccountNum() const { return accountNum; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "\t\tWithdraw Successfully..." << endl;
        } else {
            cout << "\t\tInsufficient Balance...." << endl;
        }
    }

    string toCSV() const {
        return name + "," + to_string(accountNum) + "," + to_string(balance);
    }
};

class BankManagement {
private:
    vector<BankAccount> accounts;

    void loadFromFile() {
        ifstream file("bank.csv");
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, accountNumStr, balanceStr;
            getline(ss, name, ',');
            getline(ss, accountNumStr, ',');
            getline(ss, balanceStr, ',');
            if (!name.empty() && !accountNumStr.empty() && !balanceStr.empty()) {
                int accNum = stoi(accountNumStr);
                double bal = stod(balanceStr);
                accounts.push_back(BankAccount(name, accNum, bal));
            }
        }
        file.close();
    }

    void saveToFile() {
        ofstream file("bank.csv");
        for (const auto& acc : accounts) {
            file << acc.toCSV() << endl;
        }
        file.close();
    }

public:
    BankManagement() {
        loadFromFile();
    }

    ~BankManagement() {
        saveToFile();
    }

    void AddAccount(string name, int accountNum, double balance) {
        accounts.push_back(BankAccount(name, accountNum, balance));
        saveToFile();
    }

    void showAllAccounts() {
        cout << "\t\tAll Account Holders\n";
        for (const auto& acc : accounts) {
            cout << "Name: " << acc.getName() << " Account Number: " << acc.getAccountNum() << " Balance: " << acc.getBalance() << endl;
        }
    }

    void searchAccount(int account) {
        cout << "\t\tAccount Holder\n";
        bool found = false;
        for (const auto& acc : accounts) {
            if (acc.getAccountNum() == account) {
                cout << "Name: " << acc.getName() << " Account Number: " << acc.getAccountNum() << " Balance: " << acc.getBalance() << endl;
                found = true;
            }
        }
        if (!found) cout << "\t\tAccount not found..." << endl;
    }

    BankAccount* findAccount(int accountNum) {
        for (auto& acc : accounts) {
            if (acc.getAccountNum() == accountNum) {
                return &acc;
            }
        }
        return nullptr;
    }

    void updateFile() {
        saveToFile();
    }
};

int main() {
    BankManagement bank;
    int choice;
    char op;

    do {
        system("cls");
        cout << "\t\t::Bank Management System\n";
        cout << "\t\t\tMain Menu\n";
        cout << "\t\t1. Create New Account\n";
        cout << "\t\t2. Show All Accounts\n";
        cout << "\t\t3. Search Account\n";
        cout << "\t\t4. Deposit Money\n";
        cout << "\t\t5. Withdraw Money\n";
        cout << "\t\t6. Exit\n";
        cout << "\t\t-------------------------------\n";
        cout << "\t\tEnter Your Choice : ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            int accountNum;
            double balance;
            cout << "\t\tEnter Name : ";
            cin >> name;
            cout << "\t\tEnter Account Number : ";
            cin >> accountNum;
            cout << "\t\tEnter Initial Balance : ";
            cin >> balance;
            bank.AddAccount(name, accountNum, balance);
            cout << "\t\tAccount Created Successfully...." << endl;
            break;
        }
        case 2:
            bank.showAllAccounts();
            break;
        case 3: {
            int accountNum;
            cout << "Enter Account Number : ";
            cin >> accountNum;
            bank.searchAccount(accountNum);
            break;
        }
        case 4: {
            int accountNum;
            double amount;
            cout << "\t\tEnter Account Number to Deposit Money : ";
            cin >> accountNum;
            BankAccount* account = bank.findAccount(accountNum);
            if (account) {
                cout << "\t\tEnter Amount to Deposit : ";
                cin >> amount;
                account->deposit(amount);
                cout << "\t\t" << amount << " Deposited Successfully ...." << endl;
                bank.updateFile();
            } else {
                cout << "\t\tAccount Not Found ..." << endl;
            }
            break;
        }
        case 5: {
            int accountNum;
            double amount;
            cout << "\t\tEnter Account Number to Withdraw Money : ";
            cin >> accountNum;
            BankAccount* account = bank.findAccount(accountNum);
            if (account) {
                cout << "\t\tEnter Amount to Withdraw : ";
                cin >> amount;
                account->withdraw(amount);
                bank.updateFile();
            } else {
                cout << "\t\tAccount Not Found ..." << endl;
            }
            break;
        }
        case 6:
            exit(0);
        }

        cout << "\t\tDo You Want to Continue? [Y/N]: ";
        cin >> op;

    } while (op == 'y' || op == 'Y');

    return 0;
}

