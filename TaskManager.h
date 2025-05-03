#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string name;
    string dueDate;
    int priority;
};

class TaskManager {
    private:
        vector<Task> tasks;

    public:
        void addTask(const string& name, const string& dueDate, int priority){
            tasks.push_back({name, dueDate, priority});
        }

        void displayTasks() const {
            for (const auto& task: tasks){
                cout << "Task Name: " << task.name 
                     << " Task DueDate: " << task.dueDate
                     << " Priority of the task: "  << task.priority
                     << endl; 
            }
        }

        void completeTask(int index){
            if (index >= 0 && index < tasks.size()){
                tasks.erase(tasks.begin() + index);
                cout << "Task Completed and removed from the list." << endl;
            } else {
                cout << "Invalid task index" << endl;
            }
        }

        void updateTask(int index, Task task){
            if (index >= 0 && index < tasks.size()){
                tasks[index] = task;
                cout << "The task was updated successfully" << endl;
            } else {
                cout << "Invalid task index" << endl;
            }
        }
};

#endif
