#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>

using namespace std;

// Structure for an inventory item
struct Item {
    int id;
    string name;
    int quantity;
    string reg_date;
    Item* next; // Pointer to next item
};

// Class to manage inventory using a linked list
class Inventory {
    Item* head; // Head of linked list
    string csv_file; // File for saving data

    // Load items from CSV file
    void loadFromCSV() {
        ifstream file(csv_file);
        string line;
        while (getline(file, line)) {
            vector<string> tokens;
            string token;
            for (char c : line) {
                if (c == ',') {
                    tokens.push_back(token);
                    token.clear();
                } else {
                    token += c;
                }
            }
            tokens.push_back(token); // Last token

            if (tokens.size() == 4) {
                Item* newItem = new Item;
                newItem->id = stoi(tokens[0]);
                newItem->name = tokens[1];
                newItem->quantity = stoi(tokens[2]);
                newItem->reg_date = tokens[3];
                newItem->next = nullptr;

                // Insert sorted by name
                if (!head || toLower(head->name) > toLower(newItem->name)) {
                    newItem->next = head;
                    head = newItem;
                } else {
                    Item* current = head;
                    while (current->next && toLower(current->next->name) < toLower(newItem->name))
                        current = current->next;
                    newItem->next = current->next;
                    current->next = newItem;
                }
            }
        }
        file.close();
    }

    // Save items to CSV file
    void saveToCSV() {
        ofstream file(csv_file);
        Item* current = head;
        while (current) {
            file << current->id << "," << current->name << ","
                 << current->quantity << "," << current->reg_date << "\n";
            current = current->next;
        }
        file.close();
    }

public:
    Inventory(string filename) {
        head = nullptr;
        csv_file = filename;
        loadFromCSV(); // Load data at start
    }

    // Convert string to lowercase for case-insensitive commands
    string toLower(string str) {
        for (char& c : str)
            c = tolower(c);
        return str;
    }

    // Split string by spaces
    vector<string> split(string str) {
        vector<string> tokens;
        string token;
        for (char c : str) {
            if (c == ' ') {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
            } else {
                token += c;
            }
        }
        if (!token.empty())
            tokens.push_back(token);
        return tokens;
    }

    // Add a new item
    void addItem(int id, string name, int quantity, string date) {
        Item* newItem = new Item;
        newItem->id = id;
        newItem->name = name;
        newItem->quantity = quantity;
        newItem->reg_date = date;
        newItem->next = nullptr;

        // Insert sorted by name
        if (!head || toLower(head->name) > toLower(name)) {
            newItem->next = head;
            head = newItem;
        } else {
            Item* current = head;
            while (current->next && toLower(current->next->name) < toLower(name))
                current = current->next;
            newItem->next = current->next;
            current->next = newItem;
        }

        saveToCSV(); // Save to file
        cout << "? Item added successfully.\n";
    }

    // List all items
    void listItems() {
        if (!head) {
            cout << " No items in inventory.\n";
            return;
        }

        Item* current = head;
        cout << "\n Inventory List\n";
        cout << "---------------------------------------------------\n";
        cout << left << setw(9) << "Item ID"
             << setw(21) << "Item Name"
             << setw(10) << "Quantity"
             << "Reg Date\n";
        cout << "---------------------------------------------------\n";
        while (current) {
            cout << left << setw(9) << current->id
                 << setw(21) << current->name
                 << setw(10) << current->quantity
                 << current->reg_date << "\n";
            current = current->next;
        }
    }

    // Show help for commands
    void showHelp() {
        cout << "\n?? Available Commands:\n"
             << "1 or itemadd <id> <name> <quantity> <date> - Add new item\n"
             << "2 or itemslist - List all items\n"
             << "3 or help - Show this help message\n"
             << "4 or exit - Exit the program\n"
             << "Commands are case-insensitive.\n";
    }
};

// Main program
int main() {
    Inventory inventory("inventory.csv");
    string input;

    cout << " Welcome to RCA Inventory System\n"
         << "Type 'help' or '3' for a list of commands\n";

    while (true) {
        cout << "\nCommand: ";
        getline(cin, input);
        vector<string> tokens = inventory.split(input);
        if (tokens.empty()) continue;

        string command = inventory.toLower(tokens[0]);

        if (tokens[0] == "1" || command == "itemadd") {
            if (tokens.size() != 5) {
                cout << "Usage: itemadd <id> <name> <quantity> <date>\n";
                continue;
            }
            try {
                int id = stoi(tokens[1]);
                int quantity = stoi(tokens[3]);
                inventory.addItem(id, tokens[2], quantity, tokens[4]);
            } catch (...) {
                cout << "? Invalid id or quantity. Use numbers only.\n";
            }
        }
        else if (tokens[0] == "2" || command == "itemslist") {
            inventory.listItems();
        }
        else if (tokens[0] == "3" || command == "help") {
            inventory.showHelp();
        }
        else if (tokens[0] == "4" || command == "exit") {
            cout << "?? Goodbye!\n";
            break;
        }
        else {
            cout << "??  Unknown command. Try 'help' or '3'.\n";
        }
    }

    return 0;
}
