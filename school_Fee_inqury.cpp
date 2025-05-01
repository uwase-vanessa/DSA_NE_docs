#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

class Student {
private:
    string name;
    int rollNo, fee;

public:
    // Constructor to initialize student data
    Student(int RollNo, string Name, int Fee) {
        name = Name;
        rollNo = RollNo;
        fee = Fee;
    }

    string getName() {
        return name;
    }

    int getRollNo() {
        return rollNo;
    }

    int getFee() {
        return fee;
    }

    // Update the fee of the student
    void updateFee(int newFee) {
        fee = newFee;
    }

    // Save student details to a CSV file
    void saveToFile(ofstream& file) {
        file << rollNo << "," << name << "," << fee << endl;
    }

    // Convert string to lowercase to make comparison case-insensitive
    static string toLowerCase(string str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }
};

class FeeInq {
private:
    vector<Student> students;

    // Load student data from the file into the vector
    void loadData() {
        ifstream file("students.csv");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string name, feeStr, rollNoStr;
                int rollNo, fee;

                getline(ss, rollNoStr, ',');
                getline(ss, name, ',');
                getline(ss, feeStr, ',');
                
                rollNo = stoi(rollNoStr);
                fee = stoi(feeStr);

                Student student(rollNo, name, fee);
                students.push_back(student);
            }
            file.close();
        }
    }

    // Save all student data to the file
    void saveData() {
        ofstream file("students.csv", ios::trunc); // Open the file in truncate mode to overwrite
        if (file.is_open()) {
            for (int i = 0; i < students.size(); i++) {
                students[i].saveToFile(file);
            }
            file.close();
        } else {
            cout << "Error saving data to file!" << endl;
        }
    }

public:
    FeeInq() {
        loadData(); // Load student data from file when the program starts
    }

    // Add a student
    void add(int RollNo, string Name, int Fee) {
        Student student(RollNo, Name, Fee);
        students.push_back(student);
        saveData(); // Save updated student list to file
    }

    // Search student by roll number and display fee
    void feeStatusByRollNo(int rollNo) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getRollNo() == rollNo) {
                cout << "Roll No: " << students[i].getRollNo() << endl;
                cout << "Name: " << students[i].getName() << endl;
                cout << "Fee: " << students[i].getFee() << " per month" << endl;
                return;
            }
        }
        cout << "Student with Roll No " << rollNo << " not found!" << endl;
    }

    // Search student by name and display fee
    void feeStatusByName(string name) {
        bool found = false;
        // Convert the input name to lowercase to make comparison case-insensitive
        name = Student::toLowerCase(name);

        for (int i = 0; i < students.size(); i++) {
            string studentName = Student::toLowerCase(students[i].getName());
            if (studentName == name) {
                cout << "Roll No: " << students[i].getRollNo() << endl;
                cout << "Name: " << students[i].getName() << endl;
                cout << "Fee: " << students[i].getFee() << " per month" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Student with name " << name << " not found!" << endl;
        }
    }

    // Update a student's fee
    void updateStudentFee(int rollNo, int newFee) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getRollNo() == rollNo) {
                students[i].updateFee(newFee);
                saveData(); // Save the updated data
                cout << "Fee updated for student with Roll No " << rollNo << endl;
                return;
            }
        }
        cout << "Student with Roll No " << rollNo << " not found!" << endl;
    }

    // Display all students
    void displayAllStudents() {
        cout << "All Students List:" << endl;
        for (int i = 0; i < students.size(); i++) {
            cout << "Roll No: " << students[i].getRollNo() << ", "
                 << "Name: " << students[i].getName() << ", "
                 << "Fee: " << students[i].getFee() << " per month" << endl;
        }
    }
};

int main() {
    FeeInq feeInquiry;
    int choice;

    while (true) {
        cout << "\n***** Fee Inquiry Management System *****" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Fee Inquiry by Roll Number" << endl;
        cout << "3. Fee Inquiry by Name" << endl;
        cout << "4. Update Fee" << endl;
        cout << "5. Display All Students" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        int rollNo, fee;
        string name;

        switch (choice) {
            case 1:
                cout << "Enter Roll No: ";
                cin >> rollNo;
                cin.ignore();  // To ignore the newline character left by cin
                cout << "Enter Name: ";
                getline(cin, name);  // Use getline to read full name with spaces
                cout << "Enter Fee: ";
                cin >> fee;
                feeInquiry.add(rollNo, name, fee);
                break;
            case 2:
                cout << "Enter Roll No for Fee Inquiry: ";
                cin >> rollNo;
                feeInquiry.feeStatusByRollNo(rollNo);
                break;
            case 3:
                cin.ignore();  // To ignore the newline character left by cin
                cout << "Enter Name for Fee Inquiry: ";
                getline(cin, name);  // Use getline to read full name with spaces
                feeInquiry.feeStatusByName(name);
                break;
            case 4:
                cout << "Enter Roll No for Fee Update: ";
                cin >> rollNo;
                cout << "Enter New Fee: ";
                cin >> fee;
                feeInquiry.updateStudentFee(rollNo, fee);
                break;
            case 5:
                feeInquiry.displayAllStudents();
                break;
            case 6:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

