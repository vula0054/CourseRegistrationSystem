#include "../File Header/Course.h"
#include <iostream>

using namespace std;

Course::Course(const string& cid, const string& n, int c)
    : courseId(cid), name(n), credits(c) {}

string Course::getId() const { return courseId; }
string Course::getName() const { return name; }
int Course::getCredits() const { return credits; }

void Course::displayInfo() const {
    cout << "Course: " << courseId << " - " << name
         << " (" << credits << " credits)\n";
}