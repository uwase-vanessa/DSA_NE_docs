#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Student structure
struct Student {
    int roll;
    string name;
    double balance;
};

// Book structure
struct Book {
    string title;
    string author;
    int isbn;
    bool available;
};

// Global variables
Student students[20];
Book books[15];
int student_count = 0;
int book_count = 0;

// Function prototypes
void create_account();
void display_student(int roll);
void deposit_amount(int roll, double amount);
void issue_book(int roll);
void display_all_students();
int find_student(int roll);
int find_book(int isbn);
void add_book();
void edit_book();
void view_books();

int main() {
    // Initialization
   // Add initial 15 books to the library
    for (int i = 0; i < 15; i++) {
        books[i] = {"Book " + to_string(i+1), "Author " + to_string(i+1), 1000+i, true};
    }
    book_count = 15;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Admin Login\n";
        cout << "2. Student Login\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
        
        int option;
        cin >> option;
        
        if (option == 0) break;
        
        if (option == 1 || option == 2) {
            cout << "Enter password: ";
            string password;
            cin >> password;
            
            if (password != "password") {
                cout << "Incorrect password!\n";
                continue;
            }
            
            if (option == 1) { // Admin menu
                cout << "\nAdmin Menu\n";
                cout << "1. Add Book\n";
                cout << "2. Edit Book\n";
                cout << "3. View Books\n";
                cout << "4. View All Students\n";
                cout << "5. View Student Details\n";
                cout << "Choose option: ";
                
                cin >> option;
                switch(option) {
                    case 1: add_book(); break;
                    case 2: edit_book(); break;
                    case 3: view_books(); break;
                    case 4: display_all_students(); break;
                    case 5: {
                        int roll;
                        cout << "Enter roll number: ";
                        cin >> roll;
                        display_student(roll);
                        break;
                    }
                }
            } 
            else { // Student menu
                int roll;
                cout << "Enter roll number: ";
                cin >> roll;
                
                int index = find_student(roll);
                if (index == -1) {
                    cout << "Account not found. Create new account? (1=Yes, 0=No): ";
                    cin >> option;
                    if (option == 1) create_account();
                } 
                else {
                    cout << "\nStudent Menu\n";
                    cout << "1. View Details\n";
                    cout << "2. Deposit Amount\n";
                    cout << "3. Issue Book\n";
                    cout << "Choose option: ";
                    
                    cin >> option;
                    switch(option) {
                        case 1: display_student(roll); break;
                        case 2: {
                            double amount;
                            cout << "Enter amount: $";
                            cin >> amount;
                            deposit_amount(roll, amount);
                            break;
                        }
                        case 3: issue_book(roll); break;
                    }
                }
            }
        }
    }
    return 0;
}

void create_account() {
    if (student_count >= 20) {
        cout << "Maximum students reached!\n";
        return;
    }
    
    Student s;
    cout << "Enter roll number: ";
    cin >> s.roll;
    
    if (find_student(s.roll) {
        cout << "Account already exists!\n";
        return;
    }
    
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, s.name);
    
    double deposit;
    cout << "Enter initial deposit (minimum $50): $";
    cin >> deposit;
    
    if (deposit < 50) {
        cout << "Deposit too low!\n";
        return;
    }
    
    s.balance = deposit - 50; // $50 security deposit
    students[student_count++] = s;
    cout << "Account created successfully!\n";
}

void display_student(int roll) {
    int index = find_student(roll);
    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }
    
    cout << "\nStudent Details\n";
    cout << "Roll: " << students[index].roll << endl;
    cout << "Name: " << students[index].name << endl;
    cout << fixed << setprecision(2);
    cout << "Balance: $" << students[index].balance << endl;
}

void deposit_amount(int roll, double amount) {
    int index = find_student(roll);
    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }
    
    students[index].balance += amount;
    cout << "New balance: $" << students[index].balance << endl;
}

void issue_book(int roll) {
    int student_index = find_student(roll);
    if (student_index == -1) {
        cout << "Student not found!\n";
        return;
    }
    
    if (students[student_index].balance < 2) {
        cout << "Insufficient balance ($2 required)!\n";
        return;
    }
    
    cout << "\nAvailable Books:\n";
    for (int i = 0; i < book_count; i++) {
        if (books[i].available) {
            cout << i+1 << ". " << books[i].title << " by " << books[i].author 
                 << " (ISBN: " << books[i].isbn << ")\n";
        }
    }
    
    cout << "Enter book number (0 to cancel): ";
    int choice;
    cin >> choice;
    
    if (choice == 0) return;
    if (choice < 1 || choice > book_count || !books[choice-1].available) {
        cout << "Invalid selection!\n";
        return;
    }
    
    books[choice-1].available = false;
    students[student_index].balance -= 2;
    cout << "Book issued! New balance: $" << students[student_index].balance << endl;
}

void display_all_students() {
    // Simple bubble sort by roll number
    for (int i = 0; i < student_count; i++) {
        for (int j = i+1; j < student_count; j++) {
            if (students[i].roll > students[j].roll) {
                swap(students[i], students[j]);
            }
        }
    }
    
    cout << "\nAll Students (" << student_count << ")\n";
    for (int i = 0; i < student_count; i++) {
        cout << students[i].roll << " - " << students[i].name 
             << " - Balance: $" << fixed << setprecision(2) << students[i].balance << endl;
    }
}

int find_student(int roll) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].roll == roll) return i;
    }
    return -1;
}

int find_book(int isbn) {
    for (int i = 0; i < book_count; i++) {
        if (books[i].isbn == isbn) return i;
    }
    return -1;
}

void add_book() {
    if (book_count >= 15) {
        cout << "Maximum books reached!\n";
        return;
    }
    
    Book b;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, b.title);
    
    cout << "Enter author: ";
    getline(cin, b.author);
    
    cout << "Enter ISBN: ";
    cin >> b.isbn;
    
    if (find_book(b.isbn) != -1) {
        cout << "Book already exists!\n";
        return;
    }
    
    b.available = true;
    books[book_count++] = b;
    cout << "Book added successfully!\n";
}

void edit_book() {
    int isbn;
    cout << "Enter ISBN of book to edit: ";
    cin >> isbn;
    
    int index = find_book(isbn);
    if (index == -1) {
        cout << "Book not found!\n";
        return;
    }
    
    cout << "Current title: " << books[index].title << endl;
    cout << "Enter new title: ";
    cin.ignore();
    getline(cin, books[index].title);
    
    cout << "Current author: " << books[index].author << endl;
    cout << "Enter new author: ";
    getline(cin, books[index].author);
    
    cout << "Book updated successfully!\n";
}

void view_books() {
    cout << "\nAll Books (" << book_count << ")\n";
    for (int i = 0; i < book_count; i++) {
        cout << "Title: " << books[i].title << endl;
        cout << "Author: " << books[i].author << endl;
        cout << "ISBN: " << books[i].isbn << endl;
        cout << "Available: " << (books[i].available ? "Yes" : "No") << endl << endl;
    }
}