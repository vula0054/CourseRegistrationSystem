#include "../File Header/Section.h"
#include <iostream>
#include <algorithm>

using namespace std;

Section::Section(const string& sid, Course* c, Instructor* ins,
                 const string& sch, int cap)
    : sectionId(sid), course(c), instructor(ins), schedule(sch), capacity(cap) {}

string Section::getId() const { return sectionId; }
Course* Section::getCourse() const { return course; }
string Section::getSchedule() const { return schedule; }
int Section::getCapacity() const { return capacity; }
int Section::getCurrentCount() const { return currentCount; }

bool Section::registerStudent(Student* stu) {
    if (currentCount < capacity) {
        enrolledStudents.push_back(stu);
        currentCount++;
        stu->addEnrolledSection(sectionId);
        cout << "Registered successfully! Current: " << currentCount << "/" << capacity << endl;
        return true;
    } else {
        int pos = waitlist.size() + 1;
        waitlist.emplace_back(stu, pos);
        cout << "Section full. Added to waitlist (position " << pos << ").\n";
        return false;
    }
}

bool Section::dropStudent(Student* stu) {
    auto it = find(enrolledStudents.begin(), enrolledStudents.end(), stu);
    if (it != enrolledStudents.end()) {
        enrolledStudents.erase(it);
        currentCount--;
        stu->dropSection(sectionId);
        cout << "Dropped. Current: " << currentCount << "/" << capacity << endl;

        if (!waitlist.empty() && currentCount < capacity) {
            auto [waitStu, pos] = waitlist.front();
            waitlist.erase(waitlist.begin());
            enrolledStudents.push_back(waitStu);
            currentCount++;
            waitStu->addEnrolledSection(sectionId);
            cout << "Auto-confirmed student from waitlist: " << waitStu->getName() << endl;
        }
        return true;
    }
    return false;
}

void Section::displayClassList() const {
    cout << "\nClass list - " << sectionId << " (" << course->getName() << ")\n";
    cout << "Capacity: " << currentCount << "/" << capacity << "\n";
    if (enrolledStudents.empty()) {
        cout << "No students enrolled yet.\n";
    } else {
        for (const auto* s : enrolledStudents) {
            cout << "- " << s->getId() << " | " << s->getName() << endl;
        }
    }
    if (!waitlist.empty()) {
        cout << "\nWaitlist:\n";
        for (const auto& [s, p] : waitlist) {
            cout << "Pos " << p << ": " << s->getName() << endl;
        }
    }
}