#ifndef USERMAPPER_H
#define USERMAPPER_H

#include <string>
#include "Database.h"
#include "User.h"
#include <vector>
#include "sqlite3.h"

class UserMapper {
public:
    UserMapper(Database& db);
    bool insert(const User& user);
    bool remove(int id);
    bool update(const User& user);
    std::vector<User> findAll();
    std::vector<User> findByName(const std::string& name);

private:
    Database& db;
};

#endif // USERMAPPER_H
