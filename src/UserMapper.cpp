#include "UserMapper.h"
#include <iostream>
#include "sqlite3.h"

UserMapper::UserMapper(Database& db) : db(db) {}

bool UserMapper::insert(const User& user) {
    std::string sql = "INSERT INTO Users (name, email) VALUES ('" + user.name + "', '" + user.email + "');";
    return db.executeSQL(sql);
}

bool UserMapper::remove(int id) {
    std::string sql = "DELETE FROM Users WHERE id = " + std::to_string(id) + ";";
    return db.executeSQL(sql);
}

bool UserMapper::update(const User& user) {
        std::string sql = "UPDATE Users SET name = '" + user.name + "', email = '" + user.email + "' WHERE id = " + std::to_string(user.id) + ";";
        return db.executeSQL(sql);
    }

std::vector<User> UserMapper::findAll() {
        std::string sql = "SELECT id, name, email FROM Users;";
        sqlite3_stmt* stmt;
        std::vector<User> users;

        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
            std::cerr << "Failed to execute query: " << sqlite3_errmsg(db.getDB()) << std::endl;
            return users;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            std::string email(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            users.emplace_back(id, name, email);
        }
        sqlite3_finalize(stmt);
        return users;
    }

std::vector<User> UserMapper::findByName(const std::string& name) {
        std::string sql = "SELECT id, name, email FROM Users WHERE name LIKE '%" + name + "%';";
        sqlite3_stmt* stmt;
        std::vector<User> users;

        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
            std::cerr << "Failed to execute query: " << sqlite3_errmsg(db.getDB()) << std::endl;
            return users;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            std::string email(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            users.emplace_back(id, name, email);
        }
        sqlite3_finalize(stmt);
        return users;
    }
