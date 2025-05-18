#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Car {
    string name;
    string number;
    string model;
    string rentPrice;
};

struct RentRecord {
    string carNumber;
    string renterName;
    string renterPhone;
    string renterAddress;
    string startDate;
    string endDate;
};

vector<Car> cars;
vector<RentRecord> rentRecords;

string getInput(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

void showMenu() {
    cout << "\nCar Rental System\n";
    cout << "1. Check Car\n";
    cout << "2. Add Car\n";
    cout << "3. Update Car\n";
    cout << "4. Remove Car\n";
    cout << "5. Show All Cars\n";
    cout << "6. Rent Car\n";
    cout << "7. Update Rent\n";
    cout << "8. Show Rent Records\n";
    cout << "0. Exit\n";
    cout << "Choose option: ";
}

void checkCar() {
    string name = getInput("Enter car name: ");
    
    for (int i = 0; i < cars.size(); i++) {
        if (cars[i].name == name) {
            cout << "\nCar Details:\n";
            cout << "Name: " << cars[i].name << endl;
            cout << "Number: " << cars[i].number << endl;
            cout << "Model: " << cars[i].model << endl;
            cout << "Rent Price: $" << cars[i].rentPrice << "/day\n";
            return;
        }
    }
    cout << "Car not found!\n";
}

void addCar() {
    Car newCar;
    newCar.name = getInput("Enter car name: ");
    newCar.number = "C" + to_string(cars.size() + 100);
    newCar.model = getInput("Enter car model: ");
    newCar.rentPrice = getInput("Enter rent price per day: $");

    cars.push_back(newCar);
    cout << "Car added successfully! Number: " << newCar.number << endl;
}

void updateCar() {
    string number = getInput("Enter car number: ");
    
    for (int i = 0; i < cars.size(); i++) {
        if (cars[i].number == number) {
            cars[i].name = getInput("New name: ");
            cars[i].model = getInput("New model: ");
            cars[i].rentPrice = getInput("New rent price: $");
            cout << "Car updated!\n";
            return;
        }
    }
    cout << "Car not found!\n";
}

void removeCar() {
    string number = getInput("Enter car number to remove: ");
    
    for (int i = 0; i < cars.size(); i++) {
        if (cars[i].number == number) {
            cars.erase(cars.begin() + i);
            cout << "Car removed!\n";
            return;
        }
    }
    cout << "Car not found!\n";
}

void showAllCars() {
    cout << "\nAll Cars (" << cars.size() << ")\n";
    cout << "No. Name\tNumber\tModel\tPrice/day\n";
    
    for (int i = 0; i < cars.size(); i++) {
        cout << i+1 << ". " << cars[i].name << "\t" 
             << cars[i].number << "\t" << cars[i].model << "\t$" 
             << cars[i].rentPrice << endl;
    }
}

void rentCar() {
    RentRecord record;
    record.carNumber = getInput("Enter car number: ");
    record.renterName = getInput("Enter renter name: ");
    record.renterPhone = getInput("Enter renter phone: ");
    record.renterAddress = getInput("Enter renter address: ");
    record.startDate = getInput("Enter start date (dd-mm-yyyy): ");
    record.endDate = getInput("Enter end date (dd-mm-yyyy): ");

    rentRecords.push_back(record);
    cout << "Car rented successfully!\n";
}

void showRentRecords() {
    cout << "\nRent Records (" << rentRecords.size() << ")\n";
    cout << "No. Car\tRenter\tEnd Date\n";
    
    for (int i = 0; i < rentRecords.size(); i++) {
        cout << i+1 << ". " << rentRecords[i].carNumber << "\t" 
             << rentRecords[i].renterName << "\t" << rentRecords[i].endDate << endl;
    }
}

void updateRent() {
    string number = getInput("Enter car number to update rent: ");
    
    for (int i = 0; i < rentRecords.size(); i++) {
        if (rentRecords[i].carNumber == number) {
            rentRecords[i].renterName = getInput("New renter name: ");
            rentRecords[i].renterPhone = getInput("New renter phone: ");
            rentRecords[i].renterAddress = getInput("New renter address: ");
            rentRecords[i].startDate = getInput("New start date: ");
            rentRecords[i].endDate = getInput("New end date: ");
            cout << "Rent updated!\n";
            return;
        }
    }
    cout << "Rent record not found!\n";
}

int main() {
    cout << "Car Rental System\n";

    while (true) {
        showMenu();
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: checkCar(); break;
            case 2: addCar(); break;
            case 3: updateCar(); break;
            case 4: removeCar(); break;
            case 5: showAllCars(); break;
            case 6: rentCar(); break;
            case 7: updateRent(); break;
            case 8: showRentRecords(); break;
            case 0: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}