#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// --------- PATIENT CLASS ---------
class Patient {
public:
	string patientID, name, dob, gender;
	Patient* next;
	Patient(string id, string n, string d, string g) : patientID(id), name(n), dob(d), gender(g), next(NULL) {}
};

class PatientList {
private:
	Patient* head;
public:
	PatientList() : head(NULL) {}

	void registerPatient() {
		string id, name, dob, gender;
		cout << "Enter Patient ID: "; cin >> id;
		cout << "Enter Name: "; cin >> name;
		cout << "Enter DOB: "; cin >> dob;
		cout << "Enter Gender: "; cin >> gender;
		Patient* newPatient = new Patient(id, name, dob, gender);
		newPatient->next = head;
		head = newPatient;

		ofstream out("patients.csv", ios::app);
		out << id << "," << name << "," << dob << "," << gender << "\n";
		out.close();
		cout << "Patient registered and saved.\n";
	}

	void displayPatients() {
		Patient* current = head;
		while (current) {
			cout << "ID: " << current->patientID << ", Name: " << current->name << ", DOB: " << current->dob << ", Gender: " << current->gender << endl;
			current = current->next;
		}
	}

	void displayFromCSV() {
		ifstream inFile("patients.csv");
		string line;
		cout << "\nPATIENTS FROM FILE:\n";
		while (getline(inFile, line)) {
			stringstream ss(line);
			string id, name, dob, gender;
			getline(ss, id, ','); getline(ss, name, ','); getline(ss, dob, ','); getline(ss, gender, ',');
			cout << "ID: " << id << ", Name: " << name << ", DOB: " << dob << ", Gender: " << gender << endl;
		}
		inFile.close();
	}
};

// --------- DOCTOR CLASS ---------
class Doctor {
public:
	string doctorID, name, specialization;
	Doctor* next;
	Doctor(string id, string n, string s) : doctorID(id), name(n), specialization(s), next(NULL) {}
};

class DoctorList {
private:
	Doctor* head;
public:
	DoctorList() : head(NULL) {}

	void registerDoctor() {
		string id, name, spec;
		cout << "Enter Doctor ID: "; cin >> id;
		cout << "Enter Name: "; cin >> name;
		cout << "Enter Specialization: "; cin >> spec;
		Doctor* newDoctor = new Doctor(id, name, spec);
		newDoctor->next = head;
		head = newDoctor;

		ofstream out("doctors.csv", ios::app);
		out << id << "," << name << "," << spec << "\n";
		out.close();
		cout << "Doctor registered and saved.\n";
	}

	void displayDoctors() {
		Doctor* current = head;
		while (current) {
			cout << "ID: " << current->doctorID << ", Name: " << current->name << ", Specialization: " << current->specialization << endl;
			current = current->next;
		}
	}

	void displayFromCSV() {
		ifstream inFile("doctors.csv");
		string line;
		cout << "\nDOCTORS FROM FILE:\n";
		while (getline(inFile, line)) {
			stringstream ss(line);
			string id, name, spec;
			getline(ss, id, ','); getline(ss, name, ','); getline(ss, spec, ',');
			cout << "ID: " << id << ", Name: " << name << ", Specialization: " << spec << endl;
		}
		inFile.close();
	}
};

// --------- APPOINTMENT CLASS ---------
class Appointment {
public:
	string appointmentID, patientID, doctorID, date;
	Appointment* next;
	Appointment(string id, string pID, string dID, string dt) : appointmentID(id), patientID(pID), doctorID(dID), date(dt), next(NULL) {}
};

class AppointmentList {
private:
	Appointment* head;
public:
	AppointmentList() : head(NULL) {}

	void registerAppointment() {
		string id, pid, did, date;
		cout << "Enter Appointment ID: "; cin >> id;
		cout << "Enter Patient ID: "; cin >> pid;
		cout << "Enter Doctor ID: "; cin >> did;
		cout << "Enter Date: "; cin >> date;
		Appointment* newAppointment = new Appointment(id, pid, did, date);
		newAppointment->next = head;
		head = newAppointment;

		ofstream out("appointments.csv", ios::app);
		out << id << "," << pid << "," << did << "," << date << "\n";
		out.close();
		cout << "Appointment registered and saved.\n";
	}

	void displayAppointments() {
		Appointment* current = head;
		while (current) {
			cout << "ID: " << current->appointmentID << ", Patient ID: " << current->patientID << ", Doctor ID: " << current->doctorID << ", Date: " << current->date << endl;
			current = current->next;
		}
	}

	void displayFromCSV() {
		ifstream inFile("appointments.csv");
		string line;
		cout << "\nAPPOINTMENTS FROM FILE:\n";
		while (getline(inFile, line)) {
			stringstream ss(line);
			string id, pid, did, date;
			getline(ss, id, ','); getline(ss, pid, ','); getline(ss, did, ','); getline(ss, date, ',');
			cout << "ID: " << id << ", Patient ID: " << pid << ", Doctor ID: " << did << ", Date: " << date << endl;
		}
		inFile.close();
	}
};

// --------- MAIN ---------
int main() {
	PatientList patientList;
	DoctorList doctorList;
	AppointmentList appointmentList;
	int choice;
	do {
		cout << "\nHEALTHCARE MANAGEMENT SYSTEM\n";
		cout << "1. Register Patient\n2. Register Doctor\n3. Register Appointment\n";
		cout << "4. Display Patients\n5. Display Doctors\n6. Display Appointments\n0. Exit\n";
		cout << "Enter your choice: "; cin >> choice;
		switch (choice) {
			case 1: patientList.registerPatient(); break;
			case 2: doctorList.registerDoctor(); break;
			case 3: appointmentList.registerAppointment(); break;
			case 4:
				cout << "\n--- In-Memory Data ---\n";
				patientList.displayPatients();
				cout << "\n--- Data From File ---\n";
				patientList.displayFromCSV();
				break;
			case 5:
				cout << "\n--- In-Memory Data ---\n";
				doctorList.displayDoctors();
				cout << "\n--- Data From File ---\n";
				doctorList.displayFromCSV();
				break;
			case 6:
				cout << "\n--- In-Memory Data ---\n";
				appointmentList.displayAppointments();
				cout << "\n--- Data From File ---\n";
				appointmentList.displayFromCSV();
				break;
			case 0: cout << "Exiting...\n"; break;
			default: cout << "Invalid option.\n";
		}
	} while (choice != 0);
	return 0;
}

