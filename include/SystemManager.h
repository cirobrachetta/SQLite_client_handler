#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "UserMapper.h"
#include "GameMapper.h"
#include "UserGameAssociation.h"
#include "sqlite3.h"

class SystemManager {
public:
    SystemManager(const std::string& dbName);
    void run();

private:
    Database db;
    UserMapper userMapper;
    GameMapper gameMapper;
    UserGameAssociation userGameAssociation;

    void showMenu();
    void addUser();
    void updateUser();
    void listUsers();
    void updateGame();
    void listGames();
    void associateUserGame();
    void listAllAssociations();
    void findAssociationsByUser();
    void removeUser();
    void addGame();
    void removeGame();
    void findAssociationsByGame();
    void showInventory();
    void buyGame();
    void sellGame();
};

#endif // SYSTEMMANAGER_H
