#ifndef USERGAMEASSOCIATION_H
#define USERGAMEASSOCIATION_H

#include <vector>
#include <utility>
#include "UserMapper.h"
#include "GameMapper.h"
#include "sqlite3.h"

class UserGameAssociation {
public:
    UserGameAssociation(Database& db);
    bool associate(int userId, int gameId);
    std::vector<std::pair<User, Game>> findAllAssociations(UserMapper& userMapper, GameMapper& gameMapper);

private:
    Database& db;
};

#endif // USERGAMEASSOCIATION_H
