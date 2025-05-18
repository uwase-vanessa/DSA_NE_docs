#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype> // Needed for tolower()

using namespace std;

// Structure for a generic data record
struct Record {
    int id;           // Unique identifier
    string name;      // Name of item/person/book/etc.
    int value;        // Generic value (quantity, age, etc.)
    string extra;     // Extra field (date, category, etc.)
    Record* next;     // Pointer to next record
};

// Class to manage a dynamic linked list of records
class DataManager {
    Record* head;     // Head of linked list
    string csv_file;  // File for persistent storage

    // Load records from CSV
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
            tokens.push_back(token);

            if (tokens.size() == 4) {
                Record* newRecord = new Record;
                newRecord->id = stoi(tokens[0]);
                newRecord->name = tokens[1];
                newRecord->value = stoi(tokens[2]);
                newRecord->extra = tokens[3];
                newRecord->next = nullptr;

                // Insert sorted by name
                if (!head || toLower(head->name) > toLower(newRecord->name)) {
                    newRecord->next = head;
                    head = newRecord;
                } else {
                    Record* current = head;
                    while (current->next && toLower(current->next->name) < toLower(newRecord->name))
                        current = current->next;
                    newRecord->next = current->next;
                    current->next = newRecord;
                }
            }
        }
        file.close();
    }

    // Save records to CSV
    void saveToCSV() {
        ofstream file(csv_file);
        Record* current = head;
        while (current) {
            file << current->id << "," << current->name << ","
                 << current->value << "," << current->extra << "\n";
            current = current->next;
        }
        file.close();
    }

public:
    DataManager(string filename) {
        head = nullptr;
        csv_file = filename;
        loadFromCSV();
    }

    // Convert string to lowercase
    string toLower(string str) {
        for (char &c : str)
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

    // Add a new record
    void addRecord(int id, string name, int value, string extra) {
        Record* newRecord = new Record;
        newRecord->id = id;
        newRecord->name = name;
        newRecord->value = value;
        newRecord->extra = extra;
        newRecord->next = nullptr;

        // Insert sorted by name
        if (!head || toLower(head->name) > toLower(name)) {
            newRecord->next = head;
            head = newRecord;
        } else {
            Record* current = head;
            while (current->next && toLower(current->next->name) < toLower(newRecord->name))
                current = current->next;
            newRecord->next = current->next;
            current->next = newRecord;
        }

        saveToCSV();
        cout << "Record added.\n";
    }

    // List all records
    void listRecords() {
        if (!head) {
            cout << "No records found.\n";
            return;
        }

        Record* current = head;
        cout << "ID    Name                 Value  Extra\n";
        cout << "------------------------------------\n";
        while (current) {
            cout << left << setw(6) << current->id
                 << setw(21) << current->name
                 << setw(7) << current->value
                 << current->extra << "\n";
            current = current->next;
        }
    }

    // Delete a record by ID
    void deleteRecord(int id) {
        if (!head) {
            cout << "No records to delete.\n";
            return;
        }

        if (head->id == id) {
            Record* temp = head;
            head = head->next;
            delete temp;
            saveToCSV();
            cout << "Record deleted.\n";
            return;
        }

        Record* current = head;
        while (current->next && current->next->id != id)
            current = current->next;

        if (current->next) {
            Record* temp = current->next;
            current->next = temp->next;
            delete temp;
            saveToCSV();
            cout << "Record deleted.\n";
        } else {
            cout << "Record ID not found.\n";
        }
    }

    // Search records by name (partial match)
    void searchRecords(string query) {
        query = toLower(query);
        Record* current = head;
        bool found = false;

        cout << "ID    Name                 Value  Extra\n";
        cout << "------------------------------------\n";
        while (current) {
            if (toLower(current->name).find(query) != string::npos) {
                cout << left << setw(6) << current->id
                     << setw(21) << current->name
                     << setw(7) << current->value
                     << current->extra << "\n";
                found = true;
            }
            current = current->next;
        }
        if (!found)
            cout << "No records match '" << query << "'.\n";
    }

    // Show help for commands
    void showHelp() {
        cout << "Commands:\n"
             << "1 or add <id> <name> <value> <extra> - Add a record\n"
             << "2 or list - List all records\n"
             << "3 or delete <id> - Delete a record\n"
             << "4 or search <query> - Search records by name\n"
             << "5 or help - Show this help\n"
             << "6 or exit - Exit program\n"
             << "Commands are case-insensitive.\n";
    }
};

// Main program
int main() {
    DataManager manager("data.csv");
    string input;

    cout << "Dynamic Data Manager\n"
         << "Enter 'help' or '5' for commands\n";

    while (true) {
        cout << "\nCommand: ";
        getline(cin, input);
        vector<string> tokens = manager.split(input);
        if (tokens.empty()) continue;

        string command = manager.toLower(tokens[0]);

        if (tokens[0] == "1" || command == "add") {
            if (tokens.size() != 5) {
                cout << "Use: add <id> <name> <value> <extra>\n";
                continue;
            }
            try {
                int id = stoi(tokens[1]);
                int value = stoi(tokens[3]);
                manager.addRecord(id, tokens[2], value, tokens[4]);
            } catch (...) {
                cout << "Invalid id or value. Use numbers.\n";
            }
        }
        else if (tokens[0] == "2" || command == "list") {
            manager.listRecords();
        }
        else if (tokens[0] == "3" || command == "delete") {
            if (tokens.size() != 2) {
                cout << "Use: delete <id>\n";
                continue;
            }
            try {
                int id = stoi(tokens[1]);
                manager.deleteRecord(id);
            } catch (...) {
                cout << "Invalid id. Use a number.\n";
            }
        }
        else if (tokens[0] == "4" || command == "search") {
            if (tokens.size() < 2) {
                cout << "Use: search <query>\n";
                continue;
            }
            string query = tokens[1];
            for (int i = 2; i < tokens.size(); i++)
                query += " " + tokens[i];
            manager.searchRecords(query);
        }
        else if (tokens[0] == "5" || command == "help") {
            manager.showHelp();
        }
        else if (tokens[0] == "6" || command == "exit") {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Unknown command. Try 'help' or '5'.\n";
        }
    }

    return 0;
}
