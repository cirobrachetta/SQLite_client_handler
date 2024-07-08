#ifndef GAME_H
#define GAME_H

#include <string>

class Game {
public:
    int id;
    std::string title;
    std::string genre;
    int available;

    Game(int id, const std::string& title, const std::string& genre, int available);
};

#endif // GAME_H
