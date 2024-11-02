#include "UserManager.h"

UserManager::UserManager() {
    openDatabase();
    const char* createTableQuery =
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE, "
        "passwordHash TEXT);";
    sqlite3_exec(db, createTableQuery, nullptr, nullptr, nullptr);
}

UserManager::~UserManager() {
    closeDatabase();
}

bool UserManager::openDatabase() {
    int result = sqlite3_open("users.db", &db);
    if (result != SQLITE_OK) {
        std::cerr << "Blad otwarcia bazy danych: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

void UserManager::closeDatabase() {
    sqlite3_close(db);
}

std::string UserManager::hashPassword(const std::string& password) {
    unsigned long hash = 5381; // Arbitralna wartoœæ pocz¹tkowa

    for (char c : password) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}

RegistrationStatus UserManager::registerUser(const std::string& username, const std::string& password) {
    if (username.empty() || password.empty())
        return RegistrationStatus::EmptyUsernameOrPassword;

    std::string hashedPassword = hashPassword(password);

    std::string query = "SELECT COUNT(*) FROM users WHERE users.username = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW)
        count = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);

    if (count > 0)
        return RegistrationStatus::UsernameAlreadyExists;

    query = "INSERT INTO users (username, passwordHash) VALUES (?, ?);";
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashedPassword.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return RegistrationStatus::DatabaseError;
    }
    sqlite3_finalize(stmt);

    return RegistrationStatus::Success;
}

User* UserManager::loginUser(const std::string& username, const std::string& password) {
    if (username.empty() || password.empty())
        return nullptr;

    std::string hashedPassword = hashPassword(password);

    std::string query = "SELECT users.id FROM users WHERE users.username = ? AND users.passwordHash = ?";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashedPassword.c_str(), -1, SQLITE_STATIC);

    int userId = NULL;
    if (sqlite3_step(stmt) != SQLITE_ROW)
        return nullptr;

    userId = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);

    return new User(userId, username, hashedPassword);
}