#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h> // for Sleep() and system("cls")
using namespace std;

// Define a class to represent a billable item
class Bill {
private:
    string Item;
    int Rate, Quantity;
public:
    // Default constructor
    Bill(): Item(""), Rate(0), Quantity(0) {}

    // Setter functions
    void setItem(string item) { Item = item; }
    void setRate(int rate) { Rate = rate; }
    void setQuant(int quant) { Quantity = quant; }

    // Getter functions
    string getItem() { return Item; }
    int getRate() { return Rate; }
    int getQuant() { return Quantity; }
};

// Function to add a new item to the inventory
void addItem(Bill b) {
    bool close = false;
    while (!close) {
        int choice;
        cout << "\t1. Add Item" << endl;
        cout << "\t2. Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls"); // Clear the screen
            string item;
            int rate, quant;

            // Take item details from user
            cout << "\tEnter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate Of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity Of Item: ";
            cin >> quant;
            b.setQuant(quant);

            // Save the item to the file
            ofstream out("bill_system.txt", ios::app); // Append mode
            if (!out) {
                cout << "\tError: File Can't Open!" << endl;
            } else {
                out << b.getItem() << " : " << b.getRate() << " : " << b.getQuant() << endl;
            }
            out.close();

            cout << "\tItem Added Successfully" << endl;
            Sleep(3000); // Pause for 3 seconds
        }

        else if (choice == 2) {
            system("cls");
            close = true;
            cout << "\tBack To Main Menu!" << endl;
            Sleep(3000);
        }
    }
}

// Function to handle billing (customer purchase)
void printBill() {
    system("cls");
    int count = 0; // Total cost
    bool close = false;

    while (!close) {
        system("cls");
        int choice;
        cout << "\t1. Add to Bill" << endl;
        cout << "\t2. Close Session" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            string item;
            int quant;
            cout << "\tEnter Item Name: ";
            cin >> item;
            cout << "\tEnter Quantity: ";
            cin >> quant;

            // Open current inventory
            ifstream in("bill_system.txt");
            ofstream out("bill_temp.txt"); // Temporary file for updated inventory

            string line;
            bool found = false;

            // Read all items from inventory
            while (getline(in, line)) {
                stringstream ss(line);
                string itemName;
                int itemRate, itemQuant;
                char delimiter;
                ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

                if (item == itemName) {
                    found = true;
                    if (quant <= itemQuant) {
                        int amount = itemRate * quant;
                        cout << "\n\tItem | Rate | Quantity | Amount" << endl;
                        cout << "\t" << itemName << "\t" << itemRate << "\t" << quant << "\t" << amount << endl;

                        // Update inventory quantity
                        int newQuant = itemQuant - quant;
                        count += amount;

                        // Write updated item to temp file
                        out << itemName << " : " << itemRate << " : " << newQuant << endl;
                    } else {
                        cout << "\tSorry, not enough quantity for " << item << "!" << endl;
                        // Still keep the original quantity
                        out << itemName << " : " << itemRate << " : " << itemQuant << endl;
                    }
                } else {
                    // Keep unchanged items
                    out << line << endl;
                }
            }

            if (!found) {
                cout << "\tItem Not Available!" << endl;
            }

            in.close();
            out.close();

            // Replace original file with updated file
            remove("bill_system.txt");
            rename("bill_temp.txt", "bill_system.txt");
        }

        else if (choice == 2) {
            close = true;
            cout << "\tCounting Total Bill..." << endl;
        }

        Sleep(3000);
    }

    // Final summary
    system("cls");
    cout << "\n\n";
    cout << "\tTotal Bill ----------------- : " << count << endl << endl;
    cout << "\tThanks For Shopping!" << endl;
    Sleep(5000);
}

// Function to display all available items
void viewAvailableItems() {
    system("cls");
    ifstream in("bill_system.txt");
    string line;

    cout << "\tAvailable Items in the Market\n";
    cout << "\t-----------------------------\n";
    cout << "\tItem\t\tRate\tQuantity\n";

    // Read each line and print the item
    while (getline(in, line)) {
        stringstream ss(line);
        string itemName;
        int rate, quant;
        char delimiter;
        ss >> itemName >> delimiter >> rate >> delimiter >> quant;
        cout << "\t" << itemName << "\t\t" << rate << "\t" << quant << endl;
    }

    in.close();
    cout << "\n\tPress any key to return to the main menu...";
    cin.ignore();
    cin.get(); // Wait for user to press a key
}

// Main function: Entry point of the application
int main() {
    Bill b;
    bool exit = false;

    // Main menu loop
    while (!exit) {
        system("cls");
        int val;

        cout << "\tWelcome To Super Market Billing System" << endl;
        cout << "\t**************************************" << endl;
        cout << "\t\t1. Add Item to Inventory" << endl;
        cout << "\t\t2. Print Bill (Customer Purchase)" << endl;
        cout << "\t\t3. View Available Items" << endl;
        cout << "\t\t4. Exit" << endl;
        cout << "\t\tEnter Choice: ";
        cin >> val;

        if (val == 1) {
            system("cls");
            addItem(b);
            Sleep(3000);
        }

        else if (val == 2) {
            printBill();
        }

        else if (val == 3) {
            viewAvailableItems();
        }

        else if (val == 4) {
            system("cls");
            exit = true;
            cout << "\tGood Luck!" << endl;
            Sleep(3000);
        }
    }
}



//1. Classes and Objects
//Class: A blueprint for creating objects.
//
//Object: An instance of a class.
//
//Your class Bill has:
//
//Private members: Item, Rate, Quantity
//
//Public methods: setItem(), getRate(), etc.
//
//? 2. Functions
//Functions are blocks of reusable code.
//
//Examples: addItem(), printBill(), viewAvailableItems(), and main().
//
//? 3. File Handling
//Used to read/write data to files.
//
//ifstream – read from file
//
//ofstream – write to file
//
//remove() and rename() – update file content
//
//? 4. String and StringStream
//stringstream helps parse strings from file lines.
//
//? 5. Control Structures
//if, else, while, switch, etc., are used for logic and user choices.
//
//? 6. Input/Output
//cin to take user input.
//
//cout to display output.
//
//? 7. System Commands
//system("cls"): clears screen.
//
//Sleep(milliseconds): pauses execution.
