#include "TaskManager.h"
#include <iostream>
#include <limits>

using namespace std;

// Function declarations (consistent const usage.)
void addTask(TaskManager& manager);
void viewTasks(TaskManager& manager);
void completeTask(TaskManager& manager);
void updateTask(TaskManager& manager);

int main(){
    TaskManager manager;
    int choice;


    while(true){
        cout << "\nTask Manager Menu \n1. Add Task \n2.View Tasks. \n3.Complete Task \n4.Update Task \n5.Exit \n Choose an option";

        if(!(cin >> choice)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number (1-5)." << endl;
            continue;
        }

        switch(choice){
            case 1: addTask(manager); break;
            case 2: viewTasks(manager); break;
            case 3: completeTask(manager); break;
            case 4: updateTask(manager); break;
            case 5: cout << "Exiting the program." << endl; return 0;
            default: cout << "Invalid option please choose between (1-5)";
        }
    }
}


void addTask(TaskManager& manager){
    string name, dueDate;
    int priority;

    cout << "Enter the new task name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);


    cout << "Enter the new task dueDate: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, dueDate);
    
    cout << "Enter the task priority: ";
    while(!(cin >> priority)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid priority, please  enter a number: ";
    }

    manager.addTask(name, dueDate, priority);
}

void viewTasks(TaskManager& manager){
    manager.displayTasks();
}


void completeTask(TaskManager& manager){
    int index;

    cout << "Enter the index of the task you want to update:  ";
    while(!(cin >> index)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid index, please enter a number";
    }

    manager.completeTask(index);

}

void updateTask(TaskManager& manager){
    int index;
    string name, dueDate;
    int priority;

    cout << "Enter the index of the task you want to update: ";
    while(!(cin >> index)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input, please enter a number"<< endl;
    }

    cout << "Enter a new task name: ";
    // it's a must that we have to clear the input buffer after like handling a cin operation due to it leaves an empty line.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    cout << "Enter the new due date for the task: ";
    getline(cin, dueDate);

    cout << "Enter the new priority you wish for the task";
    while(!(cin >> priority)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input, please enter a number" << endl;
    }

    manager.updateTask(index, {name, dueDate, priority});
}

