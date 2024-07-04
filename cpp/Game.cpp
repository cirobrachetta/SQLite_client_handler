#include "./Game.h"

Game::Game(int id, const std::string& title) : id(id), title(title) {}

int Game::getId() const {
    return id;
}

const std::string& Game::getTitle() const {
    return title;
}

void Game::setTitle(const std::string& title) {
    this->title = title;
}
