#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;
// Struct to represent the patient linked list
struct PatientsLL {
	int patient_id;
	string name;
	string dob;
	string gender;
	PatientsLL* next;
	//constructor
	PatientsLL(int patientId, string patientName, string patientDob, string patientGender) : patient_id(patientId), name(patientName), dob(patientDob), gender(patientGender),next(nullptr) {}
};

// Struct to represent the doctor linked list
struct DoctorsLL {
	int doctor_id;
	string name;
	string specialization;
	DoctorsLL* next;
	//constructor
	DoctorsLL(int doctorId, string doctorName, string doctorSpecialization): doctor_id(doctorId), name(doctorName), specialization(doctorSpecialization), next(nullptr) {}
};

// Struct to represent the appointment linked list
struct AppointmentsLL {
	int appointment_id;
	int patient_id;
	int doctor_id;
	string appointment_date;
	AppointmentsLL* next;

	//constructor
	AppointmentsLL(int apId, int pId, int docId, string apDate): appointment_id(apId), patient_id(pId), doctor_id(docId), appointment_date(apDate) {}

};

//Class to manage a list of patients
class PatientList {
	private:
		PatientsLL* head;

	public:
		int count=0;
		// Constructor
		PatientList() : head(nullptr) {}

		// Method to add a new patient
		void addPatient(int id, string name, string dob, string gender) {
			count++;
			PatientsLL* newPatient = new PatientsLL(id, name, dob, gender);
			newPatient->next = head;
			head = newPatient;
		}
		// Method to find a patient by ID
		PatientsLL* findPatient(int id) {
			PatientsLL* current = head;
			while (current != nullptr) {
				if (current->patient_id == id)
					return current;
				current = current->next;
			}
			return nullptr;
		}

		//Method to check if there are any patients in the list
		bool isPatientEmpty() {
			if(count==0) {
				return true;
			}
			return false;

		}
		// Method to display all patients
		void displayPatients() {
			if(isPatientEmpty()) {
				cout<<"There are no patients registered yet"<<endl;
				return;
			}
			PatientsLL* current = head;
			while (current != nullptr) {
				cout << "Patient ID: " << current->patient_id << ", Name: " << current->name << ", DOB: " << current->dob <<", Gender: " << current->gender;
				cout << endl;
				current = current->next;
			}
		}


		// Getter for the head of the patient list
		PatientsLL* getHead() const {
			return head;
		}
};



// Class to manage a list of doctors
class DoctorList {
	private:
		DoctorsLL* head;

	public:
		int count=0;
		// Constructor
		DoctorList() : head(nullptr) {}

		// Method to add a new doctor
		void addDoctor(int id, string name, string specialization) {
			count++;
			DoctorsLL* newDoctor = new DoctorsLL(id, name, specialization);
			newDoctor->next = head;
			head = newDoctor;
		}
		// Method to find a doctor by ID
		DoctorsLL* findDoctor(int id) {
			DoctorsLL* current = head;
			while (current != nullptr) {
				if (current->doctor_id == id)
					return current;
				current = current->next;
			}
			return nullptr;
		}

		// Method to chech whether they are any doctors in the list
		bool isDoctorEmpty() {
			if(count==0) {
				return true;
			}
			return false;

		}
		// Method to display all doctors
		void displayDoctors() {
			if(isDoctorEmpty()) {
				cout<<"There are no doctors registered yet"<<endl;
				return;
			}
			DoctorsLL* current = head;
			while (current != nullptr) {
				cout << "Doctor ID: " << current->doctor_id << ", Name: " << current->name << ", Specialization: " << current->specialization;
				cout << endl;
				current = current->next;
			}
		}


		// Getter for the head of the doctor list
		DoctorsLL* getHead() const {
			return head;
		}
};


//class to manage a list of appointments

class AppointmentList {
	private:
		AppointmentsLL* head;

	public:
		int count=0;
		// Constructor
		AppointmentList() : head(nullptr) {}

		// Method to add a new doctor
		void addAppointment(int id, int patId, int docId, string date) {
			count++;
			AppointmentsLL* newAppointment = new AppointmentsLL(id, patId, docId, date);
			newAppointment->next = head;
			head = newAppointment;
		}
		// Method to find an appointment by ID
		AppointmentsLL* findAppointment(int id) {
			AppointmentsLL* current = head;
			while (current != nullptr) {
				if (current->appointment_id == id)
					return current;
				current = current->next;
			}
			return nullptr;
		}

		// Method to chech whether they are any appointments in the list
		bool isAppointmentEmpty() {
			if(count==0) {
				return true;
			}
			return false;

		}
		// Method to display all the appointments
		void displayAppointments() {
			if(isAppointmentEmpty()) {
				cout<<"There are no appointments registered yet"<<endl;
				return;
			}
			AppointmentsLL* current = head;
			while (current != nullptr) {
				cout << "Appointment ID: " << current->appointment_id << ", Patient ID: " <<current->patient_id << ", Doctor ID: "<<current->doctor_id << ", Date: " << current->appointment_date ;
				cout << endl;
				current = current->next;
			}
		}


		// Getter for the head of the appointment list
		AppointmentsLL* getHead() const {
			return head;
		}
};

bool isDoctorIdExists(const DoctorList& doctorList, int id) {
	DoctorsLL* current = doctorList.getHead();
	while (current != nullptr) {
		if (current->doctor_id == id)
			return true;
		current = current->next;
	}
	return false;
}

bool isPatientIdExists(const PatientList& patientList, int id) {
	PatientsLL* current = patientList.getHead();
	while (current != nullptr) {
		if (current->patient_id == id)
			return true;
		current = current->next;
	}
	return false;
}

bool isAppointmentIdExists(const AppointmentList& appointmentList, int id) {
	AppointmentsLL* current = appointmentList.getHead();
	while (current != nullptr) {
		if (current->appointment_id == id)
			return true;
		current = current->next;
	}
	return false;
}
// Function to validate integer input from user
bool isValidIntegerInput() {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
	return true;
}

// Function to validate non-empty string input from user
bool isValidStringInput(const string& input) {
	return !input.empty() && !all_of(input.begin(), input.end(), ::isspace);
}
//Function to validate date input
bool isValidDate(const std::string& dateStr) {
	std::stringstream ss(dateStr);
	int year, month, day;
	char delimiter;

	// Check for valid format (DD/MM/YYYY or YYYY-MM-DD)
	if (dateStr.find('/') != std::string::npos) {
		if (ss >> day >> delimiter >> month >> delimiter >> year) {
			// Further validation for day, month, and year range
		} else {
			return false;
		}
	} else if (ss >> year >> delimiter >> month >> delimiter >> day) {
		// Further validation for day, month, and year range
	} else {
		return false;
	}

	// Additional checks for leap years, month lengths, etc.

	return true;
}

// Function to convert the inputted string into lowercase
string toLower(const string& str) {
	string lowercaseStr = str;
	transform(lowercaseStr.begin(), lowercaseStr.end(), lowercaseStr.begin(), ::tolower);
	return lowercaseStr;
}

// Function to display the welcome message
void displayWelcomeMessage() {
	cout << "                              Welcome to HEALTHCARE MANAGEMENT SYSTEM!                            " << endl;
	cout << "                           ***********************************************                        " << endl;

}
int main() {
	DoctorList doctorList;
	PatientList patientList;
	AppointmentList appointmentList;
	displayWelcomeMessage();
	int choice;
	do {
		cout << "Menu:"<<endl;
		cout << "1. Register a Patient\n";
		cout << "2. Register a Doctor\n";
		cout << "3. Register an Appointment\n";
		cout << "4. Display Patients\n";
		cout << "5. Display Doctors\n";
		cout << "6. Display Appointments\n";
		cout << "7. Exit\n";
in:
		cout << "Enter your choice: ";
		cin >> choice;

		if (!isValidIntegerInput()) {
			cout << "Invalid input. Please enter an integer between 1 and 7.\n";
			goto in;
		}

//  Switching between options chosen

		switch (choice) {
			case 1: {
				int id;
				string name;
				string dob;
				string gender;
				cout<<"PATIENT REGISTRATION \n";
				cout<<"-------------------------"<<endl;
patId:
				cout << "ID: ";
				cin>>id;
				if (!isValidIntegerInput() || id <= 0) {
					cout << "Invalid patient id. Please enter a positive integer.\n";
					goto patId;
				} else if (isPatientIdExists(patientList, id)) {
					cout << "The ID has already been used. Please enter another one.\n";
					goto patId;
				}

patientName:
				cout<<"NAME: ";
				cin.ignore();
				getline(cin, name);

				if (!isValidStringInput(name)) {
					cout << "Invalid patient name. Please enter a non-empty name.\n";
					goto patientName;
				}

patientDOB:
				cout<<"DoB: ";
				getline(cin,dob);
				if (!isValidStringInput(dob)) {
					cout << "Invalid date. Please enter a non-empty date.\n";
					goto patientDOB;
				} else if(!isValidDate(dob)) {
					cout<<"Invalid date. The date should be in DD/MM/YYYY or YYYY-MM-DD format. \n";

					goto patientDOB;
				}

patientGender:
				cout<<"GENDER: ";

				cin>>gender;
				if(!isValidStringInput(gender) ) {
					cout<< "Invalid gender. Please enter a valid gender \n";
					goto patientGender;
				} else if(toLower(gender)!="male" && toLower(gender)!="female" && toLower(gender)!="f" && toLower(gender)!="m") {
					cout<< "Invalid gender. Please enter a valid gender \n";
					goto patientGender;
				}
				patientList.addPatient(id, name,dob,gender);

				break;
			}
			case 2: {
				int id;
				string name;
				string specialization;
				cout<<"DOCTOR REGISTRATION \n";
				cout<<"-------------------------"<<endl;

doctorId:
				cout << "ID: ";
				cin>>id;
				if (!isValidIntegerInput() || id <= 0) {
					cout << "Invalid doctor id. Please enter a positive integer.\n";
					goto doctorId;
				} else if (isDoctorIdExists(doctorList, id)) {
					cout << "The ID has already been used. Please enter another one.\n";
					goto doctorId;
				}

doctorName:
				cout<<"NAME: ";
				cin.ignore();
				getline(cin, name);

				if (!isValidStringInput(name)) {
					cout << "Invalid doctor name. Please enter a non-empty name.\n";
					goto doctorName;
				}
doctorSpec:
				cout<<"SPECIALIZATION: ";
				getline(cin, specialization);
				if (!isValidStringInput(specialization)) {
					cout << "Invalid doctor specialization. Please enter a non-empty specialization.\n";
					goto doctorSpec;
				}

				doctorList.addDoctor(id, name, specialization);

				break;

			}
			case 3: {
				int id;
				int patient_id;
				int doctor_id;
				string date;
				cout<<"APPOINTMENT REGISTRATION \n"
				    ;
				cout<<"-------------------------"<<endl;

appointmentId:
				cout << "ID: ";
				cin>>id;
				if (!isValidIntegerInput() || id <= 0) {
					cout << "Invalid appointment id. Please enter a positive integer.\n";
					goto appointmentId;
				} else if (isAppointmentIdExists(appointmentList, id)) {
					cout << "The ID has already been used. Please enter another one.\n";
					goto appointmentId;
				}

appointPatientId:
				cout<<"P_ID: ";
				cin>>patient_id;
				if (!isValidIntegerInput() || id <= 0) {
					cout << "Invalid patient id. Please enter a positive integer.\n";
					goto appointPatientId;
				} else if (!isPatientIdExists(patientList, patient_id)) {
					if(patientList.isPatientEmpty()) {
						cout<<"There are no patients registered yet"<<endl;
						break;
					}
					cout << "That patient ID does not exist. Please enter another one.\n";
					goto appointPatientId;
				}

appointDoctorId:
				cout<< "D_ID: ";
				cin>>doctor_id;
				if (!isValidIntegerInput() || id <= 0) {
					cout << "Invalid doctor id. Please enter a positive integer.\n";
					goto appointPatientId;
				} else if (!isDoctorIdExists(doctorList, doctor_id)) {
					if(doctorList.isDoctorEmpty()) {
						cout<<"There are no doctors registered yet"<<endl;
						break;
					}
					cout << "That doctor ID does not exist. Please enter another one.\n";
					goto appointDoctorId;
				}

appointmentDate:
				cout<<"DATE: ";
				cin>>date;
				if (!isValidStringInput(date)) {
					cout << "Invalid date. Please enter a non-empty date.\n";
					goto appointmentDate;
				} else if (!isValidDate(date)) {
					cout << "Invalid date. The date should be in DD/MM/YYYY or YYYY-MM-DD format.\n";
					goto appointmentDate;
				}

				appointmentList.addAppointment(id, patient_id, doctor_id, date);

				break;

			}
			case 4:
				patientList.displayPatients();
				break;
			case 5:
				doctorList.displayDoctors();
				break;
			case 6:
				appointmentList.displayAppointments();
				break;
			case 7:
				cout << "Thank you for using our system" << endl;
				cout << "Exiting.............."<<endl;
				break;
			default:
				cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 7);

	return 0;
}


