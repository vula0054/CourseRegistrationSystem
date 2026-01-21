#include "../File Header/User.h"
using namespace std;

User::User(const string& i, const string& e, const string& n)
    : id(i), email(e), name(n) {}

string User::getId() const { return id; }
string User::getEmail() const { return email; }
string User::getName() const { return name; }