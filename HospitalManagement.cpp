#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Structure for Patient
struct Patient {
    int id;
    string name;
    string condition;
    Patient* next;
};

// Structure for Doctor
struct Doctor {
    int id;
    string name;
    string specialty;
    Doctor* next;
};

// Structure for Appointment
struct Appointment {
    int patient_id;
    int doctor_id;
    string date;
    Appointment* next;
};

// Class to manage hospital data
class HospitalManager {
    Patient* patients;
    Doctor* doctors;
    Appointment* appointments;
    string csv_patients;
    string csv_doctors;
    string csv_appointments;

    string toLower(string str) {
        for (char &c : str)
            c = tolower(c);
        return str;
    }

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

    void loadPatients() {
        ifstream file(csv_patients);
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
                Patient* newPatient = new Patient{stoi(tokens[0]), tokens[1], tokens[2], nullptr};

                if (!patients || toLower(patients->name) > toLower(newPatient->name)) {
                    newPatient->next = patients;
                    patients = newPatient;
                } else {
                    Patient* current = patients;
                    while (current->next && toLower(current->next->name) < toLower(newPatient->name))
                        current = current->next;
                    newPatient->next = current->next;
                    current->next = newPatient;
                }
            }
        }
        file.close();
    }

    void loadDoctors() {
        ifstream file(csv_doctors);
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
                Doctor* newDoctor = new Doctor{stoi(tokens[0]), tokens[1], tokens[2], nullptr};

                if (!doctors || toLower(doctors->name) > toLower(newDoctor->name)) {
                    newDoctor->next = doctors;
                    doctors = newDoctor;
                } else {
                    Doctor* current = doctors;
                    while (current->next && toLower(current->next->name) < toLower(newDoctor->name))
                        current = current->next;
                    newDoctor->next = current->next;
                    current->next = newDoctor;
                }
            }
        }
        file.close();
    }

    void loadAppointments() {
        ifstream file(csv_appointments);
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
                Appointment* newAppt = new Appointment{stoi(tokens[0]), stoi(tokens[1]), tokens[2], nullptr};

                if (!appointments) {
                    appointments = newAppt;
                } else {
                    Appointment* current = appointments;
                    while (current->next)
                        current = current->next;
                    current->next = newAppt;
                }
            }
        }
        file.close();
    }

    void savePatients() {
        ofstream file(csv_patients);
        Patient* current = patients;
        while (current) {
            file << current->id << "," << current->name << "," << current->condition << "\n";
            current = current->next;
        }
        file.close();
    }

    void saveDoctors() {
        ofstream file(csv_doctors);
        Doctor* current = doctors;
        while (current) {
            file << current->id << "," << current->name << "," << current->specialty << "\n";
            current = current->next;
        }
        file.close();
    }

    void saveAppointments() {
        ofstream file(csv_appointments);
        Appointment* current = appointments;
        while (current) {
            file << current->patient_id << "," << current->doctor_id << "," << current->date << "\n";
            current = current->next;
        }
        file.close();
    }

public:
    HospitalManager(string p_file, string d_file, string a_file) {
        patients = nullptr;
        doctors = nullptr;
        appointments = nullptr;
        csv_patients = p_file;
        csv_doctors = d_file;
        csv_appointments = a_file;
        loadPatients();
        loadDoctors();
        loadAppointments();
    }

    void addPatient(int id, string name, string condition) {
        Patient* newPatient = new Patient{id, name, condition, nullptr};

        if (!patients || toLower(patients->name) > toLower(name)) {
            newPatient->next = patients;
            patients = newPatient;
        } else {
            Patient* current = patients;
            while (current->next && toLower(current->next->name) < toLower(newPatient->name))
                current = current->next;
            newPatient->next = current->next;
            current->next = newPatient;
        }

        savePatients();
        cout << "Patient added.\n";
    }

    void addDoctor(int id, string name, string specialty) {
        Doctor* newDoctor = new Doctor{id, name, specialty, nullptr};

        if (!doctors || toLower(doctors->name) > toLower(name)) {
            newDoctor->next = doctors;
            doctors = newDoctor;
        } else {
            Doctor* current = doctors;
            while (current->next && toLower(current->next->name) < toLower(newDoctor->name))
                current = current->next;
            newDoctor->next = current->next;
            current->next = newDoctor;
        }

        saveDoctors();
        cout << "Doctor added.\n";
    }

    void bookAppointment(int patient_id, int doctor_id, string date) {
        bool patient_exists = false, doctor_exists = false;

        Patient* p = patients;
        while (p) {
            if (p->id == patient_id) {
                patient_exists = true;
                break;
            }
            p = p->next;
        }

        Doctor* d = doctors;
        while (d) {
            if (d->id == doctor_id) {
                doctor_exists = true;
                break;
            }
            d = d->next;
        }

        if (!patient_exists || !doctor_exists) {
            cout << "Invalid patient or doctor ID.\n";
            return;
        }

        Appointment* newAppt = new Appointment{patient_id, doctor_id, date, nullptr};

        if (!appointments) {
            appointments = newAppt;
        } else {
            Appointment* current = appointments;
            while (current->next)
                current = current->next;
            current->next = newAppt;
        }

        saveAppointments();
        cout << "Appointment booked.\n";
    }

    void listPatients() {
        if (!patients) {
            cout << "No patients registered.\n";
            return;
        }

        cout << "ID    Name                 Condition\n";
        cout << "--------------------------------------\n";
        Patient* current = patients;
        while (current) {
            cout << left << setw(6) << current->id
                 << setw(21) << current->name
                 << current->condition << "\n";
            current = current->next;
        }
    }

    void listDoctors() {
        if (!doctors) {
            cout << "No doctors registered.\n";
            return;
        }

        cout << "ID    Name                 Specialty\n";
        cout << "--------------------------------------\n";
        Doctor* current = doctors;
        while (current) {
            cout << left << setw(6) << current->id
                 << setw(21) << current->name
                 << current->specialty << "\n";
            current = current->next;
        }
    }

    void listAppointments() {
        if (!appointments) {
            cout << "No appointments booked.\n";
            return;
        }

        cout << "Patient ID  Doctor ID  Date\n";
        cout << "-------------------------------\n";
        Appointment* current = appointments;
        while (current) {
            cout << left << setw(12) << current->patient_id
                 << setw(11) << current->doctor_id
                 << current->date << "\n";
            current = current->next;
        }
    }
};

// Example usage
int main() {
    HospitalManager hm("patients.csv", "doctors.csv", "appointments.csv");

    int choice;
    while (true) {
        cout << "\n========= Hospital Management System =========\n";
        cout << "1. Add Patient\n";
        cout << "2. Add Doctor\n";
        cout << "3. Book Appointment\n";
        cout << "4. List Patients\n";
        cout << "5. List Doctors\n";
        cout << "6. List Appointments\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // clear error flag
            cin.ignore(10000, '\n'); // discard input
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 1) {
            int id;
            string name, condition;
            cout << "Enter patient ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter patient name: ";
            getline(cin, name);
            cout << "Enter condition: ";
            getline(cin, condition);
            hm.addPatient(id, name, condition);

        } else if (choice == 2) {
            int id;
            string name, specialty;
            cout << "Enter doctor ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter doctor name: ";
            getline(cin, name);
            cout << "Enter specialty: ";
            getline(cin, specialty);
            hm.addDoctor(id, name, specialty);

        } else if (choice == 3) {
            int pid, did;
            string date;
            cout << "Enter patient ID: ";
            cin >> pid;
            cout << "Enter doctor ID: ";
            cin >> did;
            cin.ignore();
            cout << "Enter date (YYYY-MM-DD): ";
            getline(cin, date);
            hm.bookAppointment(pid, did, date);

        } else if (choice == 4) {
            hm.listPatients();

        } else if (choice == 5) {
            hm.listDoctors();

        } else if (choice == 6) {
            hm.listAppointments();

        } else if (choice == 7) {
            cout << "Exiting program...\n";
            break;

        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
