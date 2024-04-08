#include "SpeakerView.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// enter the program
int main(int argc, char** argv) {
    if (argc < 2) { // checking for the filename argument
        std::cerr << "Usage: " << argv[0] << " seating.txt" << std::endl; // error message if no filename is provided
        return 1; // return with error
    }

    std::string filename = argv[1]; // store the filename
    
    std::ifstream file(filename); // open the file for reading
    std::string line; // holds each line read from the file
    int row_count = 0; // count of rows
    int column_count = 0; // count of columns

    if (file.is_open()) { // check if the file is successfully open
        while (std::getline(file, line)) { // read file line by line
            ++row_count; // incrememnt row count for each line read
            if (row_count == 1) { // if it's the first line, determine the number of columns
                std::istringstream iss(line); // create a string stream from line
                std::string token; // holds each tokem in the line
                while (iss >> token) {
                    ++column_count; // incrememnt column count for each token
                }
            }
        }
        file.close(); // close file after reading
    } else {
        std::cerr << "Unable to open file" << std::endl; // error message
        return 1; // return error code
    }

    // row and column counts
    SpeakerView view(row_count, column_count);
    if (!view.readSeatingArrangement(filename)) { // read the seating arragement from the file
        return 1;
    }

    view.computeVisibility(); // compute and print visibility for each column

    return 0;
}
