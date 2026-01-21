#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
private:
    std::string courseId;
    std::string name;
    int credits;

public:
    Course(const std::string& cid, const std::string& n, int c);

    std::string getId() const;
    std::string getName() const;
    int getCredits() const;
    void displayInfo() const;
};

#endif 