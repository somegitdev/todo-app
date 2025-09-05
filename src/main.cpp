#include "Task.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

// Function to save tasks to a file.
void saveTasks(const std::vector<Task>& tasks, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& task : tasks) {
            file << task.getId() << "," << task.getDescription() << "," << Task::statusToString(task.getStatus()) << std::endl;
        }
        file.close();
    }
}

// Function to load tasks from a file.
std::vector<Task> loadTasks(const std::string& filename) {
    std::vector<Task> tasks;
    std::ifstream file(filename);
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            // Simple parsing for demonstration.
            size_t firstComma = line.find(',');
            size_t secondComma = line.find(',', firstComma + 1);

            if (firstComma != std::string::npos && secondComma != std::string::npos) {
                try {
                    int id = std::stoi(line.substr(0, firstComma));
                    std::string description = line.substr(firstComma + 1, secondComma - (firstComma + 1));
                    std::string statusStr = line.substr(secondComma + 1);

                    Task::Status status = Task::Status::Pending;
                    if (statusStr == "InProgress") {
                        status = Task::Status::InProgress;
                    } else if (statusStr == "Completed") {
                        status = Task::Status::Completed;
                    }

                    tasks.push_back(Task(id, description, status));
                } catch (...) {
                    // Handle potential errors in parsing.
                }
            }
        }
        file.close();
    }
    return tasks;
}

// Function to get the next available task ID.
int getNextId(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        return 1;
    }
    int maxId = 0;
    for (const auto& task : tasks) {
        if (task.getId() > maxId) {
            maxId = task.getId();
        }
    }
    return maxId + 1;
}

// Function to print all tasks.
void printTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "No tasks found." << std::endl;
        return;
    }
    std::cout << "--- To-Do List ---" << std::endl;
    for (const auto& task : tasks) {
        std::cout << task.getId() << ". [" << Task::statusToString(task.getStatus()) << "] " << task.getDescription() << std::endl;
    }
    std::cout << "------------------" << std::endl;
}

int main() {
    std::string dataPath = "data/tasks.txt";
    std::vector<Task> tasks = loadTasks(dataPath);

    std::cout << "Welcome to the C++ To-Do App!" << std::endl;

    // Main application loop
    while (true) {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Add a new task" << std::endl;
        std::cout << "2. View all tasks" << std::endl;
        std::cout << "3. Mark a task as completed" << std::endl;
        std::cout << "4. Delete a task" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        // Input validation for a cleaner user experience
        while (std::cin.fail() || choice < 1 || choice > 5) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please enter a number between 1 and 5: ";
            std::cin >> choice;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            std::cout << "Enter task description: ";
            std::string description;
            std::getline(std::cin, description);
            int newId = getNextId(tasks);
            tasks.push_back(Task(newId, description));
            saveTasks(tasks, dataPath);
            std::cout << "Task added successfully!" << std::endl;
        } else if (choice == 2) {
            printTasks(tasks);
        } else if (choice == 3) {
            std::cout << "Enter the ID of the task to mark as completed: ";
            int taskId;
            std::cin >> taskId;
            bool found = false;
            for (auto& task : tasks) {
                if (task.getId() == taskId) {
                    task.setStatus(Task::Status::Completed);
                    found = true;
                    break;
                }
            }
            if (found) {
                saveTasks(tasks, dataPath);
                std::cout << "Task " << taskId << " marked as completed." << std::endl;
            } else {
                std::cout << "Task with ID " << taskId << " not found." << std::endl;
            }
        } else if (choice == 4) {
            std::cout << "Enter the ID of the task to delete: ";
            int taskId;
            std::cin >> taskId;

            auto it = tasks.begin();
            bool found = false;
            while (it != tasks.end()) {
                if (it->getId() == taskId) {
                    it = tasks.erase(it);
                    found = true;
                    break;
                } else {
                    ++it;
                }
            }

            if (found) {
                saveTasks(tasks, dataPath);
                std::cout << "Task " << taskId << " deleted successfully." << std::endl;
            } else {
                std::cout << "Task with ID " << taskId << " not found." << std::endl;
            }
        } else if (choice == 5) {
            break;
        }
    }

    return 0;
}