#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {

public:
    int serviceTimes[3]; // array to store service times at different offices
    std::string officeOrder; // the order in which offices are visited
    int currentClockTick; // when the student arrived at student center
    int currentServiceTime; // holds current service time being processed
    int studentNo; // student number

    // constructor
    Customer(); 
    Customer(int clockTick, int registrarTime, int cashierTime, int financialAidTime, const std::string order, int studentNumber); // parameterized constructor
    
    // total service time for customer
    int getServiceTime() const; // returns integer representing the total time required across all service centers

    // method to check if the customer is finished
    bool isFinished() const; // returns true if the customer is finished, false otherwise
    Customer *point2Next = NULL; // pointer to the next customer in a queue
    Customer *point2Prev = NULL; // pointer to the previous customer in a queue
};

#endif // CUSTOMER_H
