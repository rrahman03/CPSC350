#include "Customer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

// default constructor
Customer::Customer() : serviceTimes{0, 0, 0}, officeOrder("") {
}

// parameterized constructor 
Customer::Customer(int clockTick, int registrarTime, int cashierTime, int financialAidTime, const std::string order, int studentNumber)
    : officeOrder(order) { // initialize officeOrder

    char officeChar; // stores office type
    int j = 0; // index to access service time array 
    int servTimeArray[3]; // array to hold initial service times

    // setting initial service times
    servTimeArray[0] = registrarTime;
    servTimeArray[1] = cashierTime;
    servTimeArray[2] = financialAidTime;

    // initialize all service times to 1
    serviceTimes[0] = 1; // initialize service time for the registrar
    serviceTimes[1] = 1; // initialize service time for the cashier
    serviceTimes[2] = 1; // initialize the service time for the financial aid office
    studentNo = studentNumber; // assign student number

    // office order and corresponding service times
    for (int i = 0; i < order.length(); ++i)
    {
        if (order[i] != ' ' ) { // skip spaces
            switch (order[i]) {
                case 'R': // 'R' for registrar
                    serviceTimes[0] = servTimeArray[j];
                    break;
                case 'C': // 'C' for cashier
                    serviceTimes[1] = servTimeArray[j];
                    break;
                case 'F': // 'F' for financial aid
                    serviceTimes[2] = servTimeArray[j];
                    break;
            }
            j++; // move to the next service time in the array
        }
    }
    currentClockTick = clockTick; // store the current clock tick
}

// function to get the total service time for the customer
int Customer::getServiceTime() const {
    int totalServiceTime = 0; // variable to hold overall service time
    for (int time : serviceTimes) { // loop through the service times array
        totalServiceTime += time; // accumulate the total service time
    }
    return totalServiceTime; // return the total calculated service time
}

// checks if all services are completed
bool Customer::isFinished() const {
    // check if all service times are zero (completed)
    for (int time : serviceTimes) { // iterate over each service time
        if (time > 0) { // if there is any service time greater than zero
            return false; // if any service time is remaining
        }
    }
    return true; // if all service times are zero, the customer is finished
}
