#include "SpeakerView.h"
#include "MonoStack.h"
#include <iostream>
#include <fstream>
#include <sstream>

// constructor
SpeakerView::SpeakerView(int nRows, int nColumns) : rows(nRows), columns(nColumns) {
    allocateSeatingArray(nRows, nColumns); // initialize the seating array
}

// destructor
SpeakerView::~SpeakerView() {
    clearSeatingArray(); // clear the seating array
}

// allocates the seating array
void SpeakerView::allocateSeatingArray(int nRows, int nColumns) {
    seatingArray = new float*[nRows]; // allocates memory for rows
    for (int i = 0; i < nRows; i++) {
        seatingArray[i] = new float[nColumns]; // allocates memory for columns
    }
}

// clears the seating array
void SpeakerView::clearSeatingArray() {
    if (seatingArray) { // checks if seating array is null
        for (int i = 0; i < rows; i++) {
            delete[] seatingArray[i]; // deletes each column array
        }
        delete[] seatingArray; // delete the row array
        seatingArray = nullptr; // seatingArray pointer is set to null
    }
}

// validates the seating array dimensions
bool SpeakerView::validateSeatingArray(std::ifstream& file) {
    std::string line; // string to hold each line read from the file
    int rowCount = 0; // counter for number of rows read
    while (std::getline(file, line)) { // read lines from the file until end of file
        std::istringstream iss(line); // string stream to read from line
        float height; // holds height values read from the line
        int columnCount = 0; // counts the number of columns
        while (iss >> height) { // reads height values from the line
            columnCount++; // increment the column counter
        }
        if (rowCount == 0) { // set the number of columns
            columns = columnCount;
        } else if (columnCount != columns) { // check if the current row has the same amount of columns as the first row
            std::cerr << "Inconsistent number of heights in row " << rowCount << std::endl;
            return false; // return false if column number does not match
        }
        rowCount++;
    }
    if (rowCount != rows) { // check if the number of rows is consistent 
        std::cerr << "Inconsistent number of rows. Expected: " << rows << ", but found: " << rowCount << std::endl;
        return false; // returns false if inconsistent
    }
    return true; // return true if seating array dimensions work
}

// reads seating arrangements from a file
bool SpeakerView::readSeatingArrangement(const std::string& filename) {
    std::ifstream file(filename); // open the file for reading
    if (!file) { // check if the file failed to open
        std::cerr << "Could not open the file: " << filename << std::endl;
        return false;
    }

    if (!validateSeatingArray(file)) { // validate seating array dimensions
        file.close(); // close the file
        return false; //return false if seating array dimensions do not work
    }

    file.clear();
    file.seekg(0, std::ios::beg); // seek to the beginning of the file

    std::string line; // string to hold each line read from the file
    int currentRow = 0; // counter for the current row being read
    while (std::getline(file, line) && currentRow < rows) { // read lines from the file until the end
        std::istringstream iss(line); // string stream used to read from the line
        float height; // variable to hold height values read from the line
        int currentColumn = 0; // counter for current column being filled
        while (iss >> height && currentColumn < columns) { // read height values and fill seating array
            seatingArray[currentRow][currentColumn] = height; // assign height values to the seating array
            currentColumn++;
        }
        if (currentColumn != columns) { // checks if current row has enough height values
            std::cerr << "Error: Row " << currentRow << " does not contain enough height values." << std::endl;
            file.close(); // close the file
            return false; // return false if there are not enough height values in the current row
        }
        currentRow++;
    }
    if (currentRow != rows) { // checks if enough rows were provided
        std::cerr << "Error: Not enough rows of height values were provided in the file." << std::endl;
        file.close(); // close the file
        return false; // return false if not enough rows were provided
    }

    file.close(); // close the file
    return true;
}

// computes visibility for a single column using MonoStack
void SpeakerView::computeVisibilityForColumn(int col) {
    MonoStack stack(rows, 'd'); // 'd' for decreasing stack
    int visibleCount = 0; // counter for the number of visible seat

    for (int row = 0; row < rows; row++) { // iterate through each row
        if (stack.peek() == -1 || seatingArray[row][col] > stack.peek()) { // check if current seat is visible
            visibleCount++;
            stack.push(seatingArray[row][col]); // push the current seat's height onto the stack
        }
    }

    // print the number of seats in the current column that have obstructed views
    std::cout << "In column " << col << ", there are " << visibleCount << " seats that can see. Their heights are: ";
    while (stack.peek() != -1) {
        std::cout << stack.pop() << " inches. "; // pop and print each seat's height from the stack
    }
    std::cout << std::endl;
}

// computes visibility for each column
void SpeakerView::computeVisibility() {
    for (int col = 0; col < columns; col++) { // iterate through each column
        computeVisibilityForColumn(col); // function to compute visibility for the current column
    }
}
