#include <iostream>
#include <fstream>
#include <string>
#include "Office.h"
#include "Window.h"
#include "Customer.h"
#include "DblList.h"
#include "ListQueue.h"
#include "ServiceCenter.h"

// entry point of program
int main(int argc, char** argv) {
    // check ifprogram was run with at least one command-line argument
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1; // return error code
    }

    // store filename
    std::string filename = argv[1];
    // open the file for reading
    std::ifstream inputFile(filename);
    if (!inputFile) { // check if file was successfully opened
        std::cerr << "Error opening input file: " << filename << std::endl;
        return 1; // return error code
    }

    // read number of windows for three different service types from the input file
    int numWindowsRegistrar, numWindowsCashier, numWindowsFinancialAid;
    inputFile >> numWindowsRegistrar >> numWindowsCashier >> numWindowsFinancialAid;

    // create a service center object with specified number of windows for each service type
    ServiceCenter serviceCenter(numWindowsRegistrar, numWindowsCashier, numWindowsFinancialAid);

    // declare variables to store the current simulation time and number of students
    int currentClockTick, numStudents;
    std::string order; // variable to store order details

    // read data from file until EOF
    while (inputFile >> currentClockTick >> numStudents) {
        // process each student read from file
        for (int i = 0; i < numStudents; i++) {
            int time1, time2, time3; // variable to store service times for each window type
            inputFile >> time1 >> time2 >> time3; // read the service times
            getline(inputFile, order); // read the remaining part of the line as the order

            // add student to service center
            serviceCenter.addStudentServiceCenterQueue(currentClockTick, time1, time2, time3, order);//
        }
    }

    // output of the start of simulation 
    std::cout << "Simulation Logs:" << std::endl;

    // initialize clock tick for simulation
    currentClockTick = 1;
    // run the simulation while there are still students in line
    while (serviceCenter.checkStudentsPresent()) { 
        std::cout << "Clock:" << currentClockTick << std::endl; // output the current clock tick
        serviceCenter.moveStudentToOfficeQue(currentClockTick); // move student to correct queue
        serviceCenter.serviceAllWindows(); // process services at all windows

        currentClockTick++; // increment the simulation clock tick
        
        
    }

    inputFile.close(); // close the input file

    // output simulation results
    std::cout << std::endl;
    std::cout << "Simulation Metrics:" << std::endl;
    serviceCenter.displayMetrics(); // display the colelcted metrics from the simulation

    return 0; // end of program
}
