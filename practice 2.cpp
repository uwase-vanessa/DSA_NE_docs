#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "utils.cpp"

using namespace std;

// Function to display menu
void printHelp()
{
    cout << "Menu:\n";
    cout << "1. Register a Patient\n";
    cout << "2. Register a Doctor\n";
    cout << "3. Register an appointment\n";
    cout << "4. Display Patients\n";
    cout << "5. Display Doctors\n";
    cout << "6. Display Appointments\n";
    cout << "7. Exit\n";
}

int main()
{

    // Give user a welcome message
    cout << "=============================================================" << endl;
    cout << "**********=   WELCOME TO OUR HEALTH CARE SYSTEM     =********" << endl;
    cout << "**********=      RUHENGERI REFFERAL HOSPITAL        =********" << endl;
    cout << "**********=   Developed by Precieux Mugisha - RCA   =********" << endl;
    cout << "=============================================================" << endl;

    // Initialize the linked lists
    struct Patient *patientsHead = NULL;
    struct Doctor *doctorsHead = NULL;
    struct Appointment *appointmentsHead = NULL;

    string choice;

    // Run program until exit(7) is input
    while (true)
    {
        printHelp();
        cout << "Enter your choice: ";
        getline(cin, choice);

        if (choice == "1")
        {
        startPatientRegistration:

            int id;
            string name;
            string dob;
            string gender;

            cout << "PATIENT REGISTRATION" << endl;
            cout << "___________________________" << endl;
            cout << "ID: ";
            cin >> id;
            cin.ignore();
            cout << "NAME: ";
            getline(cin, name);
            cout << "DoB: ";
            cin >> dob;
            cout << "GENDER: ";
            cin >> gender;

            if (!validatePatientRegistration(id, dob, patientsHead))
            {
                cout << "Re-enter your patient info" << endl;
                cout << "==============================" << endl;
                goto startPatientRegistration;
            }

            addPatient(&patientsHead, id, name, dob, gender);

            cout << "==============================" << endl;
            cout << "Patient registered successfully" << endl;
            cin.ignore();
        }
        else if (choice == "2")
        {
        startDoctorRegistration:

            int id;
            string name;
            string specialization;

            cout << "DOCTOR REGISTRATION" << endl;
            cout << "___________________________" << endl;
            cout << "ID: ";
            cin >> id;
            cin.ignore();
            cout << "NAME: ";
            getline(cin, name);
            cout << "SPECIALIZATION: ";
            cin >> specialization;

            if (!validateDoctorRegistration(id, doctorsHead))
            {
                cout << "Re-enter your doctor info" << endl;
                cout << "==============================" << endl;
                goto startDoctorRegistration;
            }

            addDoctor(&doctorsHead, id, name, specialization);

            cout << "==============================" << endl;
            cout << "Doctor registered successfully" << endl;
            cin.ignore();
        }

        else if (choice == "3")
        {
        startAppointmentRegistration:

            int id;
            int patientId;
            int doctorId;
            string appointmentDate;

            cout << "APPOINTMENT REGISTRATION" << endl;
            cout << "___________________________" << endl;
            cout << "ID: ";
            cin >> id;
            cin.ignore();
            cout << "P_ID: ";
            cin >> patientId;
            cout << "D_ID: ";
            cin >> doctorId;
            cout << "DATE: ";
            cin >> appointmentDate;

            if (!validateAppointmentRegistration(id, patientId, doctorId, appointmentDate, patientsHead, doctorsHead, appointmentsHead))
            {
                cout << "Re-enter your appointment data" << endl;
                cout << "==============================" << endl;
                goto startAppointmentRegistration;
            }

            addAppointment(&appointmentsHead, id, doctorId, patientId, appointmentDate);

            cout << "Appointment registered successfully" << endl;
            cin.ignore();
        }
        else if (choice == "4")
        {
            displayPatients(patientsHead);
        }
        else if (choice == "5")
        {
            displayDoctors(doctorsHead);
        }
        else if (choice == "6")
        {
            displayAppointments(appointmentsHead);
        }
        else if (choice == "7")
        {
            break;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
