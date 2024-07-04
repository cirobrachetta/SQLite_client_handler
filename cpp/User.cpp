#include "./User.h"

User::User(int id, const std::string& name) : id(id), name(name) {}

int User::getId() const {
    return id;
}

const std::string& User::getName() const {
    return name;
}

void User::setName(const std::string& name) {
    this->name = name;
}
