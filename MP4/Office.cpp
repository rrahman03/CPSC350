#include "Office.h"
#include "Window.h"
#include "Customer.h"
#include "DblList.h"
#include "ListQueue.h"
#include "ServiceCenter.h"
#include <iostream>
#include <iostream>

// constructor
Office::Office() 
{}

// initialize array of windows in the office
void Office::initializeWindows(int numWindows) {
    numOfficeWindows = numWindows; // store the number of windows
    officeWindows = new Window[numOfficeWindows]; // allocate memory
}

// returns the number of windows 
int Office::returnNoOfWindows () {
    return (numOfficeWindows); // return the stored number of office windows
}

// adds a customer to the office queue
void Office::addCustomer(const Customer& customer) {
    customers.enqueue(customer); // adds a new student to the queue of students waiting for service
}

// checks if all windows are currently not serving any customers
bool Office::allOfficeWindowsEmpty() 
{
    bool returnVal = true; // all windows are empty
    for (int i = 0; i < numOfficeWindows; i++) { // iterate over all windows
        if (!officeWindows[i].isEmpty()) returnVal = false; // set to false if any window is not empty

    }
    return (returnVal); // return whether all windows are empty or not
}

// customers are moved to and from queues and status is being updated
void Office::serviceCustomers(ListQueue* queue, ListQueue* registrarQueue, ListQueue* cashierQueue, ListQueue* financialAidQueue, int clock) 
{

    for (int i = 0; i < numOfficeWindows; i++){ // iterate over each window
        if (officeWindows[i].isEmpty()) { // if current window is empty
            if(!queue->isEmpty()) { // check if any students are in main queue
                
                officeWindows[i].currentCustomer = new Customer; 

                *officeWindows[i].currentCustomer = queue->peekFront(); // assign the customer at the front of the queue to this window
                std::cout << "Student " << officeWindows[i].currentCustomer->studentNo << " arrived at window " << i+1 << " of " << numOfficeWindows << " for service time " << queue->peekFront().currentServiceTime << std::endl;
                numberOfStudentsServed++; 
                int studentWaitTime = clock - queue->peekFront().currentClockTick; // calculate wait time for the student
                totalWaitTime = totalWaitTime + studentWaitTime; // update total wait time
                if (studentWaitTime > longestWaitTime) longestWaitTime = studentWaitTime; // save longest wait time for the office
                if (studentWaitTime > 10) noOfStudentsWaitingOver10Minutes++; // increment count of students who waited over 10 minutes
                totalWindowIdleTime = totalWindowIdleTime + clock - officeWindows[i].windowIdleClockStart; // update total idle time
                if (longestWindowIdleTime < (clock - officeWindows[i].windowIdleClockStart)) longestWindowIdleTime = (clock - officeWindows[i].windowIdleClockStart); // update the longest window idle time
                if ((clock - officeWindows[i].windowIdleClockStart) > 5 ) numLongIdles++; // increment the counter of windows idle over 5 minutes
                queue->moveHeadToNext(); // move to the head of the queue to the next customer

            }
            
        }

        else {
            if (officeWindows[i].currentCustomer->currentServiceTime != 0) { // if student is not done at window
                officeWindows[i].currentCustomer->currentServiceTime--; // decrease remaining service time by one
                std::cout << "Student " << officeWindows[i].currentCustomer->studentNo << 
                     " at window " << i+1 << " of " << numOfficeWindows << " with time remaining: " << officeWindows[i].currentCustomer->currentServiceTime << std::endl;
            }
            else { // if students service time has ended
                Customer moveCustomer = *officeWindows[i].currentCustomer;

                officeWindows[i].windowIdleClockStart = clock; // reset idle start time for the window

                size_t firstNonSpace = moveCustomer.officeOrder.find_first_not_of(" "); 

                if (firstNonSpace != std::string::npos) { // if there is a non-space character
                    char firstChar = moveCustomer.officeOrder[firstNonSpace];

                    moveCustomer.officeOrder.erase(firstNonSpace, 1); // remove character from order

                    switch (firstChar){ // determine the next queue 
                        case 'R': // registrar
                            moveCustomer.currentServiceTime = moveCustomer.serviceTimes[0]; // set service time for registrar
                            officeWindows[i].currentCustomer->currentClockTick = clock; // update the clock tick for the current customer
                            registrarQueue->enqueue(moveCustomer); // enqueue the student to the registrar queue
                            std::cout << "Student " << moveCustomer.studentNo << " moving to Registrar queue with service time " << moveCustomer.currentServiceTime << std::endl;
                            break;
                        case 'C': // cashier
                            moveCustomer.currentServiceTime = moveCustomer.serviceTimes[1]; // set service time for cashier
                            officeWindows[i].currentCustomer->currentClockTick = clock; // update clock tick for current student
                            cashierQueue->enqueue(moveCustomer); // enqueue the student to cashier queue
                            std::cout << "Student " << moveCustomer.studentNo << " moving to Cashier queue with service time " << moveCustomer.currentServiceTime << std::endl;

                            break;
                        case 'F': // financial aid
                            moveCustomer.currentServiceTime = moveCustomer.serviceTimes[2]; // set service time for financial aid
                            officeWindows[i].currentCustomer->currentClockTick = clock; // update clock tick for current student
                            financialAidQueue->enqueue(moveCustomer); // enqueue the student to the financial aid queue
                            std::cout << "Student " << moveCustomer.studentNo << " moving to FinancialAid queue with service time " << moveCustomer.currentServiceTime << std::endl;

                            break;
                    }

                }
                officeWindows[i].currentCustomer = nullptr; // clear current student from the window
            }
        }
   
    }
}



void Office::updateMetrics() {
    // placeholder function
}

void Office::displayMetrics() const {
    // display metrics for office
    std::cout << "Office Metrics:" << std::endl;
    std::cout << "Mean Wait Time: " << (totalWaitTime / customers.getSize()) << std::endl;
    std::cout << "Longest Wait Time: " << longestWaitTime << std::endl;
}
