#include "Student.h"

// Constructor
Student::Student () {
}

// parametized constructor
Student::Student(int id, std::string name, std::string level, std::string major, double gpa, int advisorID)
    : id(id), name(name), level(level), major(major), gpa(gpa), advisorID(advisorID) {}

// getters
int Student::getId() const { return id; } // returns students ID
std::string Student::getName() const { return name; } // returns the students name
std::string Student::getLevel() const { return level; } // return students academic level
std::string Student::getMajor() const { return major; } // returns student major
double Student::getGpa() const { return gpa; } // returns students GPA
int Student::getAdvisorID() const { return advisorID; } // returns student's advisor ID

// overloaded equality operator
bool Student::operator==(const Student& other) const {
    return id == other.id; // compares two students based on their ID
}

// overloaded less than operator
bool Student::operator<(const Student& other) const {
    return id < other.id; // to order students by ID in ascending order
}

// overloaded greater than operator
bool Student::operator>(const Student& other) const {
    return id > other.id; // to order students by ID in descending order
}

// overloaded ostream operator for easy output
std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << "Student ID: " << s.id << "\n"
       << "Name: " << s.name << "\n"
       << "Level: " << s.level << "\n"
       << "Major: " << s.major << "\n"
       << "GPA: " << s.gpa << "\n"
       << "Advisor ID: " << s.advisorID << "\n" << std::endl;
    return os;
}
