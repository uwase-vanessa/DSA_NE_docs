#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

// Forward declaration
class CourseList;

// Define the Course class
class Course {
public:
    string courseName;
    bool available;
    Course* next;

    Course(string name, bool avail) : courseName(name), available(avail), next(nullptr) {}
};

// Define the Student class
class Student {
public:
    string studentName;
    vector<string> courses;
    Student* next;

    Student(string name) : studentName(name), next(nullptr) {}
};

// Define the LinkedList class to manage students
class LinkedList {
private:
    Student* head;

public:
    LinkedList() : head(nullptr) {}
    
    
// function to add students
    void addStudent(string name) {
        Student* newStudent = new Student(name);
        newStudent->next = head;
        head = newStudent;
    }

// Function to find student by name
    Student* findStudent(string name) {
        Student* current = head;
        while (current != nullptr) {
            if (current->studentName == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    
    
// Enroll student in course declaration
    void enrollStudentInCourse(string studentName, string courseName, CourseList& courseList);

//Save information to csv 
    void saveToCSV(string filename) {
        ofstream file(filename);
        file << "Student Name,Course Name\n";
        Student* current = head;
        while (current != nullptr) {
            for (const auto& course : current->courses) {
                file << current->studentName << "," << course << "\n";
            }
            current = current->next;
        }
        file.close();
    }

// Load CSV file data
    void loadFromCSV(string filename) {
        ifstream file(filename);
        string line, studentName, courseName;
        getline(file, line); 

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, studentName, ',');
            getline(ss, courseName, ',');

            Student* student = findStudent(studentName);
            if (student == nullptr) {
                addStudent(studentName);
                student = head;
            }
            student->courses.push_back(courseName);
        }
        file.close();
    }

// Display student list with assigned courses
    void displayList() {
        cout << left << setw(20) << "Student Name" << "Courses\n";
        cout << "--------------------------------------------------\n";
        Student* current = head;
        while (current != nullptr) {
            cout << left << setw(20) << current->studentName;
            for (size_t i = 0; i < current->courses.size(); ++i) {
                if (i > 0) cout << ", ";
                cout << current->courses[i];
            }
            cout << "\n";
            current = current->next;
        }
    }
    
    // Search student

    void searchStudent(string studentName) {
        Student* student = findStudent(studentName);
        if (student == nullptr) {
            cout << "Student not found!\n";
        } else {
            cout << left << setw(20) << "Student Name" << "Courses\n";
            cout << "--------------------------------------------------\n";
            cout << left << setw(20) << student->studentName;
            for (size_t i = 0; i < student->courses.size(); ++i) {
                if (i > 0) cout << ", ";
                cout << student->courses[i];
            }
            cout << "\n";
        }
    }
};

// Define CourseList class
class CourseList {
private:
    Course* head;

public:
    CourseList() : head(nullptr) {}
    
    
// Function to add course
    void addCourse(string name, bool avail) {
        Course* newCourse = new Course(name, avail);
        newCourse->next = head;
        head = newCourse;
    }
    
    
// Function to find course
    Course* findCourse(string name) {
        Course* current = head;
        while (current != nullptr) {
            if (current->courseName == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    
// Display courses 
        void displayCourses() {
        cout << "Courses" ;
        cout << "--------------------------------------------------\n";
        Course* current = head;
      while (current != nullptr) {
            cout << left << setw(20) << current->courseName;
//            for (size_t i = 0; i < current->courses.size(); ++i) {
//                if (i > 0) cout << ", ";
//                cout << current->courses[i];
//            }
            cout << "\n";
            current = current->next;
        }
//        return nullptr;
    }
    
};

//Enroll student function after to avoid circular dependency problem
void LinkedList::enrollStudentInCourse(string studentName, string courseName, CourseList& courseList) {
    Student* student = findStudent(studentName);
    if (student == nullptr) {
        cout << "Student not found!\n";
        return;
    }

    Course* course = courseList.findCourse(courseName);
    if (!course) {
        cout << "Course \"" << courseName << "\" not found!\n";
    } else if (!course->available) {
        cout << "Course \"" << courseName << "\" is not available!\n";
    } else {
        student->courses.push_back(courseName);
        cout << "Student \"" << studentName << "\" enrolled in \"" << courseName << "\".\n";
    }
}

// ------------------------- Main -------------------------

//int main() {
//    LinkedList studentList;
//    CourseList courseList;
//
//    studentList.loadFromCSV("students.csv");
//
//    // Adding predefined courses
//    courseList.addCourse("Math", true);
//    courseList.addCourse("Physics", true);
//    courseList.addCourse("Chemistry", false);
//
//    char option;
//    do {
//        cout << "\nOptions:\n";
//        cout << "1. Display student list\n";
//        cout << "2. Add student\n";
//        cout << "3. Add course\n";
//        cout << "4. Enroll student in course\n";
//        cout << "5. Search for student\n";
//        cout << "6. Display courses list\n";
//        cout << "7. Exit\n";
//        cout << "Choose an option: ";
//        cin >> option;
//
//
//        if (option == '1') {
//            studentList.displayList();
//        
//        } else if (option == '2') {
//            string name;
//            cout << "Enter student name: ";
//            getline(cin, name);
//            studentList.addStudent(name);
//        } else if (option == '3') {
//            string name;
//            bool avail;
//            cout << "Enter course name: ";
//            getline(cin, name);
//            cout << "Is the course available? (1 for true, 0 for false): ";
//            cin >> avail;
//            cin.ignore();
//            courseList.addCourse(name, avail);
//        } else if (option == '4') {
//            string studentName, courseName;
//            cout << "Enter student name: ";
//            getline(cin, studentName);
//            cout << "Enter course name: ";
//            getline(cin, courseName);
//            cin.ignore();
//            studentList.enrollStudentInCourse(studentName, courseName, courseList);            cin.ignore();
//        } else if (option == '5') {
//            string name;
//            cout << "Enter student name to search: ";
//            getline(cin, name);
//            studentList.searchStudent(name);
//        } else if (option == '6') {
//          courseList.displayCourses();
//        }
//
//    } while (option != '7');
//
//    studentList.saveToCSV("students.csv");
//    return 0;
//}


int main() {
    LinkedList studentList;
    CourseList courseList;

    studentList.loadFromCSV("students.csv");

    // Add predefined courses
    courseList.addCourse("Math", true);
    courseList.addCourse("Physics", true);
    courseList.addCourse("Chemistry", false);

    char option;
    do {
        cout << "\nOptions:\n";
        cout << "1. Display student list\n";
        cout << "2. Add student\n";
        cout << "3. Add course\n";
        cout << "4. Enroll student in course\n";
        cout << "5. Search for student\n";
        cout << "6. Display course list\n";
        cout << "7. Exit\n";
        cout << "Choose an option: ";
        cin >> option;
        cin.ignore(); 

        if (option == '1') {
            studentList.displayList();
        } else if (option == '2') {
            string name;
            cout << "Enter student name: ";
            getline(cin, name);
            studentList.addStudent(name);
        } else if (option == '3') {
            string name;
            bool avail;
            cout << "Enter course name: ";
            getline(cin, name);
            cout << "Is the course available? (1 for true, 0 for false): ";
            cin >> avail;
            cin.ignore();
            courseList.addCourse(name, avail);
        } else if (option == '4') {
            string studentName, courseName;
            cout << "Enter student name: ";
            getline(cin, studentName);
            cout << "Enter course name: ";
            getline(cin, courseName);
            studentList.enrollStudentInCourse(studentName, courseName, courseList);
        } else if (option == '5') {
            string name;
            cout << "Enter student name to search: ";
            getline(cin, name);
            studentList.searchStudent(name);
        }else if(option == '6'){
        	courseList.displayCourses();
		}

    } while (option != '7');

    studentList.saveToCSV("students.csv");
    return 0;
}