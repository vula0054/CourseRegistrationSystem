#include "../File Header/Instructor.h"
#include <iostream>
using namespace std;

Instructor::Instructor(const string& i, const string& e, const string& n, const string& d)
    : User(i, e, n), department(d) {}

string Instructor::getRole() const { return "Instructor"; }

void Instructor::displayMenu() {
    cout << "\n=== INSTRUCTOR MENU ===\n";
    cout << "1. View my teaching sections\n";
    cout << "2. View class list of a section\n";
    cout << "3. Logout\n";
    cout << "0. Exit program\n";
}

void Instructor::addTeachingSection(const string& secId) {
    teachingSections.push_back(secId);
}

const vector<string>& Instructor::getTeachingSections() const {
    return teachingSections;
}

string Instructor::getDepartment() const {
    return department;
}