#ifndef WINDOW_H
#define WINDOW_H

#include "Customer.h"

class Window {
private:
    bool isIdle; // state of the window
    int idleTime; // time the window has been idle

public:
    int totalWindowIdleTime = 0; // total idle time for this window
    int totalStudentsServed = 0; // count of total students served at window
    int windowIdleTimeUntilNext = 0; // idle time until next student is served
    int longestIdleTime = 0; // longest period the window has been idle
    int windowIdleClockStart = 1; // the start time for current idle period
    Customer* currentCustomer = nullptr; // pointer to the currently served customer

    // constructor
    Window();

    // check if the window is idle
    bool getIdleState() const;

    // returns true if no student is currently being served
    bool isEmpty();

    // get the idle time of the window
    int getIdleTime() const;

    // assign a customer to the window
    void serveCustomer(Customer* customer);

    // update the window state for a time tick
    void updateTimeTick();

    // release the customer if their service is complete
    void releaseCustomer();

    // increment the idle time
    void incrementIdleTime();

    // reset the idle time to zero
    void resetIdleTime();

    // destructor
    ~Window();
};

#endif
