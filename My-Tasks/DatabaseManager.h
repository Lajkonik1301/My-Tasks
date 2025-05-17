#pragma once
#include <string>
#include <vector>
#include "Task.h"
#include "User.h"

class DatabaseManager {
public:
    static DatabaseManager& GetInstance();

    bool RegisterUser(const std::string& login, const std::string& password);
    bool ValidateUser(const std::string& login, const std::string& password);

    bool UpdatePassword(const std::string& login, const std::string& newPassword);
    bool DeleteUser(const std::string& login);

    void AddTask(const std::string& login, const std::string& name, const std::string& description);
    void DeleteTask(const std::string& login, int index);
    void MarkTaskDone(const std::string& login, int index);
    void UpdateTaskStatus(const std::string& login, int index, int status);
    void UpdateTask(const std::string& login, int index, const std::string& name, const std::string& description);

    std::vector<Task> GetTasks(const std::string& login);

private:
    DatabaseManager();
    void Init();

    std::string dbPath;
};
