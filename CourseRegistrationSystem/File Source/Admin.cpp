#include "../File Header/Admin.h"
#include <iostream>

using namespace std;

Admin::Admin(const string& i, const string& e, const string& n)
    : User(i, e, n) {}

string Admin::getRole() const { return "Admin"; }

void Admin::displayMenu() {
    cout << "\n=== ADMIN MENU ===\n";
    cout << "1. Create new course\n";
    cout << "2. Create new section\n";
    cout << "3. View all courses\n";
    cout << "4. Logout\n";
    cout << "0. Exit program\n";
}