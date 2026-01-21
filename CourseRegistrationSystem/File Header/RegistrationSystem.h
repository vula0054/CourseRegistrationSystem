#ifndef REGISTRATIONSYSTEM_H
#define REGISTRATIONSYSTEM_H

#include "User.h"
#include "Course.h"
#include "Section.h"
#include <vector>
#include <string>

class RegistrationSystem {
private:
    std::vector<User*> users;
    std::vector<Course*> courses;
    std::vector<Section*> sections;
    User* currentUser = nullptr;

public:
    ~RegistrationSystem();
    void addUser(User* p);
    User* login(const std::string& email, const std::string& password);
    void logout();
    User* getCurrentUser() const;
    void addCourse(Course* c);
    void addSection(Section* s);
    Course* findCourse(const std::string& cid);
    Section* findSection(const std::string& sid);
    void listAvailableSections() const;
    Student* findStudent(const std::string& sid);

    void listAllCourses() const;
    Instructor* selectInstructor();
    Course* selectCourse();

    // tai du lieu tu file
    void loadDataFromFiles();
};

#endif