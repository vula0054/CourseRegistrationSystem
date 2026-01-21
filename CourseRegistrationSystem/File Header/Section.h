#ifndef SECTION_H
#define SECTION_H

#include "Course.h"
#include "Instructor.h"
#include "Student.h"
#include <vector>
#include <string>
#include <utility>

class Section {
private:
    std::string sectionId;
    Course* course;
    Instructor* instructor;
    std::string schedule;
    int capacity;
    int currentCount = 0;
    std::vector<Student*> enrolledStudents;
    std::vector<std::pair<Student*, int>> waitlist;

public:
    Section(const std::string& sid, Course* c, Instructor* ins,
            const std::string& sch, int cap);

    std::string getId() const;
    Course* getCourse() const;
    std::string getSchedule() const;
    int getCapacity() const;
    int getCurrentCount() const;

    bool registerStudent(Student* stu);
    bool dropStudent(Student* stu);
    void displayClassList() const;
};

#endif 