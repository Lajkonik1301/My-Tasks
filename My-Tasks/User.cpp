#include "User.h"

User::User(int id, const std::string& login, const std::string& password)
    : id(id), login(login), password(password) {}

int User::getId() const {
    return id;
}

const std::string& User::getLogin() const {
    return login;
}

const std::string& User::getPassword() const {
    return password;
}
