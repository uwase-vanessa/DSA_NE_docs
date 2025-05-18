#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Structure for Volunteer
struct Volunteer {
    int id;
    string name;
    string skill;
    Volunteer* next;
};

// Structure for Mission
struct Mission {
    int id;
    string name;
    string date;
    Mission* next;
};

// Structure for Assignment
struct Assignment {
    int volunteer_id;
    int mission_id;
    string date;
    Assignment* next;
};

// Class to manage volunteer coordination
class VolunteerManager {
    Volunteer* volunteers;
    Mission* missions;
    Assignment* assignments;
    string csv_volunteers;
    string csv_missions;
    string csv_assignments;

    // Convert string to lowercase
    string toLower(string str) {
        for (char &c : str)
            c = tolower(c);
        return str;
    }

    void loadVolunteers() {
        ifstream file(csv_volunteers);
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

            if (tokens.size() == 3) {
                Volunteer* newVolunteer = new Volunteer;
                newVolunteer->id = stoi(tokens[0]);
                newVolunteer->name = tokens[1];
                newVolunteer->skill = tokens[2];
                newVolunteer->next = nullptr;

                if (!volunteers || toLower(volunteers->name) > toLower(newVolunteer->name)) {
                    newVolunteer->next = volunteers;
                    volunteers = newVolunteer;
                } else {
                    Volunteer* current = volunteers;
                    while (current->next && toLower(current->next->name) < toLower(newVolunteer->name))
                        current = current->next;
                    newVolunteer->next = current->next;
                    current->next = newVolunteer;
                }
            }
        }
        file.close();
    }

    void loadMissions() {
        ifstream file(csv_missions);
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

            if (tokens.size() == 3) {
                Mission* newMission = new Mission;
                newMission->id = stoi(tokens[0]);
                newMission->name = tokens[1];
                newMission->date = tokens[2];
                newMission->next = nullptr;

                if (!missions || toLower(missions->name) > toLower(newMission->name)) {
                    newMission->next = missions;
                    missions = newMission;
                } else {
                    Mission* current = missions;
                    while (current->next && toLower(current->next->name) < toLower(newMission->name))
                        current = current->next;
                    newMission->next = current->next;
                    current->next = newMission;
                }
            }
        }
        file.close();
    }

    void loadAssignments() {
        ifstream file(csv_assignments);
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

            if (tokens.size() == 3) {
                Assignment* newAsgmt = new Assignment;
                newAsgmt->volunteer_id = stoi(tokens[0]);
                newAsgmt->mission_id = stoi(tokens[1]);
                newAsgmt->date = tokens[2];
                newAsgmt->next = nullptr;

                if (!assignments) {
                    assignments = newAsgmt;
                } else {
                    Assignment* current = assignments;
                    while (current->next)
                        current = current->next;
                    current->next = newAsgmt;
                }
            }
        }
        file.close();
    }

    void saveVolunteers() {
        ofstream file(csv_volunteers);
        Volunteer* current = volunteers;
        while (current) {
            file << current->id << "," << current->name << "," << current->skill << "\n";
            current = current->next;
        }
        file.close();
    }

    void saveMissions() {
        ofstream file(csv_missions);
        Mission* current = missions;
        while (current) {
            file << current->id << "," << current->name << "," << current->date << "\n";
            current = current->next;
        }
        file.close();
    }

    void saveAssignments() {
        ofstream file(csv_assignments);
        Assignment* current = assignments;
        while (current) {
            file << current->volunteer_id << "," << current->mission_id << "," << current->date << "\n";
            current = current->next;
        }
        file.close();
    }

public:
    VolunteerManager(string v_file, string m_file, string a_file) {
        volunteers = nullptr;
        missions = nullptr;
        assignments = nullptr;
        csv_volunteers = v_file;
        csv_missions = m_file;
        csv_assignments = a_file;
        loadVolunteers();
        loadMissions();
        loadAssignments();
    }

    void addVolunteer() {
        int id;
        string name, skill;
        cout << "Enter volunteer ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter volunteer name: ";
        getline(cin, name);
        cout << "Enter volunteer skill: ";
        getline(cin, skill);

        Volunteer* newVolunteer = new Volunteer;
        newVolunteer->id = id;
        newVolunteer->name = name;
        newVolunteer->skill = skill;
        newVolunteer->next = nullptr;

        if (!volunteers || toLower(volunteers->name) > toLower(name)) {
            newVolunteer->next = volunteers;
            volunteers = newVolunteer;
        } else {
            Volunteer* current = volunteers;
            while (current->next && toLower(current->next->name) < toLower(newVolunteer->name))
                current = current->next;
            newVolunteer->next = current->next;
            current->next = newVolunteer;
        }

        saveVolunteers();
        cout << "Volunteer added.\n";
    }

    void addMission() {
        int id;
        string name, date;
        cout << "Enter mission ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter mission name: ";
        getline(cin, name);
        cout << "Enter mission date (YYYY-MM-DD): ";
        getline(cin, date);

        Mission* newMission = new Mission;
        newMission->id = id;
        newMission->name = name;
        newMission->date = date;
        newMission->next = nullptr;

        if (!missions || toLower(missions->name) > toLower(name)) {
            newMission->next = missions;
            missions = newMission;
        } else {
            Mission* current = missions;
            while (current->next && toLower(current->next->name) < toLower(newMission->name))
                current = current->next;
            newMission->next = current->next;
            current->next = newMission;
        }

        saveMissions();
        cout << "Mission added.\n";
    }

    void assignVolunteer() {
        int volunteer_id, mission_id;
        string date;
        cout << "Enter volunteer ID: ";
        cin >> volunteer_id;
        cout << "Enter mission ID: ";
        cin >> mission_id;
        cin.ignore();
        cout << "Enter assignment date (YYYY-MM-DD): ";
        getline(cin, date);

        Volunteer* v = volunteers;
        bool volunteer_exists = false;
        while (v) {
            if (v->id == volunteer_id) {
                volunteer_exists = true;
                break;
            }
            v = v->next;
        }

        Mission* m = missions;
        bool mission_exists = false;
        while (m) {
            if (m->id == mission_id) {
                mission_exists = true;
                break;
            }
            m = m->next;
        }

        if (!volunteer_exists || !mission_exists) {
            cout << "Invalid volunteer or mission ID.\n";
            return;
        }

        Assignment* newAsgmt = new Assignment;
        newAsgmt->volunteer_id = volunteer_id;
        newAsgmt->mission_id = mission_id;
        newAsgmt->date = date;
        newAsgmt->next = nullptr;

        if (!assignments) {
            assignments = newAsgmt;
        } else {
            Assignment* current = assignments;
            while (current->next)
                current = current->next;
            current->next = newAsgmt;
        }

        saveAssignments();
        cout << "Volunteer assigned.\n";
    }

    void listVolunteers() {
        if (!volunteers) {
            cout << "No volunteers registered.\n";
            return;
        }

        cout << "ID    Name                 Skill\n";
        cout << "--------------------------------\n";
        Volunteer* current = volunteers;
        while (current) {
            cout << left << setw(6) << current->id
                 << setw(21) << current->name
                 << current->skill << "\n";
            current = current->next;
        }
    }

    void listMissions() {
        if (!missions) {
            cout << "No missions registered.\n";
            return;
        }

        cout << "ID    Name                 Date\n";
        cout << "--------------------------------\n";
        Mission* current = missions;
        while (current) {
            cout << left << setw(6) << current->id
                 << setw(21) << current->name
                 << current->date << "\n";
            current = current->next;
        }
    }

    void listAssignments() {
        if (!assignments) {
            cout << "No assignments made.\n";
            return;
        }

        cout << "VolunteerID  MissionID    Date\n";
        cout << "-------------------------------\n";
        Assignment* current = assignments;
        while (current) {
            cout << left << setw(13) << current->volunteer_id
                 << setw(13) << current->mission_id
                 << current->date << "\n";
            current = current->next;
        }
    }
};

// Entry point for testing
int main() {
    VolunteerManager manager("volunteers.csv", "missions.csv", "assignments.csv");

    int choice;
    do {
        cout << "\nVolunteer Management System\n";
        cout << "1. Add Volunteer\n";
        cout << "2. Add Mission\n";
        cout << "3. Assign Volunteer\n";
        cout << "4. List Volunteers\n";
        cout << "5. List Missions\n";
        cout << "6. List Assignments\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.addVolunteer(); break;
            case 2: manager.addMission(); break;
            case 3: manager.assignVolunteer(); break;
            case 4: manager.listVolunteers(); break;
            case 5: manager.listMissions(); break;
            case 6: manager.listAssignments(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
