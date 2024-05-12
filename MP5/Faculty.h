#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include <iostream>
#include <fstream>


class Faculty {
private:
    int facultyID; // store faculty ID
    std::string name; // store faculty name
    std::string level; // store faculty level
    std::string department; // store department name
    int adviseesIDs[100];  // assuming a max of 100 advisees for simplicity
    int numAdvisees;  // to keep track of the actual number of advisees

public:
    // default constructor
    Faculty();
    Faculty(int id, std::string name, std::string level, std::string department);
    
    // getters
    int getFacultyID() const;
    std::string getName() const;
    std::string getLevel() const;
    std::string getDepartment() const;
    void getAdviseesIDs(int* outArray, int& outSize) const;
    int getNumAdvisees () const;
    
    bool operator==(const Faculty& other) const; // equality comparison operator
    bool operator<(const Faculty& other) const; // less than comparison 
    bool operator>(const Faculty& other) const; // greater than comparison
    
    void addAdvisee(int studentID); // method to add advisee
    void removeAdvisee(int studentID); // method to remove advisee

    friend std::ostream& operator<<(std::ostream& os, const Faculty& faculty);
};



#endif
