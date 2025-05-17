#pragma once
#include <string>

class User {
public:
    User(int id, const std::string& login, const std::string& password);

    int getId() const;
    const std::string& getLogin() const;
    const std::string& getPassword() const;

private:
    int id;
    std::string login;
    std::string password;
};
