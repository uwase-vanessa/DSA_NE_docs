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
    string condition; // e.g., "Fever"
    Patient* next;
};

// Structure for Doctor
struct Doctor {
    int id;
    string name;
    string specialty; // e.g., "Cardiology"
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
    Patient* patients;      // Linked list for patients
    Doctor* doctors;       // Linked list for doctors
    Appointment* appointments; // Linked list for appointments
    string csv_patients;   // CSV file for patients
    string csv_doctors;    // CSV file for doctors
    string csv_appointments; // CSV file for appointments

    // Convert string to lowercase for search
    string toLower(string str) {
        for (char &c : str)
            c = tolower(c);
        return str;
    }

    // Load patients from CSV
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
                Patient* newPatient = new Patient;
                newPatient->id = stoi(tokens[0]);
                newPatient->name = tokens[1];
                newPatient->condition = tokens[2];
                newPatient->next = nullptr;

                // Insert sorted by name
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

    // Load doctors from CSV
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
                Doctor* newDoctor = new Doctor;
                newDoctor->id = stoi(tokens[0]);
                newDoctor->name = tokens[1];
                newDoctor->specialty = tokens[2];
                newDoctor->next = nullptr;

                // Insert sorted by name
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

    // Load appointments from CSV
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
                Appointment* newAppt = new Appointment;
                newAppt->patient_id = stoi(tokens[0]);
                newAppt->doctor_id = stoi(tokens[1]);
                newAppt->date = tokens[2];
                newAppt->next = nullptr;

                // Insert at end
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

    // Save patients to CSV
    void savePatients() {
        ofstream file(csv_patients);
        Patient* current = patients;
        while (current) {
            file << current->id << "," << current->name << "," << current->condition << "\n";
            current = current->next;
        }
        file.close();
    }

    // Save doctors to CSV
    void saveDoctors() {
        ofstream file(csv_doctors);
        Doctor* current = doctors;
        while (current) {
            file << current->id << "," << current->name << "," << current->specialty << "\n";
            current = current->next;
        }
        file.close();
    }

    // Save appointments to CSV
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

    // Add a patient
    void addPatient() {
        int id;
        string name, condition;
        cout << "Enter patient ID: ";
        cin >> id;
        cin.ignore(); // Clear newline
        cout << "Enter patient name: ";
        getline(cin, name);
        cout << "Enter patient condition: ";
        getline(cin, condition);

        Patient* newPatient = new Patient;
        newPatient->id = id;
        newPatient->name = name;
        newPatient->condition = condition;
        newPatient->next = nullptr;

        // Insert sorted by name
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

    // Add a doctor
    void addDoctor() {
        int id;
        string name, specialty;
        cout << "Enter doctor ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter doctor name: ";
        getline(cin, name);
        cout << "Enter doctor specialty: ";
        getline(cin, specialty);

        Doctor* newDoctor = new Doctor;
        newDoctor->id = id;
        newDoctor->name = name;
        newDoctor->specialty = specialty;
        newDoctor->next = nullptr;

        // Insert sorted by name
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

    // Book an appointment
    void bookAppointment() {
        int patient_id, doctor_id;
        string date;
        cout << "Enter patient ID: ";
        cin >> patient_id;
        cout << "Enter doctor ID: ";
        cin >> doctor_id;
        cin.ignore();
        cout << "Enter appointment date: ";
        getline(cin, date);

        // Check if patient and doctor exist
        Patient* p = patients;
        bool patient_exists = false;
        while (p) {
            if (p->id == patient_id) {
                patient_exists = true;
                break;
            }
            p = p->next;
        }

        Doctor* d = doctors;
        bool doctor_exists = false;
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

        Appointment* newAppt = new Appointment;
        newAppt->patient_id = patient_id;
        newAppt->doctor_id = doctor_id;
        newAppt->date = date;
        newAppt->next = nullptr;

        // Insert at end
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

    // List all patients
    void listPatients() {
        if (!patients) {
            cout << "No patients registered.\n";
            return;
        }

        cout << "ID    Name                 Condition\n";
        cout << "--------------------------------\n";
        Patient* current = patients;
        while (current) {
            cout << left << setw(6) << current->id
                 << setw(21) << current->name
                 << current->condition << "\n";
            current = current->next;
        }
    }

    // List all doctors
    void listDoctors() {
        if (!doctors) {
            cout << "No doctors registered.\n";
            return;
        }

        cout << "ID    Name                 Specialty\n";
        cout << "--------------------------------\n";
        Doctor* current = doctors;
        while (current) {
            cout << left << setw(6) << current->id
                 << setw(21) << current->name
                 << current->specialty << "\n";
            current = current->next;
        }
    }

    // List all appointments
    void listAppointments() {
        if (!appointments) {
            cout << "No appointments booked.\n";
            return;
        }

        cout << "Patient ID  Doctor ID  Date\n";
        cout << "----------------------------\n";
        Appointment* current = appointments;
        while (current) {
            cout << left << setw(12) << current->patient_id
                 << setw(11) << current->doctor_id
                 << current->date << "\n";
            current = current->next;
        }
    }

    // Search patients by name
    void searchPatients() {
        string query;
        cout << "Enter patient name to search: ";
        cin.ignore();
        getline(cin, query);
        query = toLower(query);

        Patient* current = patients;
        bool found = false;

        cout << "ID    Name                 Condition\n";
        cout << "--------------------------------\n";
        while (current) {
            if (toLower(current->name).find(query) != string::npos) {
               music cout << left << setw(6) << current->id
                     << setw(21) << current->name
                     << current->condition << "\n";
                found = true;
            }
            current = current->next;
        }
        if (!found)
            cout << "No patients match '" << query << "'.\n";
    }

    // Delete a patient
    void deletePatient() {
        int id;
        cout << "Enter patient ID to delete: ";
        cin >> id;

        if (!patients) {
            cout << "No patients to delete.\n";
            return;
        }

        if (patients->id == id) {
            Patient* temp = patients;
            patients = patients->next;
            delete temp;
            savePatients();
            cout << "Patient deleted.\n";
            return;
        }

        Patient* current = patients;
        while (current->next && current->next->id != id)
            current = current->next;

        if (current->next) {
            Patient* temp = current->next;
            current->next = temp->next;
            delete temp;
            savePatients();
            cout << "Patient deleted.\n";
        } else {
            cout << "Patient ID not found.\n";
        }
    }

    // Show menu
    void showMenu() {
        cout << "\nHospital Management System\n"
             << "1. Add Patient\n"
             << "2. Add Doctor\n"
             << "3. Book Appointment\n"
             << "4. List Patients\n"
             << "5. List Doctors\n"
             << "6. List Appointments\n"
             << "7. Search Patients\n"
             << "8. Delete Patient\n"
             << "9. Help\n"
             << "10. Exit\n"
             << "Enter choice (1-10): ";
    }
};

// Main program
int main() {
    HospitalManager hospital("patients.csv", "doctors.csv", "appointments.csv");
    int choice;

    cout << "Welcome to Hospital Management System\n";

    while (true) {
        hospital.showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                hospital.addPatient();
                break;
            case 2:
                hospital.addDoctor();
                break;
            case 3:
                hospital.bookAppointment();
                break;
            case 4:
                hospital.listPatients();
                break;
            case 5:
                hospital.listDoctors();
                break;
            case 6:
                hospital.listAppointments();
                break;
            case 7:
                hospital.searchPatients();
                break;
            case 8:
                hospital.deletePatient();
                break;
            case 9:
                hospital.showMenu();
                break;
            case 10:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Enter 1-10.\n";
        }
    }

    return 0;
}