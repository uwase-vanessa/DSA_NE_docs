#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Linked List to store patients and reference to the next one in the linked list
struct Patient
{

    int patient_id;
    string name;
    string dob;
    string gender;

    struct Patient *next; // Pointer to the next patient
};

// Linked List to store doctors and reference to the next one in the linked list
struct Doctor
{
    int doctor_id;
    string name;
    string specialization;

    struct Doctor *next; // Pointer to the next doctor
};

// Linked List to store appointments and reference to the next one in the linked list
struct Appointment
{
    int appointment_id;
    int patient_id;
    int doctor_id;
    string appointment_date;

    struct Appointment *next; // Pointer to the next appointment
};
