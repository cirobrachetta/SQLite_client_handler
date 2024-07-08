#include "UserGameAssociation.h"
#include <iostream>
#include "sqlite3.h"

UserGameAssociation::UserGameAssociation(Database& db) : db(db) {}

bool UserGameAssociation::associate(int userId, int gameId) {
        std::string sql = "INSERT INTO Users_Games (user_id, game_id) VALUES (" + std::to_string(userId) + ", " + std::to_string(gameId) + ");";
        return db.executeSQL(sql);
    }

std::vector<std::pair<User, Game>> UserGameAssociation::findAllAssociations(UserMapper& userMapper, GameMapper& gameMapper) {
        std::string sql = R"(
            SELECT Users.id, Users.name, Users.email, Games.id, Games.title, Games.genre, Games.available
            FROM Users_Games
            JOIN Users ON Users.id = Users_Games.user_id
            JOIN Games ON Games.id = Users_Games.game_id;
        )";

        sqlite3_stmt* stmt;
        std::vector<std::pair<User, Game>> associations;

        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
            std::cerr << "Failed to execute query: " << sqlite3_errmsg(db.getDB()) << std::endl;
            return associations;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int userId = sqlite3_column_int(stmt, 0);
            std::string userName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            std::string userEmail(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            int gameId = sqlite3_column_int(stmt, 3);
            std::string gameTitle(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            std::string gameGenre(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
            int gameAvailable(sqlite3_column_int(stmt, 6));

            User user(userId, userName, userEmail);
            Game game(gameId, gameTitle, gameGenre, gameAvailable);

            associations.emplace_back(user, game);
        }
        sqlite3_finalize(stmt);
        return associations;
    }
