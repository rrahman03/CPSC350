#include <iostream>
#include "LazyBST.h"
#include "Student.h"
#include "Faculty.h"

using namespace std;

void printMenu() { // function to display main menu
    cout << "\n*** University Database System ***\n"; // print title of menu
    cout << "1. Print all students\n"; // menu option to print all student records
    cout << "2. Print all faculty\n"; // menu option to print all faculty records
    cout << "3. Find and display student information\n"; // menu option to find a student
    cout << "4. Find and display faculty information\n"; // menu option to find a faculty member
    cout << "5. Add a new student\n"; // menu option to add a new student record
    cout << "6. Delete a student\n"; // menu option to delete a student record
    cout << "7. Add a new faculty member\n"; // menu option to add a new faculty member
    cout << "8. Delete a faculty member\n"; // menu option to delete a new faculty member
    cout << "9. Change a student’s advisor\n"; // menu option to change a studen't advisor
    cout << "10. Remove an advisee from a faculty member\n"; // menu option to remove advisee
    cout << "11. Exit\n"; // menu option to exit the program
   // cout << "Select an option: ";
}

//template <typename T>
//void writeToFile (T BST, ofstream& outfile){

//}

int main() {
    LazyBST<Student> studentBST;
    LazyBST<Faculty> facultyBST;

    bool running = true; // bool to keep program running until user exists
    // while loop to keep program running
    while (running) {
        printMenu(); // display menue
        cout << "\nSelect an option: "; // prompts user to select menu option
        int choice; // holds user's menu selection
        cin >> choice; // read user's input
        cout << "\n";

        int id; // variable to store an ID for searching
        // switch statement to handle the menu based on user's choice
        switch (choice) {
            case 1:
                studentBST.printTree(); // print all students stored in the tree
                break;

            case 2:
                facultyBST.printTree(); // print all faculty stored in the tree
                break;

            case 3: {
                cout << "Enter student ID: "; // ass user for student ID
                cin >> id; // read the student ID
                Student temp(id, "", "", "", 0.0, 0); // create temp student object
                if (studentBST.find(temp) == nullptr) { // search for student in BST
                    cout << "Student not found.\n"; // if not found, print message
                }
                break;
            }

            case 4: {
                cout << "Enter faculty ID: "; // ask user for a faculty ID
                cin >> id; // read faculty ID
                Faculty temp(id, "", "", ""); // create temp faculty object
                if (facultyBST.find(temp) == nullptr) { // search for faculty in BST
                    cout << "Faculty not found.\n"; // if not found, print message
                }
                break;
            }
            case 5: {
                int studentId, advisorId; // variables to store student and advsor ID
                string name, level, major; // variables to store name, level, and major of the student
                double gpa; // variable to store GPA

                // promt user for student ID and store input
                cout << "Enter student ID: ";
                cin >> studentId; 

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                // promt user to enter name and store input
                cout << "Enter name: ";
                getline(cin, name);

                // promt user to enter level and store input
                cout << "Enter level: ";
                getline(cin, level);

                // promt user to enter major and store input
                cout << "Enter major: ";
                getline(cin, major);

                // promt user to enter GPA and store input
                cout << "Enter GPA: ";
                cin >> gpa;

                // promt user to enter advisor's and store input
                cout << "Enter Advisor Id: ";
                cin >> advisorId;

                // declare a pointer for a faculty node
                TreeNode<Faculty>* facultyNode;
                Faculty temp(advisorId, "", "", ""); // create temp faculty object

                // search for faculty in BST and handle null case
                if ((facultyNode = facultyBST.find(temp)) == nullptr) {
                    cout << "Faculty not found. Student cannot be added.\n";
                    break;
                }

                // create temp student object to check for existing student ID
                Student temp2(studentId, "", "", "", 0.0, 0);

                // check if student ID is already in use
                if (studentBST.find(temp2) != nullptr) {
                    cout << "Student ID in use. Unable to add student.\n";
                }

                // add the student ID to the advisees' list
                facultyNode->key.addAdvisee(studentId);

                // isnert new student into student BST
                studentBST.insert(Student(studentId, name, level, major, gpa, advisorId));
                break;
            }

            case 6: {
                TreeNode<Student>* studentNode; // pointer storing student objects
                cout << "Enter student ID to delete: "; // prompt user to ender student ID to delete
                cin >> id; // read ID
                Student temp(id, "", "", "", 0.0, 0); // temp object

                if ((studentNode = studentBST.find(temp)) == nullptr) { // attempt to remove student
                    cout << "Student not found.\n"; // if removal fails
                    break;
                }

                Faculty temp1(studentNode->key.getAdvisorID(), "", "", ""); // create a temp faculty object

                TreeNode<Faculty>* facultyNode; // declare pointer to store faculty object
                // attempt to find faculty in BST
                // if not found, nullptr is returned
                if ((facultyNode = facultyBST.find(temp1)) == nullptr) {
                    cout << "Faculty not found. Student cannot be deleted.\n";
                    break;
                }
                else {
                    facultyNode->key.removeAdvisee(id); // if faculty is found, remove student ID
                }

                // attempt to remove the student from BST
                if (!studentBST.remove(temp)) {
                    cout << "Student not found or could not be removed.\n";
                }
                break;
            }

            case 7: {
                int facultyId; // variable to store faculty ID
                string name, level, department; // variables to store attributes

                cout << "Enter faculty ID: "; // prompt to enter faculty ID
                cin >> facultyId; // read faculty ID

                // clear the input buffer before reading strings
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter name: "; // prompt to enter faculty name
                getline(cin, name); // read line

                cout << "Enter level: "; // prompt to enter faculty level
                getline(cin, level); // read line

                cout << "Enter department: "; // prompt to enter faculty department
                getline(cin, department); // read line

                // create temp object to see if faculty id is taken
                Faculty temp(facultyId, "", "", "");
                // find faculty in the BST
                if (facultyBST.find(temp) != nullptr) {
                    cout << "Faculty Id in use. Unable too add Faculty\n";
                    break;
                }

                // if faculty ID is ot in use, insert new faculty object into the BST
                facultyBST.insert(Faculty(facultyId, name, level, department));
                break;
            }

            case 8: {
                cout << "Enter faculty ID to delete: "; // prompt user
                cin >> id; // read faculty ID from user input
                Faculty temp(id, "", "", ""); // create a temp object

                TreeNode<Faculty>* facultyNode; // declare a pointer to store faculty objects
                // attempt to find the faculty in BST
                // if not found, nullptr is returned
                if ((facultyNode = facultyBST.find(temp)) == nullptr) {
                    cout << "Faculty not found.\n";
                    break;
                }
                
                // check if faculty memeber has any advisees
                if (facultyNode->key.getNumAdvisees() != 0) {
                    cout << "Faculty has advisees, and cannot be removed.\n";
                    break;
                }
            
                // attempt to remove faculty from BST
                if (!facultyBST.remove(temp)) {
                    cout << "Faculty not found or could not be removed.\n";
                }
                break;
            }

            case 9: 
            case 10: {
                int studentId, newAdvisorId;
                cout << "Enter student ID to change advisor: "; // prompt user to enter student ID
                cin >> studentId; // read student ID from user input
                cout << "Enter new advisor Id: "; // prompt user to enter new advisor's ID
                cin >> newAdvisorId; // read new advisor ID from user input

                TreeNode<Student>* studentNode;
                Student temp(studentId, "", "", "", 0.0, 0); // create a tempory student object

                // find the student and new advisor
                if (((studentNode = studentBST.find(temp)) != nullptr) && (facultyBST.find(Faculty(newAdvisorId, "", "", ""))) != nullptr) {

                    // get old advisors ID and create temp object
                    Faculty temp1(studentNode->key.getAdvisorID(), "", "", ""); 

                    // create updated student object with new advisor ID
                    Student student(studentId, studentNode->key.getName(), studentNode->key.getLevel(), studentNode->key.getMajor(), studentNode->key.getGpa(), newAdvisorId);

                    TreeNode<Faculty>* facultyNode;
                    // find the old advisor in faculty BST
                    if ((facultyNode = facultyBST.find(temp1)) == nullptr) {
                        cout << "Faculty not found. Student cannot be deleted.\n";
                        break;
                    }
                    else {
                        facultyNode->key.removeAdvisee(studentId);
                    }
                    // remove the old student record from BST
                    if (!studentBST.remove(temp)) {
                        cout << "Student not found or could not be removed.\n";
                    }
                        // find new advusor in faculty BST
                        Faculty temp2(student.getAdvisorID(), "", "", "");
                        facultyNode = facultyBST.find(temp2);
                        facultyNode->key.addAdvisee(studentId);
                        studentBST.insert(student);
                    } 

                else {
                    cout << "Invalid student or faculty ID.\n";
                }
                break;
            }

            case 11:
                running = false; // flag to stop running the loop
                break;
            default:
                cout << "Invalid option. Please try again.\n"; // handle invalid menu options
        }
    }

    // write to file before exiting
    // it writes the current state of the student and faculty BSTs to a file
    ofstream outFile("runLog.txt");
    if (outFile.is_open()) {
        outFile << "Students:\n\n";
        studentBST.printTree(outFile);
        outFile << "\nFaculty:\n\n";
        facultyBST.printTree(outFile);
        outFile.close();
    } else {
        cout << "Unable to open file for writing.\n";
    }

    return 0;
}
