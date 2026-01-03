#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

/* ---------------- BANK ---------------- */
class bank_name {
public:
    void display_bank_name() {
        cout << setw(50) << "ABC BANK" << endl;
        cout << string(110, '-') << endl;
    }
};

/* ---------------- PASSWORD ---------------- */
class password {
public:
    void get_password() {
        string pass;
        while (true) {
            cout << "Enter Your Password: ";
            cin >> pass;

            if (pass == "abc@123") {
                cout << "Password Verified Successfully.\n\n";
                break;
            } else {
                cout << "Incorrect Password. Try again.\n\n";
            }
        }
    }
};

/* ---------------- ACCOUNT ---------------- */
class account {
public:
    int account_no;
    string customer_name, address, email;
    long long phone_no;
    double balance;

    bool validEmail(string e) {
        return (e.find('@') != string::npos && e.find('.') != string::npos);
    }

    bool validPhone(long long p) {
        int count = 0;
        while (p != 0) {
            count++;
            p /= 10;
        }
        return count == 10;
    }

    int get_account_details() {
        cout << "Enter Account Number: ";
        cin >> account_no;

        cout << "Enter Customer Name: ";
        cin.ignore();
        getline(cin, customer_name);

        cout << "Enter Address: ";
        getline(cin, address);

        // Phone validation
        while (true) {
            cout << "Enter Phone Number (10 digits): ";
            cin >> phone_no;

            if (validPhone(phone_no))
                break;
            else
                cout << "Invalid Mobile Number! Must be 10 digits.\n";
        }

        // Email validation
        while (true) {
            cout << "Enter Email Address: ";
            cin >> email;

            if (validEmail(email))
                break;
            else
                cout << "Invalid Email! Must contain '@' and '.'\n";
        }

        cout << "Enter Initial Balance: ";
        cin >> balance;

        return account_no;
    }

    void display_account_details() {
        cout << fixed << setprecision(0);
        cout << setw(40) << "NAME = " << customer_name << endl;
        cout << setw(40) << "ACCOUNT NO = " << account_no << endl;
        cout << setw(40) << "ADDRESS = " << address << endl;
        cout << setw(40) << "PHONE = " << phone_no << endl;
        cout << setw(40) << "EMAIL = " << email << endl;
        cout << setw(40) << "BALANCE = " << balance << endl << endl;
    }
};

/* ---------------- TRANSACTION ---------------- */
class transaction {
public:
    void start(account &acc, string type, int duration) {

        if (type == "Fixed" && duration < 5) {
            cout << "\nFixed Account Restriction: Transactions not allowed before 5 years.\n";
            return;
        }

        int choice;
        double amount;

        do {
            cout << "\n--- TRANSACTION MENU ---\n";
            cout << "1. Deposit\n2. Withdraw\n3. Transfer\n4. View Account\n0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Deposit Amount: ";
                cin >> amount;
                acc.balance += amount;
                cout << "Deposit Successful.\n";
                break;

            case 2:
                cout << "Withdrawal Amount: ";
                cin >> amount;
                if (amount <= acc.balance) {
                    acc.balance -= amount;
                    cout << "Withdrawal Successful.\n";
                } else {
                    cout << "Insufficient Balance.\n";
                }
                break;

            case 3:
                cout << "Transfer Amount: ";
                cin >> amount;
                if (amount <= acc.balance) {
                    int receiver;
                    cout << "Receiver Account Number: ";
                    cin >> receiver;
                    acc.balance -= amount;
                    cout << "Transfer Successful.\n";
                } else {
                    cout << "Insufficient Balance.\n";
                }
                break;

            case 4:
                acc.display_account_details();
                break;

            case 0:
                cout << "Transaction session ended.\n";
                break;

            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }
};

/* ---------------- LOAN ---------------- */
class loan {
public:
    double loan_amount = 0;
    double interest_rate = 0;
    int duration_years = 0;
    bool active = false;

    void apply(account &acc) {
        string type;

        cout << "Loan Type (Personal/Home/Business): ";
        cin >> type;

        cout << "Loan Amount: ";
        cin >> loan_amount;

        cout << "Duration (Years): ";
        cin >> duration_years;

        if (type == "Personal") interest_rate = 10;
        else if (type == "Home") interest_rate = 5;
        else interest_rate = 12;

        acc.balance += loan_amount;
        active = true;

        cout << "\n--- LOAN APPROVED ---\n";
        cout << "Loan Amount Credited: " << loan_amount << endl;
        cout << "Interest Rate: " << interest_rate << "%\n";
        cout << "Duration: " << duration_years << " Years\n";
        cout << "Updated Balance: " << acc.balance << endl;
    }

    void repay(account &acc) {
        if (!active) {
            cout << "No active loan found.\n";
            return;
        }

        double interest = (loan_amount * interest_rate * duration_years) / 100;
        double total = loan_amount + interest;

        cout << "\n--- LOAN REPAYMENT ---\n";
        cout << "Total Payable: " << total << endl;

        if (acc.balance >= total) {
            acc.balance -= total;
            cout << "Loan Repaid Successfully.\n";
            active = false;
        } else {
            cout << "Insufficient balance to repay loan.\n";
            acc.balance -= loan_amount;
        }
    }
};

/* ---------------- MAIN ---------------- */
int main() {
    bank_name bank;
    password pass;
    account acc;
    transaction txn;
    loan ln;

    bank.display_bank_name();
    pass.get_password();

    acc.get_account_details();
    bank.display_bank_name();
    acc.display_account_details();

    string choice;
    cout << "Do you want to perform transactions? (Yes/No): ";
    cin >> choice;

    if (choice == "Yes" || choice == "yes") {
        string type;
        int duration;
        cout << "Account Type (Saving/Current/Fixed): ";
        cin >> type;
        cout << "Account Duration (Years): ";
        cin >> duration;
        txn.start(acc, type, duration);
    }

    cout << "\nDo you want to apply for loan? (Yes/No): ";
    cin >> choice;

    if (choice == "Yes" || choice == "yes") {
        ln.apply(acc);
    }

    cout << "\nDo you want to repay loan now? (Yes/No): ";
    cin >> choice;

    if (choice == "Yes" || choice == "yes") {
        ln.repay(acc);
    }

    cout << "\n--- FINAL ACCOUNT STATUS ---\n";
    acc.display_account_details();
    cout << "Thank you for using ABC BANK.\n";

    return 0;
}
