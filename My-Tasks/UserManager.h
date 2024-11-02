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

class UserManager {
private:
    sqlite3* db;

    bool openDatabase();
    void closeDatabase();

    std::string hashPassword(const std::string& password); // Funkcja hashowania has³a

public:
    UserManager();
    ~UserManager();

    RegistrationStatus registerUser(const std::string& username, const std::string& password);
    User* loginUser(const std::string& username, const std::string& password);
};