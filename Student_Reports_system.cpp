#include <iostream>      // For input/output operations (cin, cout)
#include <fstream>       // For file handling (reading/writing files)
#include <windows.h>     // For Windows-specific functions like Sleep() and system("cls")
#include <sstream>       // For manipulating strings and conversions
using namespace std;

// Define a class called Student
class Student {
private:
    string Name, RollNo;  // Private member variables for name and roll number
    float CGPA;           // Private member variable for CGPA

public:
    // Constructor to initialize member variables with default values
    Student(): Name(""), RollNo(""), CGPA(0.0) {}

    // Setters (to assign values to private members)
    void setName(string name) {
        Name = name;
    }

    void setRollNo(string rollNo) {
        RollNo = rollNo;
    }

    void setCGPA(float cgpa) {
        CGPA = cgpa;
    }

    // Getters (to retrieve values of private members)
    string getName() {
        return Name;
    }

    string getRollNo() {
        return RollNo;
    }

    float getCGPA() {
        return CGPA;
    }
};

// Function to add student data to a file
void addStudent(Student s) {
    string name, rollNo;
    float cgpa;

    cout << "Enter Name Of Student: ";
    cin >> name;
    s.setName(name); // Set name

    cout << "Enter RollNo of Student: ";
    cin >> rollNo;
    s.setRollNo(rollNo); // Set roll number

    cout << "Enter CGPA of Student: ";
    cin >> cgpa;
    s.setCGPA(cgpa); // Set CGPA

    // Open file in append mode to add new student record
    ofstream out("Student_report.txt", ios::app);
    if (!out) {
        cout << "ERROR: File Not Opened!" << endl;
    } else {
        // Save student data in the format: Name : RollNo : CGPA
        out << s.getName() << " : " << s.getRollNo() << " : " << s.getCGPA() << endl;
        cout << "Student Added Successfully!" << endl;
    }
    out.close(); // Close file
}

// Function to search for a student by name
void search(Student s) {
    string name;
    cout << "Enter Name of Student: ";
    cin >> name;

    ifstream in("Student_report.txt"); // Open file for reading
    if (!in) {
        cout << "Error: File Can Not Open!" << endl;
    } else {
        string line;
        bool found = false;

        // Read file line by line
        while (getline(in, line)) {
            int pos = line.find(name); // Check if line contains name
            if (pos != string::npos) {
                cout << " Name | RollNo | CGPA" << endl;
                cout << line << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Student Not Found!" << endl;
        }
    }
}

// Function to update CGPA of a student based on roll number
void update() {
    string rollNo;
    cout << "Enter RollNo of Student: ";
    cin >> rollNo;

    ifstream in("Student_report.txt"); // Original file to read from
    if (!in) {
        cout << "Error: File Not Opened!" << endl;
        return;
    }

    ofstream out("Student_temp.txt"); // Temporary file to store updated data
    if (!out) {
        cout << "Error: Temporary File Not Created!" << endl;
        return;
    }

    string line;
    bool found = false;

    // Read each line and search for the matching roll number
    while (getline(in, line)) {
        int pos = line.find(rollNo);
        if (pos != string::npos) {
            found = true;

            float newcgpa;
            cout << "Enter New CGPA: ";
            cin >> newcgpa;

            // Use stringstream to convert new CGPA to string
            stringstream ss;
            ss << newcgpa;
            string newCGPA = ss.str();

            // Replace the last part of the line with new CGPA
            int cgpaPos = line.find_last_of(':');
            line.replace(cgpaPos + 2, string::npos, newCGPA);

            cout << "CGPA updated for: " << rollNo << endl;
        }
        out << line << endl; // Write (updated or original) line to temp file
    }

    if (!found) {
        cout << "Student Not Found!" << endl;
    }

    // Replace the original file with updated file
    out.close();
    in.close();
    remove("Student_report.txt");                      // Delete original file
    rename("Student_temp.txt", "Student_report.txt");  // Rename temp to original
}

// Main function - Entry point of the program
int main() {
    Student s;           // Create an object of Student class
    bool exit = false;

    while (!exit) {
        system("cls");   // Clear screen
        cout << "Welcome To Student Management System" << endl;
        cout << "************************************" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Search Student" << endl;
        cout << "3. Update Student" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter Choice: ";
        int val;
        cin >> val;

        if (val == 1) {
            system("cls");
            addStudent(s);
            Sleep(4000); // Pause for 4 seconds
        }
        else if (val == 2) {
            system("cls");
            search(s);
            Sleep(5000);
        }
        else if (val == 3) {
            system("cls");
            update();
            Sleep(5000);
        }
        else if (val == 4) {
            system("cls");
            exit = true;
            cout << "Good Luck!";
            Sleep(3000);
        }
    }
}


//ofstream out("Student_report.csv", ios::app);  // Change to .csv
//if (!out) {
//    cout << "ERROR: File Not Opened!" << endl;
//} else {
//    // Write data in CSV format: Name,RollNo,CGPA
//    out << s.getName() << "," << s.getRollNo() << "," << s.getCGPA() << endl;
//    cout << "Student Added Successfully!" << endl;
//}

//ifstream in("Student_report.csv");
//...
//while (getline(in, line)) {
//    stringstream ss(line);
//    string namePart;
//    getline(ss, namePart, ','); // Get name from CSV row
//
//    if (namePart == name) {
//        cout << "Name | RollNo | CGPA" << endl;
//        cout << line << endl;
//        found = true;
//    }
//}


