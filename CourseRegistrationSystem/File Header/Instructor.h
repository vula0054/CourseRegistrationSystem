#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "User.h"
#include <vector>
#include <string>

class Instructor : public User {
private:
    std::string department;
    std::vector<std::string> teachingSections;

public:
    Instructor(const std::string& i, const std::string& e, const std::string& n, const std::string& d);

    std::string getRole() const override;
    void displayMenu() override;
    void addTeachingSection(const std::string& secId);
    const std::vector<std::string>& getTeachingSections() const;
    std::string getDepartment() const;
};

#endif