#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
public:
    // Enum to represent the status of a task.
    enum class Status {
        Pending,
        InProgress,
        Completed
    };

    // Default constructor.
    Task();

    // Constructor to create a new task.
    Task(int id, const std::string& description, Status status = Status::Pending);

    // Getters for task properties.
    int getId() const;
    const std::string& getDescription() const;
    Status getStatus() const;

    // Setters for task properties.
    void setDescription(const std::string& description);
    void setStatus(Status status);

    // Helper function to convert a Status enum to a string.
    static std::string statusToString(Status status);

private:
    int id;
    std::string description;
    Status status;
};

#endif // TASK_H