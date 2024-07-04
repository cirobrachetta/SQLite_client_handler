#ifndef GAME_H
#define GAME_H

#include <string>

class Game {
public:
    Game(int id, const std::string& title);
    int getId() const;
    const std::string& getTitle() const;
    void setTitle(const std::string& title);

private:
    int id;
    std::string title;
};

#endif
