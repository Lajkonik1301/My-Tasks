#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(){
	bool databaseConnection = openDatabase();

	if (databaseConnection) {
		createUsersTable();
		createTaskTable();
		createCategoriesTable();
	}
}

DatabaseManager::~DatabaseManager(){
	closeDatabase();
}

bool DatabaseManager::openDatabase(){
	int result = sqlite3_open("my-tasks.db", &db);
	if (result != SQLITE_OK) {
		std::cerr << "Blad otwarcia bazy danych: " << sqlite3_errmsg(db) << std::endl;
		return false;
	}
	return true;
}

void DatabaseManager::closeDatabase() {
	sqlite3_close(db);
}

void DatabaseManager::createUsersTable(){
	const char* createTableQuery =
		"CREATE TABLE IF NOT EXISTS users ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"username TEXT UNIQUE, "
		"passwordHash TEXT);";
	sqlite3_exec(db, createTableQuery, nullptr, nullptr, nullptr);
}

void DatabaseManager::createTaskTable(){
	const char* createTableQuery =
		"CREATE TABLE IF NOT EXISTS tasks ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"user_id INTEGER, "
		"category_id INTEGER, "
		"name TEXT,"
		"description TEXT,"
		"priority INTEGER,"
		"status INTEGER,"
		"FOREIGN KEY (user_id) REFERENCES users(id),"
		"FOREIGN KEY(category_id) REFERENCES categories(id));";
	sqlite3_exec(db, createTableQuery, nullptr, nullptr, nullptr);
}

void DatabaseManager::createCategoriesTable(){
	const char* createTableQuery =
		"CREATE TABLE IF NOT EXISTS categories ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"user_id INTEGER, "
		"task_id INTEGER, "
		"name TEXT,"
		"FOREIGN KEY (user_id) REFERENCES users(id),"
		"FOREIGN KEY(task_id) REFERENCES tasks(id));";
	sqlite3_exec(db, createTableQuery, nullptr, nullptr, nullptr);
}

std::string DatabaseManager::hashPassword(const std::string& password){
	unsigned long hash = 5381; // Arbitralna warto�� pocz�tkowa

	for (char c : password) {
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	}

	std::stringstream ss;
	ss << std::hex << hash;
	return ss.str();
}

RegistrationStatus DatabaseManager::registerUser(const std::string& username, const std::string& password){
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


User* DatabaseManager::loginUser(const std::string & username, const std::string & password){
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