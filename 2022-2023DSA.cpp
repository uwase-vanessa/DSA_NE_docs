#include <iostream>
#include "fstream"
#include "sstream"
#include "vector"
#include "algorithm"

#define FILE_NAME "items.csv"

using namespace std;

struct Item
{
    int item_id;
    string item_name;
    int item_quantity;
    string item_registration_date;
};

bool compareAlphabetically(const Item &a, const Item &b)
{
    return a.item_name < b.item_name;
}

void listItems()
{
    ifstream file(FILE_NAME);
    vector<Item> items;
    string line;
    string item_id, item_name, item_quantity, item_registration_date;

    if (file.is_open())
    {
        while (getline(file, line))
        {

            // convert to string stream
            istringstream ss(line);

            // store stream values to corresponding variables
            if (ss >> item_id >> item_name >> item_quantity >> item_registration_date)
            {
                Item itm = {
                    stoi(item_id),
                    item_name,
                    stoi(item_quantity),
                    item_registration_date};
                items.push_back(itm);
            }
            else
            {
                cerr << "Invalid record : " << line << endl;
            }
        }
        if (!items.empty())
        {
            sort(items.begin(), items.end(), compareAlphabetically);
            for (auto &item : items)
            {
                cout << "Item ID: " << item.item_id << "\t" << "Item Name :" << item.item_name << "\t"
                     << "Quantity :" << item.item_quantity << "\t" << "Reg Date :"
                     << item.item_registration_date << endl;
            }
        }
        else
        {
            cout << "No items found in " << FILE_NAME << endl;
        }
        file.close();
    }
    else
    {
        cerr << "failed to open the file : " << FILE_NAME << endl;
    }
}

void addItem(const Item &itm)
{
    ofstream file(FILE_NAME, ios::app);
    if (file.is_open())
    {
        file << itm.item_id << " " << itm.item_name << " " << itm.item_quantity << " " << itm.item_registration_date
             << endl;
        cout << "Item saved successfully!" << endl;
        file.close();
    }
    else
    {
        cerr << "failed to open the file : " << FILE_NAME << endl;
    }
}

string convertToLowercase(const string &str)
{
    string lowercase_str;
    for (auto character : str)
    {
        lowercase_str.push_back(character);
    }
    return lowercase_str;
}

int main()
{
    string command, user_input, item_id, item_name, item_quantity, item_registration_date;

    while (true)
    {
        cout << "Enter command" << endl;
        getline(cin, user_input);
        istringstream ss(user_input);
        ss >> command;
        command = convertToLowercase(command);
        if (command == "itemadd")
        {
            if (ss >> item_id >> item_name >> item_quantity >> item_registration_date)
            {
                Item item = {
                    stoi(item_id),
                    item_name,
                    stoi(item_quantity),
                    item_registration_date};
                addItem(item);
            }
            else
            {
                cerr << "Invalid input format" << endl;
            }
        }
        else if (command == "itemslist")
        {
            listItems();
        }
        else if (command == "help")
        {
            cout << "----------------------" << endl;
            cout << "*\t Commands syntaxes \t *" << endl;
            cout << "\t itemadd <item_id> <item_name> <quantity> <registration_date>\n \t itemslist" << endl;
        }
        else if (command == "exit")
        {
            cout << "Quitting the program..." << endl;
            exit(0);
        }
        else
        {
            cerr << "Invalid Command" << endl;
        }
    }
}
