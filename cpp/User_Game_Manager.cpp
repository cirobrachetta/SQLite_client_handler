#include "./User_Game_Manager.h"
#include <iostream>

UserGameManager::UserGameManager(std::unique_ptr<SqliteDatabaseHandler>& dbHandler)
    : dbHandler(dbHandler) {}

void UserGameManager::addUser(const std::string& name) {
    dbHandler->prepareQuery("INSERT INTO Users(name) VALUES(?)");
    dbHandler->addParameter(1, name);//que es ese 1 que aparece en todos lados?
    dbHandler->execute();
    std::cout << "User added successfully." << std::endl;
}

void UserGameManager::deleteUser(int id) {
    dbHandler->prepareQuery("DELETE FROM Users WHERE id=?");
    dbHandler->addParameter(1, std::to_string(id));
    dbHandler->execute();
    std::cout << "User deleted successfully." << std::endl;
}

void UserGameManager::modifyUser(int id, const std::string& name) {
    dbHandler->prepareQuery("UPDATE Users SET name=? WHERE id=?");
    dbHandler->addParameter(1, name);
    dbHandler->addParameter(2, std::to_string(id));
    dbHandler->execute();
    std::cout << "User modified successfully." << std::endl;
}

void UserGameManager::listUsers() {
    dbHandler->prepareQuery("SELECT * FROM Users");
    Table table = dbHandler->fetchAll();

    for (const auto& row : table) {
        std::cout << "ID: " << row.at("id") << ", Name: " << row.at("name") << std::endl;
    }
}

void UserGameManager::addGame(const std::string& title) {
    dbHandler->prepareQuery("INSERT INTO Games(title) VALUES(?)");
    dbHandler->addParameter(1, title);
    dbHandler->execute();
    std::cout << "Game added successfully." << std::endl;
}

void UserGameManager::deleteGame(int id) {
    dbHandler->prepareQuery("DELETE FROM Games WHERE id=?");
    dbHandler->addParameter(1, std::to_string(id));
    dbHandler->execute();
    std::cout << "Game deleted successfully." << std::endl;
}

void UserGameManager::modifyGame(int id, const std::string& title) {
    dbHandler->prepareQuery("UPDATE Games SET title=? WHERE id=?");
    dbHandler->addParameter(1, title);
    dbHandler->addParameter(2, std::to_string(id));
    dbHandler->execute();
    std::cout << "Game modified successfully." << std::endl;
}

void UserGameManager::listGames() {
    dbHandler->prepareQuery("SELECT * FROM Games");
    Table table = dbHandler->fetchAll();

    for (const auto& row : table) {
        std::cout << "ID: " << row.at("id") << ", Title: " << row.at("title") << std::endl;
    }
}

void UserGameManager::associateGameUser(int userId, int gameId) {
    dbHandler->prepareQuery("INSERT INTO User_Games(user_id, game_id) VALUES(?, ?)");
    dbHandler->addParameter(1, std::to_string(userId));
    dbHandler->addParameter(2, std::to_string(gameId));
    dbHandler->execute();
    std::cout << "Game associated with user successfully." << std::endl;
}

void UserGameManager::searchByUser(int userId) {
    dbHandler->prepareQuery("SELECT Users.id AS user_id, Users.name, Games.id AS game_id, Games.title FROM Users "
                            "JOIN User_Games ON Users.id = User_Games.user_id "
                            "JOIN Games ON Games.id = User_Games.game_id "
                            "WHERE Users.id = ?");
    dbHandler->addParameter(1, std::to_string(userId));
    Table table = dbHandler->fetchAll();

    for (const auto& row : table) {
        std::cout << "User ID: " << row.at("user_id") << ", Name: " << row.at("name")
                  << ", Game ID: " << row.at("game_id") << ", Title: " << row.at("title") << std::endl;
    }
}

void UserGameManager::searchByGame(int gameId) {
    dbHandler->prepareQuery("SELECT Games.id AS game_id, Games.title, Users.id AS user_id, Users.name FROM Games "
                            "JOIN User_Games ON Games.id = User_Games.game_id "
                            "JOIN Users ON Users.id = User_Games.user_id "
                            "WHERE Games.id = ?");
    dbHandler->addParameter(1, std::to_string(gameId));
    Table table = dbHandler->fetchAll();

    for (const auto& row : table) {
        std::cout << "Game ID: " << row.at("game_id") << ", Title: " << row.at("title")
                  << ", User ID: " << row.at("user_id") << ", Name: " << row.at("name") << std::endl;
    }
}

void UserGameManager::listUsers_Games() {
    try {
        dbHandler->prepareQuery(
            "SELECT Users.name AS user_name, Games.title AS game_title "
            "FROM User_Games "
            "INNER JOIN Users ON User_Games.user_id = Users.id "
            "INNER JOIN Games ON User_Games.game_id = Games.id"
        );
        Table table = dbHandler->fetchAll();

        if (table.empty()) {
            std::cout << "No associations found in User_Games table." << std::endl;
        } else {
            for (const auto& row : table) {
                if (row.find("user_name") != row.end() && row.find("game_title") != row.end()) {
                    std::cout << "User: " << row.at("user_name") << ", Game: " << row.at("game_title") << std::endl;
                } else {
                    std::cerr << "Missing columns 'user_name' or 'game_title' in result row." << std::endl;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error while listing user-game associations: " << e.what() << std::endl;
    }
}
