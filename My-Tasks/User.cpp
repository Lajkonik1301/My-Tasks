#include "User.h"

User::User(int id, const std::string& username, const std::string& passwordHash)
    : id(id), username(username), passwordHash(passwordHash) {}

int User::getId() const {
    return id;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getPasswordHash() const {
    return passwordHash;
}