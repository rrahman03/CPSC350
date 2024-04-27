#ifndef SERVICECENTER_H
#define SERVICECENTER_H

#include "Office.h"  
#include "DblList.h" 
#include <string>

class ServiceCenter {
private:
    Office registrar; // manages registrar window queues
    Office cashier; // manages cashier window queues
    Office financialAid; // manages financial aid window queues
    
    ListQueue serviceCenterQueue; // queue for all incoming student requests

    ListQueue registrarQueue; // queue for registrar
    ListQueue cashierQueue; // queue for cashier
    ListQueue financialAidQueue; // queue for financial aid
   
    ListQueue workDoneQueue; // queue for students who have finished all services

    int simulationClock; // tracks current time in simulation
    int studentNo = 0; // counter for number of students processed

public:

    // constructor 
    // takes number of windows for each office
    ServiceCenter(int numWindowsRegistrar, int numWindowsCashier, int numWindowsFinancialAid);
    
    // process arrivals based on current time and student details
    void processArrivals(int currentTime, DblList& studentDetails);
    
    // simulates operations for a day based on data from file
    void simulateDay(const std::string& filename); 
    // adds student to service center queue
    void addStudentServiceCenterQueue(int currentClockTick, int registrarTime, int cashierTime, int financialAidTime, std::string order);
    // moves student to correct office queue based on current clock tick
    void moveStudentToOfficeQue(int currentClockTick);
    // directs a student to correct office queue based on their needs
    void moveToOfficeWindowQueue (Customer headOftheServiceCenterQueue);
    // service all windows
    void serviceAllWindows(); 
    // checks if there are students currently in any queue
    bool checkStudentsPresent();
    // displays performance metrics
    void displayMetrics();
};

#endif 
