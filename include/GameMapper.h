#ifndef GAMEMAPPER_H
#define GAMEMAPPER_H

#include <string>
#include <vector>
#include "Database.h"
#include "Game.h"

class GameMapper {
public:
    GameMapper(Database& db);
    bool insert(const Game& game);
    bool remove(int id);
    bool update(const Game& game);
    bool updateAvailability(int id, int change);
    std::vector<Game> findAll();
    std::vector<Game> findByTitle(const std::string& title);

private:
    Database& db;
};

#endif // GAMEMAPPER_H
