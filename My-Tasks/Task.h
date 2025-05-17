#pragma once
#include <string>

class Task {
public:
    Task(int id, const std::string& name, const std::string& description, bool status);

    int getId() const;
    const std::string& getName() const;
    const std::string& getDescription() const;
    bool isDone() const;

    void markDone();

private:
    int id;
    std::string name;
    std::string description;
    bool status;
};
