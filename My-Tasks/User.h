#pragma once

#include <string>

class User {
private:
    int id;
    std::string username;
    std::string passwordHash;

public:
    User(int id, const std::string& username, const std::string& passwordHash);

    int getId() const;
    std::string getUsername() const;
    std::string getPasswordHash() const;
};