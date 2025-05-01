#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

struct Car {
    string model;
    string plateNumber;
    double rentPerDay;
    bool isAvailable;
};

struct RentalRecord {
    string customerName;
    string customerPhone;
    string plateNumber;
    int rentalDays;
    double totalAmount;
};

vector<Car> cars;
vector<RentalRecord> rentals;

const string carFile = "cars.csv";
const string rentalFile = "rental_records.csv";

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void saveCars() {
    ofstream file(carFile);
    for (const auto& car : cars) {
        file << car.model << "," << car.plateNumber << "," << car.rentPerDay << "," << car.isAvailable << endl;
    }
    file.close();
}

void loadCars() {
    ifstream file(carFile);
    string line;
    cars.clear();
    while (getline(file, line)) {
        vector<string> data = split(line, ',');
        if (data.size() == 4) {
            try {
                Car car;
                car.model = data[0];
                car.plateNumber = data[1];
                car.rentPerDay = stod(data[2]);
                car.isAvailable = (data[3] == "1");
                cars.push_back(car);
            } catch (...) {
                cerr << "Skipping invalid car data line: " << line << endl;
            }
        }
    }
    file.close();
}

void saveRentals() {
    ofstream file(rentalFile);
    for (const auto& r : rentals) {
        file << r.customerName << "," << r.customerPhone << "," << r.plateNumber << ","
             << r.rentalDays << "," << r.totalAmount << endl;
    }
    file.close();
}

void loadRentals() {
    ifstream file(rentalFile);
    string line;
    rentals.clear();
    while (getline(file, line)) {
        vector<string> data = split(line, ',');
        if (data.size() == 5) {
            try {
                RentalRecord r;
                r.customerName = data[0];
                r.customerPhone = data[1];
                r.plateNumber = data[2];
                r.rentalDays = stoi(data[3]);
                r.totalAmount = stod(data[4]);
                rentals.push_back(r);
            } catch (...) {
                cerr << "Skipping invalid rental data line: " << line << endl;
            }
        }
    }
    file.close();
}

void addCar() {
    Car car;
    cout << "Enter car model: ";
    cin.ignore(); getline(cin, car.model);
    cout << "Enter plate number: ";
    getline(cin, car.plateNumber);
    cout << "Enter rent per day: ";
    cin >> car.rentPerDay;
    car.isAvailable = true;
    cars.push_back(car);
    saveCars();
    cout << "Car added successfully!\n\n";
}

void rentCar() {
    string plate;
    cout << "Enter plate number of car to rent: ";
    cin >> plate;
    for (auto& car : cars) {
        if (car.plateNumber == plate && car.isAvailable) {
            RentalRecord r;
            cin.ignore();
            cout << "Enter your name: "; getline(cin, r.customerName);
            cout << "Enter phone: "; getline(cin, r.customerPhone);
            cout << "Enter number of rental days: "; cin >> r.rentalDays;
            r.plateNumber = plate;
            r.totalAmount = r.rentalDays * car.rentPerDay;
            car.isAvailable = false;
            rentals.push_back(r);
            saveCars(); saveRentals();
            cout << "\nCar rented successfully to " << r.customerName << " for " << r.rentalDays << " days.\n\n";
            return;
        }
    }
    cout << "\nCar not available or doesn't exist.\n\n";
}

void returnCar() {
    string name;
    cout << "Enter name of customer returning car: ";
    cin.ignore(); getline(cin, name);

    for (size_t i = 0; i < rentals.size(); ++i) {
        if (rentals[i].customerName == name) {
            for (auto& car : cars) {
                if (car.plateNumber == rentals[i].plateNumber) {
                    car.isAvailable = true;
                    break;
                }
            }
            rentals.erase(rentals.begin() + i);
            saveCars(); saveRentals();
            cout << "\nCar returned successfully.\n\n";
            return;
        }
    }
    cout << "\nNo rental record found for this name.\n\n";
}

void displayCars() {
    cout << left << setw(20) << "Model" << setw(15) << "Plate No" << setw(15) << "Rent/Day" << "Status" << endl;
    cout << string(60, '-') << endl;
    for (const auto& car : cars) {
        cout << left << setw(20) << car.model << setw(15) << car.plateNumber << setw(15) << car.rentPerDay
             << (car.isAvailable ? "Available" : "Rented") << endl;
    }
    cout << endl;
}

void displayRentedCars() {
    cout << "\nCurrently Rented Cars:\n";
    cout << left << setw(20) << "Customer Name" << setw(15) << "Phone" << setw(15) << "Plate No"
         << setw(10) << "Days" << setw(10) << "Total($)" << endl;
    cout << string(70, '-') << endl;
    for (const auto& r : rentals) {
        cout << left << setw(20) << r.customerName << setw(15) << r.customerPhone << setw(15) << r.plateNumber
             << setw(10) << r.rentalDays << fixed << setprecision(2) << "$" << r.totalAmount << endl;
    }
    cout << endl;
}

void menu() {
    int choice;
    do {
        cout << "========== Car Rental System ==========" << endl;
        cout << "1. Add New Car" << endl;
        cout << "2. Display Cars" << endl;
        cout << "3. Rent a Car" << endl;
        cout << "4. Return a Car" << endl;
        cout << "5. View Rented Cars" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;
        switch (choice) {
            case 1: addCar(); break;
            case 2: displayCars(); break;
            case 3: rentCar(); break;
            case 4: returnCar(); break;
            case 5: displayRentedCars(); break;
            case 0: cout << "Goodbye!\n"; exit(0);
            default: cout << "Invalid choice. Try again.\n\n"; break;
        }
    } while (choice != 0);
}

int main() {
    loadCars();
    loadRentals();
    menu();
    return 0;
}

