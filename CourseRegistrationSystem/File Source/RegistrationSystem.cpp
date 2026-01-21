#include "../File Header/RegistrationSystem.h"
#include "../File Header/Student.h"
#include "../File Header/Instructor.h"
#include "../File Header/Admin.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

RegistrationSystem::~RegistrationSystem() {
    for (auto p : users) delete p;
    for (auto c : courses) delete c;
    for (auto s : sections) delete s;
}

void RegistrationSystem::addUser(User* p) { users.push_back(p); }

User* RegistrationSystem::login(const string& email, const string& password) {
    for (auto u : users) {
        if (u->getEmail() == email) {
            currentUser = u;
            return u;
        }
    }
    return nullptr;
}

void RegistrationSystem::logout() { currentUser = nullptr; }

User* RegistrationSystem::getCurrentUser() const { return currentUser; }

void RegistrationSystem::addCourse(Course* c) { courses.push_back(c); }

void RegistrationSystem::addSection(Section* s) { sections.push_back(s); }

Course* RegistrationSystem::findCourse(const string& cid) {
    for (auto c : courses) {
        if (c->getId() == cid) return c;
    }
    return nullptr;
}

Section* RegistrationSystem::findSection(const string& sid) {
    for (auto s : sections) {
        if (s->getId() == sid) return s;
    }
    return nullptr;
}

void RegistrationSystem::listAvailableSections() const {
    cout << "\n=== Available Sections ===\n";
    if (sections.empty()) {
        cout << "No sections available yet.\n";
        return;
    }
    for (const auto* sec : sections) {
        cout << sec->getId() << " | "
             << sec->getCourse()->getName() << " | "
             << sec->getSchedule() << " | "
             << sec->getCurrentCount() << "/" << sec->getCapacity() << endl;
    }
}

Student* RegistrationSystem::findStudent(const string& sid) {
    for (auto u : users) {
        if (u->getRole() == "Student" && u->getId() == sid) {
            return static_cast<Student*>(u);
        }
    }
    return nullptr;
}

void RegistrationSystem::listAllCourses() const {
    if (courses.empty()) {
        cout << "No courses in the system yet.\n";
        return;
    }

    cout << "\n=== ALL COURSES ===\n";
    cout << left << setw(10) << "Code" 
         << setw(40) << "Name" 
         << setw(10) << "Credits" 
         << "Sections" << endl;
    cout << string(70, '-') << endl;

    for (const auto* course : courses) {
        int sectionCount = 0;
        for (const auto* sec : sections) {
            if (sec->getCourse()->getId() == course->getId()) {
                sectionCount++;
            }
        }
        cout << left << setw(10) << course->getId()
             << setw(40) << course->getName()
             << setw(10) << course->getCredits()
             << sectionCount << endl;
    }
}

Instructor* RegistrationSystem::selectInstructor() {
    vector<Instructor*> instructors;
    for (auto* u : users) {
        if (u->getRole() == "Instructor") {
            instructors.push_back(static_cast<Instructor*>(u));
        }
    }

    if (instructors.empty()) {
        cout << "No instructors in the system.\n";
        return nullptr;
    }

    cout << "\nInstructor List:\n";
    cout << left << setw(5) << "No" << setw(15) << "ID" 
         << setw(30) << "Name" << "Department" << endl;
    cout << string(60, '-') << endl;

    for (size_t i = 0; i < instructors.size(); ++i) {
        auto* ins = instructors[i];
        cout << left << setw(5) << (i+1) 
             << setw(15) << ins->getId()
             << setw(30) << ins->getName() 
             << ins->getDepartment() << endl;
    }

    int choice = -1;
    cout << "\nSelect instructor (enter number, 0 to cancel): ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 0) return nullptr;
    if (choice < 1 || choice > static_cast<int>(instructors.size())) {
        cout << "Invalid choice.\n";
        return nullptr;
    }

    return instructors[choice - 1];
}

Course* RegistrationSystem::selectCourse() {
    if (courses.empty()) {
        cout << "No courses available.\n";
        return nullptr;
    }

    cout << "\nCourse List:\n";
    cout << left << setw(5) << "No" << setw(15) << "Code" << "Name" << endl;
    cout << string(50, '-') << endl;

    for (size_t i = 0; i < courses.size(); ++i) {
        auto* c = courses[i];
        cout << left << setw(5) << (i+1) 
             << setw(15) << c->getId() 
             << c->getName() << endl;
    }

    int choice = -1;
    cout << "\nSelect course (enter number, 0 to cancel): ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 0) return nullptr;
    if (choice < 1 || choice > static_cast<int>(courses.size())) {
        cout << "Invalid choice.\n";
        return nullptr;
    }

    return courses[choice - 1];
}

void RegistrationSystem::loadDataFromFiles() {
    //  users 
    ifstream userFile("data/users.txt");
    if (userFile.is_open()) {
        string line;
        while (getline(userFile, line)) {
            stringstream ss(line);
            string role, id, email, name, extra1, extra2;
            getline(ss, role, '|');
            getline(ss, id, '|');
            getline(ss, email, '|');
            getline(ss, name, '|');
            getline(ss, extra1, '|');
            getline(ss, extra2);

            if (role == "Student") {
                int year = stoi(extra2);
                users.push_back(new Student(id, email, name, extra1, year));
            } else if (role == "Instructor") {
                users.push_back(new Instructor(id, email, name, extra1));
            } else if (role == "Admin") {
                users.push_back(new Admin(id, email, name));
            }
        }
        userFile.close();
    }

    //  courses
    ifstream courseFile("data/courses.txt");
    if (courseFile.is_open()) {
        string line;
        while (getline(courseFile, line)) {
            stringstream ss(line);
            string cid, cname;
            int credits;
            getline(ss, cid, '|');
            getline(ss, cname, '|');
            ss >> credits;
            addCourse(new Course(cid, cname, credits));
        }
        courseFile.close();
    }

    //  sections
    ifstream sectionFile("data/sections.txt");
    if (sectionFile.is_open()) {
        string line;
        while (getline(sectionFile, line)) {
            stringstream ss(line);
            string sid, courseId, instructorId, schedule;
            int capacity;
            getline(ss, sid, '|');
            getline(ss, courseId, '|');
            getline(ss, instructorId, '|');
            getline(ss, schedule, '|');
            ss >> capacity;

            Course* course = findCourse(courseId);
            Instructor* instructor = nullptr;
            for (auto* u : users) {
                if (u->getRole() == "Instructor" && u->getId() == instructorId) {
                    instructor = static_cast<Instructor*>(u);
                    break;
                }
            }

            if (course && instructor) {
                Section* sec = new Section(sid, course, instructor, schedule, capacity);
                addSection(sec);
                instructor->addTeachingSection(sid);
            }
        }
        sectionFile.close();
    }
}