#include "ServiceCenter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

// constructor 
ServiceCenter::ServiceCenter(int numWindowsRegistrar, int numWindowsCashier, int numWindowsFinancialAid) {
    registrar.initializeWindows(numWindowsRegistrar); // initialize the registrar office windows
    cashier.initializeWindows(numWindowsCashier); // initlialize the cashier office windows
    financialAid.initializeWindows(numWindowsFinancialAid); // initialize the financial aid office windows

}

// process arrivals
// meant to handle the arrival of students
void ServiceCenter::processArrivals(int currentTime, DblList& studentDetails) {
    for (auto it = studentDetails.begin(); it != studentDetails.end(); ++it) {
        // iteration logic to process student details
    }
}

// adds student to central queue of the service center
void ServiceCenter::addStudentServiceCenterQueue(int currentClockTick, int registrarTime, int cashierTime, int financialAidTime, std::string order){
    studentNo++; // increment student number
    Customer newCustomer (currentClockTick, registrarTime, cashierTime, financialAidTime, order, studentNo);
    serviceCenterQueue.enqueue(newCustomer); // enqueue new student into service center queue
}

// move the student to the appropriate office queue based on the current clock tick
void ServiceCenter::moveStudentToOfficeQue(int currentClockTick) {
    Customer headOftheServiceCenterQueue; // temporary customer object
    
    simulationClock = currentClockTick; // update the simulation clock

    if (!serviceCenterQueue.isEmpty()){ // check if the central queue is not empty
        headOftheServiceCenterQueue = serviceCenterQueue.peekFront(); // peek at the front of the queue
        while (currentClockTick == headOftheServiceCenterQueue.currentClockTick) { // process all students due at the current time
            
            std::cout << "Student " << headOftheServiceCenterQueue.studentNo 
                   << " joined an office queue" << std::endl; // log student joining queue

            moveToOfficeWindowQueue (headOftheServiceCenterQueue); // move student to the appropriate office queue
            serviceCenterQueue.moveHeadToNext(); // move head to next student in the central queue
            if (!serviceCenterQueue.isEmpty()){
                headOftheServiceCenterQueue = serviceCenterQueue.peekFront(); // update head of the queue

            }
            else break;  // if no more students are in the queue         
        }
    }

}

// check if there are any students present in any queue
bool ServiceCenter::checkStudentsPresent(){
    if (registrar.allOfficeWindowsEmpty() && cashier.allOfficeWindowsEmpty() && financialAid.allOfficeWindowsEmpty() 
                && serviceCenterQueue.isEmpty() && registrarQueue.isEmpty() && cashierQueue.isEmpty() && financialAidQueue.isEmpty()) return (false);
    else 
        return (true);
}

// assigns a new student to the correct office based on their order
void ServiceCenter::moveToOfficeWindowQueue(Customer newStudent) {

    size_t firstNonSpace = newStudent.officeOrder.find_first_not_of(" "); // find the first non-space character in the order string

    if (firstNonSpace != std::string::npos) {
        char firstChar = newStudent.officeOrder[firstNonSpace]; // get character that indicates the next serviced office

        newStudent.officeOrder.erase(firstNonSpace, 1); // remove this character from the order string

        switch (firstChar){ // route the student to the appropiate office queue
            case 'R':
                newStudent.currentServiceTime = newStudent.serviceTimes[0]; // set service time for registrar 
                registrarQueue.enqueue(newStudent); // enqueue to registrar 
                std::cout << "Student " << newStudent.studentNo << " waiting for a Registrar window with service time " << newStudent.currentServiceTime << std::endl;
                registrar.numberOfStudentsServed++; // incremement number of students served at registrar
                break;
            case 'C':
                newStudent.currentServiceTime = newStudent.serviceTimes[1]; // set service time for cashier
                cashierQueue.enqueue(newStudent); // enqueue to cashier
                std::cout << "Student " << newStudent.studentNo << " waiting for Cashier window with service time " << newStudent.currentServiceTime << std::endl;
                cashier.numberOfStudentsServed++; // increment number of students served at cashier
                break;
            case 'F':
                newStudent.currentServiceTime = newStudent.serviceTimes[2]; // set service time for financial aid
                financialAidQueue.enqueue(newStudent); // enqueue to financial aid
                std::cout << "Student " << newStudent.studentNo << " waiting for FinancialAid window with service time " << newStudent.serviceTimes[2] << std::endl;
                financialAid.numberOfStudentsServed++; // increment number of students served at financial aid
                break;

        }
        
    }
    

}

// display metrics calculated
void ServiceCenter::displayMetrics() {
    // display mean, longest wait times, etc
    if (registrar.numberOfStudentsServed != 0) {
        std::cout << "Mean student wait time at Registrar: " << registrar.totalWaitTime / registrar.numberOfStudentsServed << std::endl;
    }
    else   {
            std::cout << "Mean student wait time at Registrar: " << 0 << std::endl;
    }
    std::cout << "Longest student wait time at Registrar: " << registrar.longestWaitTime << std::endl;

   
    if (cashier.numberOfStudentsServed != 0) {
        std::cout << "Mean student wait time at Cashier: " << cashier.totalWaitTime / cashier.numberOfStudentsServed << std::endl;
    }
    else {
        std::cout << "Mean student wait time at Cashier: " << 0 << std::endl;
    }
    std::cout << "Longest student wait time at Cashier: " << cashier.longestWaitTime << std::endl;


    if (financialAid.numberOfStudentsServed != 0) {
        std::cout << "Mean student wait time at Financial Aid: " << financialAid.totalWaitTime / financialAid.numberOfStudentsServed << std::endl;
    }
    else {
                std::cout << "Mean student wait time at Financial Aid: " << 0 << std::endl;
    }
    std::cout << "Longest student wait time at Financial Aid: " << financialAid.longestWaitTime << std::endl;

    std::cout << "Total number of students waiting over 10 minutes across all offices: " 
            << registrar.noOfStudentsWaitingOver10Minutes + cashier.noOfStudentsWaitingOver10Minutes 
            + financialAid.noOfStudentsWaitingOver10Minutes << std:: endl;

    int totalWindows = registrar.returnNoOfWindows() + cashier.returnNoOfWindows() + financialAid.returnNoOfWindows();
    double totalWindowIdleTime = registrar.totalWindowIdleTime + cashier.totalWindowIdleTime + financialAid.totalWindowIdleTime;

    std::cout << "Mean window idle time :" << totalWindows / totalWindowIdleTime << std::endl;

    std::cout << "Longest window idle time for Registrar: " << registrar.longestWindowIdleTime << std::endl;
    std::cout << "Longest window idle time for Cashier: " << cashier.longestWindowIdleTime << std::endl;
    std::cout << "Longest window idle time for Financial Aid: " << financialAid.longestWindowIdleTime << std::endl;

    std::cout << "Number of windows idle for over 5 minutes across all offices: " << registrar.numLongIdles
        + cashier.numLongIdles + financialAid.numLongIdles << std::endl;
}

// service all windows, updating each office queue
void ServiceCenter::serviceAllWindows() {
    std::cout << "Servicing Registrar windows" << std::endl;
    registrar.serviceCustomers(&registrarQueue, &registrarQueue, &cashierQueue, &financialAidQueue, simulationClock); // service registrar windows
    std::cout << "Servicing Cashier windows" << std::endl;
    cashier.serviceCustomers(&cashierQueue, &registrarQueue, &cashierQueue, &financialAidQueue, simulationClock); // service cashier windows
    std::cout << "Servicing FinancialAid windows" << std::endl;
    financialAid.serviceCustomers(&financialAidQueue, &registrarQueue, &cashierQueue, &financialAidQueue, simulationClock); // service financial aid windows

}

// simulate based on input file
void ServiceCenter::simulateDay(const std::string& filename) {
    std::ifstream file(filename); // open the file
    std::string line;
    DblList studentQueue; // list to store student details

    if (file.is_open()) {
        while (getline(file, line)) { // read each line from the file
            std::stringstream ss(line); // use stringstream to parse the line
            int time;
            std::string order;
            ss >> time >> order; // extract time and order from the line
        }
        file.close(); // close the file
    }
    
    int currentTime = 0; // initialize current time
    processArrivals(currentTime, studentQueue); // process all arrivals
}