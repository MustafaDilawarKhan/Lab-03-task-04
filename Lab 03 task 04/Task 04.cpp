#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Task {
public:
    string description;
    bool completed;
    Task(string desc) : description(desc), completed(false) {}
};

class ToDoList {
    vector<Task*> tasks;
public:
    void addTask(const string& desc) { tasks.push_back(new Task(desc)); }

    void listTasks(bool showCompleted) {
        if (tasks.empty()) {
            cout << "No tasks available." << endl;
        }
        else {
            cout << "Tasks:" << endl;
            for (int i = 0; i < tasks.size(); ++i) {
                if (showCompleted || !tasks[i]->completed) {
                    cout << i + 1 << ". " << tasks[i]->description;
                    if (tasks[i]->completed) cout << " [Completed]";
                    cout << endl;
                }
            }
        }
    }

    void completeTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index]->completed = true;
            cout << "Task marked as completed: " << tasks[index]->description << endl;
        }
        else {
            cout << "Invalid task index." << endl;
        }
    }

    bool hasTasks() const {
        return !tasks.empty();
    }

    ~ToDoList() {
        for (auto& task : tasks)
            delete task;
    }
};

int main() {
    ToDoList myList;
    char choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Add a task" << endl;
        cout << "2. Mark a task as completed" << endl;
        cout << "3. Display all tasks" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1': {
            string taskDescription;
            cout << "Enter task description to add: ";
            cin.ignore();
            getline(cin, taskDescription);
            myList.addTask(taskDescription);
            break;
        }
        case '2': {
            if (myList.hasTasks()) {
                myList.listTasks(false); 
                int taskIndex;
                cout << "Enter the index of task to mark as completed: ";
                cin >> taskIndex;
                myList.completeTask(taskIndex - 1);
            }
            break;
        }
        case '3': {
            cout << "All tasks:" << endl;
            myList.listTasks(true);
            break;
        }
        case '4':
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != '4');

    return 0;
}
