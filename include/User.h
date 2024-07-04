#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User(int id, const std::string& name);
    int getId() const;
    const std::string& getName() const;
    void setName(const std::string& name);

private:
    int id;
    std::string name;
};

#endif