Final project Software Engineering_
Project supervisor: Trần Thị Mỹ Tiên

# CourseRegistrationSystem
  A simple console-based **Course Registration System** implemented in C++ using Object-Oriented Programming principles. The     system supports three user roles: **Student**, **Instructor**, and **Admin**.
## Features

### Student
- View available course sections
- Register for a section
- Drop an enrolled section
- View personal timetable (enrolled sections)
- Waitlist support (automatically moved to enrolled when a spot opens)

### Instructor
- View list of sections they are teaching
- View class list (enrolled students + waitlist) for any of their sections

### Admin
- Create new courses
- Create new sections and assign instructors
- View list of all courses with section count

### General
- Login/logout functionality
- Data loaded from text files at startup (`users.txt`, `courses.txt`, `sections.txt`)
- Basic waitlist management with auto-confirmation on drop
- Simple console menu interface for each role

## Project Structure:![download](https://github.com/user-attachments/assets/714a22f0-3224-43eb-94f6-aa37110444b0)


## How to Build and Run

### Requirements
- C++11 or later
- Compiler: g++, clang++, MSVC, etc.

### Compile (using g++)
-bash: 
-g++ -std=c++11 -o course_system *.cpp

### Run
- bash: 
./course_system
- On Windows: 
course_system.exe

