#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "sqlite3.h"

class Database {
public:
    Database(const std::string& dbName);
    ~Database();
    bool executeSQL(const std::string& sql);
    sqlite3* getDB() const;

private:
    sqlite3* db;
};

class DatabaseInitializer {
public:
    static void initialize(Database& db);
};

#endif // DATABASE_H
