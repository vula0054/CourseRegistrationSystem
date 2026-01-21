#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    Admin(const std::string& i, const std::string& e, const std::string& n);

    std::string getRole() const override;
    void displayMenu() override;
};

#endif 