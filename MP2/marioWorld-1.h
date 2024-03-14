#ifndef MARIOWORLD_H
#define MARIOWORLD_H
#include <fstream>

class marioWorld {
private:
    void placeObjects(int level, char object, int count); // helper function to place multiple objects
    void placeObjectRandomly(int level, char object); // places a single object randomly within a level

public:
    int L; // number of levels
    int N; // dimension of each level (NxN grid)
    char*** worldArray; // 3D array of characters for the game world
    marioWorld(int levels, int dimension); // constructor
    ~marioWorld(); // destructor

    void setValueInWorld (int level, int row, int col, char val);
    void createMarioWorld(); // creates the world
    void setupMarioWorld(int percentageCoins, int percentageNothing, int percentageGoombas, int percentageKoopas, int percentageMushrooms); // Sets up the world with objects
    void printWorld(std::ofstream& outputFile, int levelToPrint); // prints the entire game world for debugging


    // return types for getter functions
    char*** getWorldArray() const { return worldArray; }
    int getLevels() const { return L; }
};

#endif // MARIOWORLD_H
