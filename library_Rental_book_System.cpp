#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

// Structure to hold book information
struct Book {
    string title;
    string ISBN;
    double rentPerDay; // Fee per day for renting the book
    bool isAvailable; // Indicates if the book is available for rent
};

// Structure to hold borrow record
struct BorrowRecord {
    string customerName;
    string customerPhone;
    string ISBN;
    int borrowDays;
    double totalAmount; // Total fee for the borrowing
};

// Vectors to hold the books and borrow records
vector<Book> books;
vector<BorrowRecord> borrowRecords;

// File names to save/load the data
const string bookFile = "books.csv";
const string borrowFile = "borrow_records.csv";

// Function to split strings based on a delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Save the books data to the file
void saveBooks() {
    ofstream file(bookFile);
    for (const auto& book : books) {
        file << book.title << "," << book.ISBN << "," << book.rentPerDay << "," << book.isAvailable << endl;
    }
    file.close();
}

// Load the books data from the file
void loadBooks() {
    ifstream file(bookFile);
    string line;
    books.clear();
    while (getline(file, line)) {
        vector<string> data = split(line, ',');
        if (data.size() == 4) {
            try {
                Book book;
                book.title = data[0];
                book.ISBN = data[1];
                book.rentPerDay = stod(data[2]);
                book.isAvailable = (data[3] == "1");
                books.push_back(book);
            } catch (...) {
                cerr << "Skipping invalid book data line: " << line << endl;
            }
        }
    }
    file.close();
}

// Save the borrow records to the file
void saveBorrowRecords() {
    ofstream file(borrowFile);
    for (const auto& record : borrowRecords) {
        file << record.customerName << "," << record.customerPhone << "," << record.ISBN << ","
             << record.borrowDays << "," << record.totalAmount << endl;
    }
    file.close();
}

// Load the borrow records from the file
void loadBorrowRecords() {
    ifstream file(borrowFile);
    string line;
    borrowRecords.clear();
    while (getline(file, line)) {
        vector<string> data = split(line, ',');
        if (data.size() == 5) {
            try {
                BorrowRecord record;
                record.customerName = data[0];
                record.customerPhone = data[1];
                record.ISBN = data[2];
                record.borrowDays = stoi(data[3]);
                record.totalAmount = stod(data[4]);
                borrowRecords.push_back(record);
            } catch (...) {
                cerr << "Skipping invalid borrow record data line: " << line << endl;
            }
        }
    }
    file.close();
}

// Function to add a new book to the library
void addBook() {
    Book book;
    cout << "Enter book title: ";
    cin.ignore(); getline(cin, book.title);
    cout << "Enter ISBN: ";
    getline(cin, book.ISBN);
    cout << "Enter rent per day: ";
    cin >> book.rentPerDay;
    book.isAvailable = true; // Book is available by default
    books.push_back(book);
    saveBooks(); // Save the updated books list
    cout << "Book added successfully!\n\n";
}

// Function to borrow a book from the library
void borrowBook() {
    string isbn;
    cout << "Enter ISBN of the book to borrow: ";
    cin >> isbn;
    for (auto& book : books) {
        if (book.ISBN == isbn && book.isAvailable) {
            BorrowRecord record;
            cin.ignore();
            cout << "Enter your name: "; getline(cin, record.customerName);
            cout << "Enter phone: "; getline(cin, record.customerPhone);
            cout << "Enter number of borrow days: "; cin >> record.borrowDays;
            record.ISBN = isbn;
            record.totalAmount = record.borrowDays * book.rentPerDay; // Calculate total fee
            book.isAvailable = false; // Mark the book as borrowed
            borrowRecords.push_back(record);
            saveBooks(); saveBorrowRecords(); // Save updated data
            cout << "\nBook borrowed successfully to " << record.customerName << " for " << record.borrowDays << " days.\n\n";
            return;
        }
    }
    cout << "\nBook not available or doesn't exist.\n\n";
}

// Function to calculate late fees if a book is returned after the due date
double calculateLateFee(int overdueDays) {
    const double lateFeePerDay = 1.0; // $1 per overdue day
    return overdueDays * lateFeePerDay;
}

// Function to return a book to the library
void returnBook() {
    string name;
    cout << "Enter name of customer returning book: ";
    cin.ignore(); getline(cin, name);

    for (size_t i = 0; i < borrowRecords.size(); ++i) {
        if (borrowRecords[i].customerName == name) {
            int overdueDays = 5; // Example: Calculate overdue days (this can be dynamic)
            double lateFee = calculateLateFee(overdueDays); // Calculate late fee

            for (auto& book : books) {
                if (book.ISBN == borrowRecords[i].ISBN) {
                    book.isAvailable = true; // Book is returned, mark it available
                    break;
                }
            }
            borrowRecords.erase(borrowRecords.begin() + i); // Remove the borrow record
            saveBooks(); saveBorrowRecords(); // Save the updated data
            cout << "\nBook returned successfully. Late fee: $" << lateFee << "\n\n";
            return;
        }
    }
    cout << "\nNo borrow record found for this name.\n\n";
}

// Function to display the available books
void displayBooks() {
    cout << left << setw(20) << "Title" << setw(15) << "ISBN" << setw(15) << "Rent/Day" << "Status" << endl;
    cout << string(60, '-') << endl;
    for (const auto& book : books) {
        cout << left << setw(20) << book.title << setw(15) << book.ISBN << setw(15) << book.rentPerDay
             << (book.isAvailable ? "Available" : "Rented") << endl;
    }
    cout << endl;
}

// Function to display the borrowed books and their records
void displayBorrowedBooks() {
    cout << "\nList of Borrowed Books\n";
    cout << "---------------------------------------------------------------\n";
    cout << left << setw(15) << "Name"
         << setw(15) << "Phone"
         << setw(15) << "Book Title"
         << setw(12) << "ISBN"
         << setw(8)  << "Days"
         << setw(10) << "Total($)" << endl;
    cout << "---------------------------------------------------------------\n";

    for (const auto& record : borrowRecords) {
        for (const auto& book : books) {
            if (book.ISBN == record.ISBN) {
                cout << left << setw(15) << record.customerName
                     << setw(15) << record.customerPhone
                     << setw(15) << book.title
                     << setw(12) << record.ISBN
                     << setw(8)  << record.borrowDays
                     << "$" << setw(9) << record.totalAmount << endl;
            }
        }
    }
    cout << "---------------------------------------------------------------\n\n";
}

// Menu to interact with the system
void menu() {
    int choice;
    do {
        cout << "========== Library Management System ==========" << endl;
        cout << "1. Add New Book" << endl;
        cout << "2. Display Books" << endl;
        cout << "3. Borrow a Book" << endl;
        cout << "4. Return a Book" << endl;
        cout << "5. View Borrowed Books\n";
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;
        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: borrowBook(); break;
            case 4: returnBook(); break;
            case 5: displayBorrowedBooks(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice, please try again.\n"; break;
        }
    } while (choice != 0);
}

// Main function
int main() {
    loadBooks();  // Load book data from file
    loadBorrowRecords();  // Load borrow records from file
    menu();  // Start the menu system
    return 0;
}

