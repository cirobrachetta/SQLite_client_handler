#ifndef USERGAMEMANAGER_H
#define USERGAMEMANAGER_H

#include <memory>
#include "SqliteDatabaseHandler.h"
#include "User.h"
#include "Game.h"

class UserGameManager {
public:
    UserGameManager(std::unique_ptr<SqliteDatabaseHandler>& dbHandler);
    void addUser(const std::string& name);
    void deleteUser(int id);
    void modifyUser(int id, const std::string& name);
    void listUsers();
    void addGame(const std::string& title);
    void deleteGame(int id);
    void modifyGame(int id, const std::string& title);
    void listGames();
    void associateGameUser(int userId, int gameId);
    void searchByUser(int userId);
    void searchByGame(int gameId);
    void listUsers_Games();

private:
    std::unique_ptr<SqliteDatabaseHandler>& dbHandler;
};

#endif
