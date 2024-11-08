#pragma once

#include "User.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
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

    std::string hashPassword(const std::string& password); // Funkcja hashowania has³a

public:
    RegistrationStatus registerUser(const std::string& username, const std::string& password);
    User* loginUser(const std::string& username, const std::string& password);
    std::string addNewTask(int userId, int categoryId, std::string name, std::string description, int priority);
};

