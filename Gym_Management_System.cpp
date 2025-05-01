#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Member class definition
class Member {
private:
    string name;
    int age;
    bool attendance; // Attendance status

public:
    Member(string name, int age) {
        this->name = name;
        this->age = age;
        this->attendance = false;  // Initially, attendance is false
    }

    string getName() {
        return name;
    }

    int getAge() {
        return age;
    }

    bool getAttendance() {
        return attendance;
    }

    void setAttendance(bool attendanceStatus) {
        this->attendance = attendanceStatus;
    }

    // Save member details to CSV file
    void saveToFile(ofstream& file) {
        file << name << "," << age << "," << attendance << endl;
    }
};

// Trainer class definition
class Trainer {
private:
    string name;
    string specialization;

public:
    Trainer(string name, string specialization) {
        this->name = name;
        this->specialization = specialization;
    }

    string getName() {
        return name;
    }

    string getSpecialization() {
        return specialization;
    }

    // Save trainer details to CSV file
    void saveToFile(ofstream& file) {
        file << name << "," << specialization << endl;
    }
};

// Gym class to manage members and trainers
class Gym {
private:
    vector<Member> members;
    vector<Trainer> trainers;

public:
    // Add a member to the gym
    void addMember(string name, int age) {
        Member newMember(name, age);
        members.push_back(newMember);
        cout << "Member Added Successfully!" << endl;
        saveMembersToFile(); // Save member details to CSV file
    }

    // Add a trainer to the gym
    void addTrainer(string name, string specialization) {
        Trainer newTrainer(name, specialization);
        trainers.push_back(newTrainer);
        cout << "Trainer Added Successfully!" << endl;
        saveTrainersToFile(); // Save trainer details to CSV file
    }

    // Mark attendance for a member
    void markAttendance(string name) {
        for (int i = 0; i < members.size(); i++) {
            if (members[i].getName() == name) {
                members[i].setAttendance(true);
                cout << "Attendance marked for member: " << members[i].getName() << endl;
                saveMembersToFile(); // Save attendance data to CSV file
                return;
            }
        }
        cout << "Member not found!" << endl;
    }

    // Display all members and their details
    void displayMembers() {
        cout << "Members List: " << endl;
        for (int i = 0; i < members.size(); i++) {
            cout << "Name: " << members[i].getName() << ", Age: " << members[i].getAge()
                 << ", Attendance: " << (members[i].getAttendance() ? "Present" : "Absent") << endl;
        }
    }

    // Display all trainers
    void displayTrainers() {
        cout << "Trainers List: " << endl;
        for (int i = 0; i < trainers.size(); i++) {
            cout << "Name: " << trainers[i].getName() << ", Specialization: " << trainers[i].getSpecialization() << endl;
        }
    }

    // Calculate and display total fees based on attendance
    void calculateFees() {
        int totalFees = 0;
        for (int i = 0; i < members.size(); i++) {
            if (members[i].getAttendance()) {
                int fee = (members[i].getAge() > 20) ? 200 : 100;
                totalFees += fee;
            }
        }
        cout << "Total Fees Collected: " << totalFees << endl;
    }

    // Save members' details to a CSV file
    void saveMembersToFile() {
        ofstream file("members.csv", ios::trunc); // Open file in truncate mode to overwrite previous data
        if (file.is_open()) {
            file << "Name,Age,Attendance" << endl; // Add headers
            for (int i = 0; i < members.size(); i++) {
                members[i].saveToFile(file); // Save each member's details
            }
            file.close();
        } else {
            cout << "Error opening members.csv file!" << endl;
        }
    }

    // Save trainers' details to a CSV file
    void saveTrainersToFile() {
        ofstream file("trainers.csv", ios::trunc); // Open file in truncate mode to overwrite previous data
        if (file.is_open()) {
            file << "Name,Specialization" << endl; // Add headers
            for (int i = 0; i < trainers.size(); i++) {
                trainers[i].saveToFile(file); // Save each trainer's details
            }
            file.close();
        } else {
            cout << "Error opening trainers.csv file!" << endl;
        }
    }

    // Load members and trainers from CSV files (if they exist)
    void loadDataFromFile() {
        ifstream memberFile("members.csv");
        if (memberFile.is_open()) {
            string line;
            getline(memberFile, line); // Skip header line
            while (getline(memberFile, line)) {
                stringstream ss(line);
                string name, ageStr, attendanceStr;
                getline(ss, name, ',');
                getline(ss, ageStr, ',');
                getline(ss, attendanceStr, ',');
                int age = stoi(ageStr);
                bool attendance = (attendanceStr == "1");
                members.push_back(Member(name, age));
                members.back().setAttendance(attendance);
            }
            memberFile.close();
        }

        ifstream trainerFile("trainers.csv");
        if (trainerFile.is_open()) {
            string line;
            getline(trainerFile, line); // Skip header line
            while (getline(trainerFile, line)) {
                stringstream ss(line);
                string name, specialization;
                getline(ss, name, ',');
                getline(ss, specialization, ',');
                trainers.push_back(Trainer(name, specialization));
            }
            trainerFile.close();
        }
    }
};

int main() {
    Gym gym;
    gym.loadDataFromFile(); // Load previous data from files

    int choice;
    while (true) {
        cout << "\n***** Gym Management System *****" << endl;
        cout << "1. Add Member" << endl;
        cout << "2. Add Trainer" << endl;
        cout << "3. Mark Attendance" << endl;
        cout << "4. Display Members" << endl;
        cout << "5. Display Trainers" << endl;
        cout << "6. Calculate Fees" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        string name;
        int age;
        string specialization;

        switch (choice) {
            case 1:
                cout << "Enter member name: ";
                cin >> name;
                cout << "Enter member age: ";
                cin >> age;
                gym.addMember(name, age);
                break;
            case 2:
                cout << "Enter trainer name: ";
                cin >> name;
                cout << "Enter trainer specialization: ";
                cin >> specialization;
                gym.addTrainer(name, specialization);
                break;
            case 3:
                cout << "Enter member name to mark attendance: ";
                cin >> name;
                gym.markAttendance(name);
                break;
            case 4:
                gym.displayMembers();
                break;
            case 5:
                gym.displayTrainers();
                break;
            case 6:
                gym.calculateFees();
                break;
            case 0:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}

