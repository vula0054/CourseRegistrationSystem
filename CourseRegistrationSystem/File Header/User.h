#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string id;
    std::string email;
    std::string name;

public:
    User(const std::string& i, const std::string& e, const std::string& n);
    virtual ~User() = default;
    std::string getId() const;
    std::string getEmail() const;
    std::string getName() const;
    virtual void displayMenu() = 0;
    virtual std::string getRole() const = 0;
};

#endif 