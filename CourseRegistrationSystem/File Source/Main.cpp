#include "../File Header/RegistrationSystem.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    RegistrationSystem system;

    // tai du lieu tu file
    system.loadDataFromFiles();

    while (true) {
        if (!system.getCurrentUser()) {
            cout << "\n=== COURSE REGISTRATION SYSTEM ===\n";
            cout << "Email: ";
            string email;
            getline(cin, email);
            cout << "Password (any for demo): ";
            string pass;
            getline(cin, pass);

            User* user = system.login(email, pass);
            if (user) {
                cout << "Login successful! Role: " << user->getRole()
                     << " - " << user->getName() << endl;
            } else {
                cout << "Login failed! Check email.\n";
                continue;
            }
        }

        User* curr = system.getCurrentUser();
        curr->displayMenu();

        cout << "\nChoice (0 to exit): ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number!\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) {
            cout << "Goodbye!\n";
            break;
        }

        if (curr->getRole() == "Student") {
            Student* stu = static_cast<Student*>(curr);
            if (choice == 1) {
                system.listAvailableSections();
            } else if (choice == 2) {
                string secId;
                cout << "Enter section ID to register: ";
                getline(cin, secId);
                Section* sec = system.findSection(secId);
                if (sec) {
                    if (stu->isEnrolled(secId)) {
                        cout << "You are already enrolled in this section!\n";
                    } else {
                        sec->registerStudent(stu);
                    }
                } else {
                    cout << "Section not found.\n";
                }
            } else if (choice == 3) {
                string secId;
                cout << "Enter section ID to drop: ";
                getline(cin, secId);
                Section* sec = system.findSection(secId);
                if (sec) {
                    sec->dropStudent(stu);
                } else {
                    cout << "Section not found.\n";
                }
            } else if (choice == 4) {
                stu->viewTimetable();
            } else if (choice == 5) {
                system.logout();
                cout << "Logged out.\n";
            } else {
                cout << "Invalid choice.\n";
            }
        }
        else if (curr->getRole() == "Instructor") {
            Instructor* ins = static_cast<Instructor*>(curr);
            if (choice == 1) {
                cout << "\nYour teaching sections:\n";
                for (const auto& s : ins->getTeachingSections()) {
                    cout << "- " << s << endl;
                }
            } else if (choice == 2) {
                string secId;
                cout << "Enter section ID to view class list: ";
                getline(cin, secId);
                Section* sec = system.findSection(secId);
                if (sec) {
                    sec->displayClassList();
                } else {
                    cout << "Section not found.\n";
                }
            } else if (choice == 3) {
                system.logout();
                cout << "Logged out.\n";
            } else {
                cout << "Invalid choice.\n";
            }
        }
        else if (curr->getRole() == "Admin") {
            if (choice == 1) {
                string cid, cname;
                int credits;

                cout << "\n=== CREATE NEW COURSE ===\n";
                cout << "Course code (e.g. CS301): ";
                getline(cin, cid);

                if (system.findCourse(cid)) {
                    cout << "Course code already exists! Choose another.\n";
                    continue;
                }

                cout << "Course name: ";
                getline(cin, cname);
                cout << "Credits: ";
                cin >> credits;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                Course* newCourse = new Course(cid, cname, credits);
                system.addCourse(newCourse);
                cout << "Course created successfully!\n";
                cout << "Code: " << cid << " | Name: " << cname << " | Credits: " << credits << endl;
            }
            else if (choice == 2) {
                string sid, schedule;
                int capacity;

                cout << "\n=== CREATE NEW SECTION ===\n";

                Course* selectedCourse = system.selectCourse();
                if (!selectedCourse) continue;

                Instructor* selectedIns = system.selectInstructor();
                if (!selectedIns) continue;

                cout << "Section ID (e.g. " << selectedCourse->getId() << ".01): ";
                getline(cin, sid);

                if (system.findSection(sid)) {
                    cout << "Section ID already exists!\n";
                    continue;
                }

                cout << "Schedule (e.g. Monday 7:00-9:00, Room C304): ";
                getline(cin, schedule);
                cout << "Capacity (max students): ";
                cin >> capacity;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                Section* newSection = new Section(sid, selectedCourse, selectedIns, schedule, capacity);
                system.addSection(newSection);
                selectedIns->addTeachingSection(sid);

                cout << "Section created successfully!\n";
                cout << "Section: " << sid << " | Course: " << selectedCourse->getName()
                     << " | Instructor: " << selectedIns->getName() << endl;
            }
            else if (choice == 3) {
                system.listAllCourses();
            }
            else if (choice == 4) {
                system.logout();
                cout << "Logged out.\n";
            } else {
                cout << "Invalid choice.\n";
            }
        }
    }

    return 0;
}