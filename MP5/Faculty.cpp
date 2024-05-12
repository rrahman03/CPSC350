#include "Faculty.h"

// default constructor
Faculty::Faculty() {
    numAdvisees = 0; // initialize number of advisees to 0
}

// constructor with parameters to initialize a faculty object
Faculty::Faculty(int id, std::string name, std::string level, std::string department)
    : facultyID(id), name(name), level(level), department(department), numAdvisees(0) {
    }

// returns faculty ID
int Faculty::getFacultyID() const { return facultyID; }
// returns the name of faculty
std::string Faculty::getName() const { return name; }
// returns level of the faculty
std::string Faculty::getLevel() const { return level; }
// returns department of faculty 
std::string Faculty::getDepartment() const { return department; }

// fills array with the IDs of the advicees and returns the size of the array
void Faculty::getAdviseesIDs(int* outArray, int& outSize) const {
    outSize = numAdvisees; // set output size to number
    for (int i = 0; i < numAdvisees; ++i) { // loop through advisees
        outArray[i] = adviseesIDs[i]; // copy advisee ID to output array
    }
}

// return the number of advisees
int Faculty::getNumAdvisees () const {
    return numAdvisees;
}

// comparison operator for equality based on faculty ID
bool Faculty::operator==(const Faculty& other) const {
    return facultyID == other.facultyID;
}

// comparison operator for less than, based on faculty ID
bool Faculty::operator<(const Faculty& other) const {
    return facultyID < other.facultyID;
}

// comparison operator for greater than, based on faculty ID
bool Faculty::operator>(const Faculty& other) const {
    return facultyID > other.facultyID;
}

// adds on advisee to the faculty list
void Faculty::addAdvisee(int studentID) {
    if (numAdvisees < 100) { // check if the max number of advisees is not exceeded
        adviseesIDs[numAdvisees++] = studentID; // add new advisee
    }
}

// adds advisee to the faculty member's list 
void Faculty::removeAdvisee(int studentID) {
    int index = -1; // initialize index to invalid value
    for (int i = 0; i < numAdvisees; ++i) { // loop through advisees
        if (adviseesIDs[i] == studentID) { // check if current advisees is the one to remove
            index = i; // set index of the advisee to remove
            break;
        }
    }
    if (index != -1) { // if advisee was found
        for (int i = index; i < numAdvisees - 1; ++i) { // shift remaining
            adviseesIDs[i] = adviseesIDs[i + 1];
        }
        numAdvisees--; // decrease count of advisees
    }
}
// overloaded ostream operator 
std::ostream& operator<<(std::ostream& os, const Faculty& faculty) {
    os << "Faculty ID: " << faculty.facultyID << "\n"
       << "Name: " << faculty.name << "\n"
       << "Level: " << faculty.level << "\n"
       << "Department: " << faculty.department << "\n"<< std::endl;
    return os;
}