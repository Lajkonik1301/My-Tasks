#include "DatabaseManager.h"
#include <sqlite3.h>
#include <iostream>

DatabaseManager::DatabaseManager() {
    dbPath = "tasks.db";
    Init();
}

DatabaseManager& DatabaseManager::GetInstance() {
    static DatabaseManager instance;
    return instance;
}

void DatabaseManager::Init() {
    sqlite3* db;
    char* err;
    if (sqlite3_open(dbPath.c_str(), &db) == SQLITE_OK) {
        const char* userSQL = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, login TEXT UNIQUE, password TEXT);";
        const char* taskSQL = "CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, user_id INTEGER, name TEXT, description TEXT, status INTEGER, FOREIGN KEY(user_id) REFERENCES users(id));";
        sqlite3_exec(db, userSQL, nullptr, nullptr, &err);
        sqlite3_exec(db, taskSQL, nullptr, nullptr, &err);
        sqlite3_close(db);
    }
}

bool DatabaseManager::RegisterUser(const std::string& login, const std::string& password) {
    sqlite3* db;
    sqlite3_open(dbPath.c_str(), &db);
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO users (login, password) VALUES (?, ?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return success;
}

bool DatabaseManager::ValidateUser(const std::string& login, const std::string& password) {
    sqlite3* db;
    sqlite3_open(dbPath.c_str(), &db);
    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM users WHERE login = ? AND password = ?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    bool valid = sqlite3_step(stmt) == SQLITE_ROW;
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return valid;
}

void DatabaseManager::AddTask(const std::string& login, const std::string& name, const std::string& description) {
    sqlite3* db;
    sqlite3_open(dbPath.c_str(), &db);
    sqlite3_stmt* stmt;
    const char* userIdSQL = "SELECT id FROM users WHERE login = ?;";
    sqlite3_prepare_v2(db, userIdSQL, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
    int userId = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        userId = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    if (userId != -1) {
        const char* taskSQL = "INSERT INTO tasks (user_id, name, description, status) VALUES (?, ?, ?, 0);";
        sqlite3_prepare_v2(db, taskSQL, -1, &stmt, nullptr);
        sqlite3_bind_int(stmt, 1, userId);
        sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, description.c_str(), -1, SQLITE_STATIC);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

std::vector<Task> DatabaseManager::GetTasks(const std::string& login) {
    sqlite3* db;
    sqlite3_open(dbPath.c_str(), &db);
    sqlite3_stmt* stmt;
    std::vector<Task> tasks;
    const char* sql = "SELECT t.id, t.name, t.description, t.status FROM tasks t JOIN users u ON t.user_id = u.id WHERE u.login = ?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        bool status = sqlite3_column_int(stmt, 3);
        tasks.emplace_back(id, name, description, status);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return tasks;
}

void DatabaseManager::DeleteTask(const std::string& login, int index) {
    auto tasks = GetTasks(login);
    if (index < 0 || index >= (int)tasks.size()) return;
    int id = tasks[index].getId();
    sqlite3* db;
    sqlite3_open(dbPath.c_str(), &db);
    sqlite3_stmt* stmt;
    const char* sql = "DELETE FROM tasks WHERE id = ?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void DatabaseManager::MarkTaskDone(const std::string& login, int index) {
    auto tasks = GetTasks(login);
    if (index < 0 || index >= (int)tasks.size()) return;
    int id = tasks[index].getId();
    sqlite3* db;
    sqlite3_open(dbPath.c_str(), &db);
    sqlite3_stmt* stmt;
    const char* sql = "UPDATE tasks SET status = 1 WHERE id = ?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
