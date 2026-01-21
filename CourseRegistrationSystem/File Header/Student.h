#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include <vector>
#include <string>

class Student : public User {
private:
    std::string major;
    int year;
    std::vector<std::string> enrolledSections;

public:
    Student(const std::string& i, const std::string& e, const std::string& n,
            const std::string& m, int y);

    std::string getRole() const override;
    void displayMenu() override;
    void addEnrolledSection(const std::string& secId);
    bool isEnrolled(const std::string& secId) const;
    void dropSection(const std::string& secId);
    void viewTimetable() const;
};

#endif