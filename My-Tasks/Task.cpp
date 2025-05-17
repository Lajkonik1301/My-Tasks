#include "Task.h"

Task::Task(int id, const std::string& name, const std::string& description, bool status)
    : id(id), name(name), description(description), status(status) {}

int Task::getId() const {
    return id;
}

const std::string& Task::getName() const {
    return name;
}

const std::string& Task::getDescription() const {
    return description;
}

bool Task::isDone() const {
    return status;
}

void Task::markDone() {
    status = true;
}
