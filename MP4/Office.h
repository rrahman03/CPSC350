#ifndef OFFICE_H
#define OFFICE_H

#include "Window.h" 
#include "ListQueue.h" 
#include "Customer.h"


class Office {
private:
    ListQueue customers; // queue of students waiting for service
    int numOfficeWindows = 0; // number of service windows in the office
    Window* officeWindows; // dynamic array of windows

public:
    int numberOfStudentsServed=0; // counter for number of students served
    double totalWaitTime = 0; // total waiting time for all students
    int longestWaitTime = 0; // longest wate time for student
    int noOfStudentsWaitingOver10Minutes = 0; // count of students who waited over 10 minutes
    double totalWindowIdleTime = 0; // total idle time for all windows
    int longestWindowIdleTime = 0; // longest idle time for any window
    int numLongIdles = 0; // number of windows idle for more than 5 minutes

    Office(); // constructor

    // methods to handle the queue and service windows
    void addCustomer(const Customer& customer); // new student to service queue
    void updateMetrics(); // update the office metrics after servicing students
    void displayMetrics() const; // display the metrics for this office
    void initializeWindows(int numWindows); // initialize service windows
    // function to manage helping students over different windows and queues
    void serviceCustomers(ListQueue* queue, ListQueue* registrarQueue, ListQueue* cashierQueue, ListQueue* financialAidQueue, int clock);
    bool allOfficeWindowsEmpty(); // checks if all service windows are empty
    int returnNoOfWindows (); // returns the number of service windows

};

#endif
