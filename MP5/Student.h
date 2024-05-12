#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include <fstream>


class Student {
private:
    int id; // student ID
    std::string name;   // students name
    std::string level;  // students grade level (e.g., Freshman)
    std::string major;  // students major
    double gpa;         // students GPA
    int advisorID;      // faculty advisors ID

public:
    // Constructor
    Student();

    // parametize constructor
    Student(int id, std::string name, std::string level, std::string major, double gpa, int advisorID);

    // getters
    int getId() const; // returns student ID
    std::string getName() const; // returns students name
    std::string getLevel() const; // returns students grade
    std::string getMajor() const; // returns students major
    double getGpa() const; // returns students GPA
    int getAdvisorID() const; // returns student advisor's ID

    // overloaded comparison operators
    bool operator==(const Student& other) const; // compares two students based on their ID
    bool operator<(const Student& other) const; // if students ID is less than another
    bool operator>(const Student& other) const; // if students ID is greater than another

    // overload ostream 
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};

#endif
