#pragma once

#include "User.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <sqlite3.h>

enum class RegistrationStatus {
    Success,
    UsernameAlreadyExists,
    EmptyUsernameOrPassword,
    DatabaseError
};

class DatabaseManager{
public:
    DatabaseManager();
    ~DatabaseManager();

private:
    sqlite3* db;

    bool openDatabase();
    void closeDatabase();

    void createUsersTable();
    void createTaskTable();
    void createCategoriesTable();

    std::string hashPassword(const std::string& password);

    void createDefaultCat(int userId);

public:
    RegistrationStatus registerUser(const std::string& username, const std::string& password);
    User* loginUser(const std::string& username, const std::string& password);
    
    void getCategories(std::vector<std::string>& categories, int userId);

    std::string addNewTask(int userId, int categoryId, std::string name, std::string description, int priority);
    bool modifyTask();
    bool markAsDone(int taskId);
};

