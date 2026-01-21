#include "../File Header/Student.h"
#include <iostream>
#include <algorithm>

using namespace std;

Student::Student(const string& i, const string& e, const string& n,
                 const string& m, int y)
    : User(i, e, n), major(m), year(y) {}

string Student::getRole() const { return "Student"; }

void Student::displayMenu() {
    cout << "\n=== STUDENT MENU ===\n";
    cout << "1. View available courses/sections\n";
    cout << "2. Register for a section\n";
    cout << "3. Drop a section\n";
    cout << "4. View my timetable (enrolled sections)\n";
    cout << "5. Logout\n";
    cout << "0. Exit program\n";
}

void Student::addEnrolledSection(const string& secId) {
    enrolledSections.push_back(secId);
}

bool Student::isEnrolled(const string& secId) const {
    return find(enrolledSections.begin(), enrolledSections.end(), secId) != enrolledSections.end();
}

void Student::dropSection(const string& secId) {
    auto it = find(enrolledSections.begin(), enrolledSections.end(), secId);
    if (it != enrolledSections.end()) {
        enrolledSections.erase(it);
        cout << "Dropped section " << secId << " successfully.\n";
    } else {
        cout << "Not enrolled in that section.\n";
    }
}

void Student::viewTimetable() const {
    cout << "\nYour enrolled sections:\n";
    if (enrolledSections.empty()) {
        cout << "No sections enrolled yet.\n";
    } else {
        for (const auto& s : enrolledSections) {
            cout << "- " << s << endl;
        }
    }
}