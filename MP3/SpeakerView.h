#ifndef SPEAKERVIEW_H
#define SPEAKERVIEW_H

#include <string>

class SpeakerView {
private:
    int rows; // number of rows
    int columns; // number of columns
    float** seatingArray; // 2D array to store the seating heights

    void allocateSeatingArray(int nRows, int nColumns); // allocates memory for seatingArray
    void clearSeatingArray(); // deallocates memory allocated for seatingArray                           

public:
    // constructor
    SpeakerView(int nRows, int nColumns);
    // destructor 
    ~SpeakerView();                      

    bool readSeatingArrangement(const std::string& filename); // reads the seating arrangment from a file and stores it
    void computeVisibility(); // computes the visibility from all columns
    void computeVisibilityForColumn(int col); // computes the visibilty for specific columns

    bool validateSeatingArray(std::ifstream& file); // validates content of seating arrangement
};

#endif 
