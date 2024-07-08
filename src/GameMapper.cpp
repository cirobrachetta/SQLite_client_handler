#include "GameMapper.h"
#include <iostream>
#include "sqlite3.h"

GameMapper::GameMapper(Database& db) : db(db) {}

bool GameMapper::insert(const Game& game) {
    std::string sql = "INSERT INTO Games (title, genre, available) VALUES ('" + game.title + "', '" + game.genre + "', " + std::to_string(game.available) + ");";
    return db.executeSQL(sql);
}

bool GameMapper::updateAvailability(int gameId, int change) {
        std::string sql = "UPDATE Games SET available = available + ? WHERE id = ?";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, 0) == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, change);
            sqlite3_bind_int(stmt, 2, gameId);

            if (sqlite3_step(stmt) != SQLITE_DONE) {
                std::cerr << "Failed to update availability: " << sqlite3_errmsg(db.getDB()) << std::endl;
                sqlite3_finalize(stmt);
                return false;
            }
            sqlite3_finalize(stmt);
            return true;
        } else {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db.getDB()) << std::endl;
            return false;
        }
    }

bool GameMapper::remove(int id) {
        std::string sql = "DELETE FROM Games WHERE id = " + std::to_string(id) + ";";
        return db.executeSQL(sql);
    }

bool GameMapper::update(const Game& game) {
        std::string sql = "UPDATE Games SET title = '" + game.title + "', genre = '" + game.genre + "' WHERE id = " + std::to_string(game.id) + ";";
        return db.executeSQL(sql);
    }

std::vector<Game> GameMapper::findAll() {
        std::string sql = "SELECT id, title, genre, available FROM Games;";
        sqlite3_stmt* stmt;
        std::vector<Game> games;

    if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Failed to execute query: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return games;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string title(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string genre(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        int available = sqlite3_column_int(stmt, 3); // Obtener la disponibilidad
        games.emplace_back(id, title, genre, available); // Añadir disponibilidad al constructor
    }

    
    sqlite3_finalize(stmt);
    return games;
}

std::vector<Game> GameMapper::findByTitle(const std::string& title) {
        std::string sql = "SELECT id, title, genre, available FROM Games WHERE title LIKE '%" + title + "%';";
        sqlite3_stmt* stmt;
        std::vector<Game> games;

        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
            std::cerr << "Failed to execute query: " << sqlite3_errmsg(db.getDB()) << std::endl;
            return games;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string title(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            std::string genre(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            int available(sqlite3_column_int(stmt, 3));
            games.emplace_back(id, title, genre, available);
        }
        sqlite3_finalize(stmt);
        return games;
    }
