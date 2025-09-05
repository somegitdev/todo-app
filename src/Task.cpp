#include "Task.h"

// Default constructor.
Task::Task() : id(0), description(""), status(Status::Pending) {}

// Constructor to create a new task.
Task::Task(int id, const std::string& description, Status status)
    : id(id), description(description), status(status) {}

// Getters for task properties.
int Task::getId() const {
    return id;
}

const std::string& Task::getDescription() const {
    return description;
}

Task::Status Task::getStatus() const {
    return status;
}

// Setters for task properties.
void Task::setDescription(const std::string& description) {
    this->description = description;
}

void Task::setStatus(Status status) {
    this->status = status;
}

// Converts a Status enum to a string.
std::string Task::statusToString(Status status) {
    switch (status) {
        case Status::Pending:
            return "Pending";
        case Status::InProgress:
            return "InProgress";
        case Status::Completed:
            return "Completed";
    }
    return "Unknown";
}