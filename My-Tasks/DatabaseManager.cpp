#include "DatabaseManager.h"

//'DATABASE IS LOCKED' error occures whilst
//the DB file is opened whilst the program is running

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
	sqlite3_exec(db, "PRAGMA encoding = 'UTF-8';", nullptr, nullptr, nullptr);
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
		"name TEXT,"
		"FOREIGN KEY (user_id) REFERENCES users(id));";

	sqlite3_exec(db, createTableQuery, nullptr, nullptr, nullptr);
}

std::string DatabaseManager::hashPassword(const std::string& password){
	unsigned long hash = 5381; // Arbitralna wartoœæ pocz¹tkowa

	for (char c : password) {
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	}

	std::stringstream ss;
	ss << std::hex << hash;
	return ss.str();
}

void DatabaseManager::createDefaultCat(int userId) {
	std::string query = "INSERT INTO categories (user_id, name) VALUES (?, ?);";
	const char* def = "Domyslne";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

	sqlite3_bind_int(stmt, 1, userId);
	sqlite3_bind_text(stmt, 2, def, -1, SQLITE_STATIC);

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
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

		int newUserId = NULL;
		query = "INSERT INTO users (username, passwordHash) VALUES (?, ?);";
		sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
		sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, hashedPassword.c_str(), -1, SQLITE_STATIC);

		if (sqlite3_step(stmt) != SQLITE_DONE) {
			sqlite3_finalize(stmt);
			return RegistrationStatus::DatabaseError;
		}

		newUserId = static_cast<int>(sqlite3_last_insert_rowid(db));
		sqlite3_finalize(stmt);

		createDefaultCat(newUserId);

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

void DatabaseManager::getCategories(std::vector<std::string>& categories, int userId) {
	sqlite3_stmt* stmt;
	std::string query = "SELECT name FROM categories WHERE user_id = ?";

	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
	sqlite3_bind_int(stmt, 1, userId);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		const unsigned char* categoryName = sqlite3_column_text(stmt, 0);
		categories.emplace_back(reinterpret_cast<const char*>(categoryName));
	}
	sqlite3_finalize(stmt);
}

std::string DatabaseManager::addNewTask(int userId, int categoryId, std::string name, std::string description, int priority){
	//data already validated

	std::string query = "INSERT INTO tasks (user_id, category_id, name, description, priority, status) VALUES(?, ?, ?, ?, ?, ?);";
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		return sqlite3_errmsg(db);
	}

	sqlite3_bind_int(stmt, 1, userId);
	sqlite3_bind_int(stmt, 2, categoryId);
	sqlite3_bind_text(stmt, 3, name.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, description.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 5, priority);
	sqlite3_bind_int(stmt, 6, 0);

	int result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		return sqlite3_errmsg(db);
	}

	sqlite3_finalize(stmt);
	
	if (result == SQLITE_DONE)
		return "sukces";

	return "b³¹d";
}

bool DatabaseManager::modifyTask(){

	return false;
}

bool DatabaseManager::markAsDone(int taskId) {
	std::string getStatusQuery = "SELECT status FROM tasks WHERE id = ?;";
	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(db, getStatusQuery.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		return false;
	}

	sqlite3_bind_int(stmt, 1, taskId);
	int result = sqlite3_step(stmt);

	if (result != SQLITE_ROW) {
		sqlite3_finalize(stmt);
		return false;
	}

	int currentStatus = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);

	int newStatus = (currentStatus == 0) ? 1 : 0;

	std::string updateQuery = "UPDATE tasks SET status = ? WHERE id = ?;";
	rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		return sqlite3_errmsg(db);
	}

	sqlite3_bind_int(stmt, 1, newStatus);
	sqlite3_bind_int(stmt, 2, taskId);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		sqlite3_finalize(stmt);
		return false;
	}

	sqlite3_finalize(stmt);
	return true;
}

