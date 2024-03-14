#include "marioWorld.h"
#include <iostream>
#include <fstream>
#include <cstdlib> // For rand() and srand()
#include <ctime> // For time()

// constructor
// initializes the world with given levels and dimensions
marioWorld::marioWorld(int levels, int dimension) : L(levels), N(dimension) {}

// destructor
// deallocates memory used for the 3D world array.
marioWorld::~marioWorld() {
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < N; ++j) {
            delete[] worldArray[i][j]; // delete each row in a level
        }
        delete[] worldArray[i]; // delete each level
    }
    delete[] worldArray; // delete the array of levels
}

// createMarioWorld
// allocates memory for the 3D world array and initializes all cells to 'x'
void marioWorld::createMarioWorld() {
   // L = noOfLevels;
   // N = dimensionOfGrids;
    worldArray = new char**[L]; // allocates memory for levels
    for (int i = 0; i < L; ++i) {
        worldArray[i] = new char*[N]; // allocates memory for rows in each level
        for (int j = 0; j < N; ++j) {
            worldArray[i][j] = new char[N]; // allocates memory for columns in each row
            for (int k = 0; k < N; ++k) {
                worldArray[i][j][k] = 'x'; // initialize all cells to 'x' indicating empty
            }
        }
    }
}

// setupMarioWorld: randomly distributes coins, goombas, etc
void marioWorld::setupMarioWorld(int percentageCoins, int percentageNothing, int percentageGoombas, int percentageKoopas, int percentageMushrooms) {
    srand(time(NULL)); // different outcomes each run
    for (int l = 0; l < L; ++l) {
        // distribute objects based on specified percentages by placing them randomly
        int numCells = N * N; // calculates total number of cells in a level
        // objects are distributed based on percentage
        placeObjects(l, 'c', (numCells * percentageCoins) / 100); // places coins
        placeObjects(l, 'g', (numCells * percentageGoombas) / 100); // places Goombas
        placeObjects(l, 'k', (numCells * percentageKoopas) / 100); // places Koopas
        placeObjects(l, 'm', (numCells * percentageMushrooms) / 100); // places mushrooms

        
        // a boss ('b') and a a warp pipe ('w') are placed
        placeObjectRandomly(l, 'b'); // place the boss
        if (l < L - 1) placeObjectRandomly(l, 'w'); // place a warp pipe except in last level
    }
}

// placeObjects
// helper function to place a specified number of a single type of object randomly in a level
void marioWorld::placeObjects(int level, char object, int count) {
    for (int i = 0; i < count; ++i) {
        placeObjectRandomly(level, object); // place each object randomly
    }
}

// placeObjectRandomly
// places a single object in a random empty cell 
void marioWorld::placeObjectRandomly(int level, char object) {
    int r, c;
    do {
        r = rand() % N; // random row index
        c = rand() % N; // random column index
    } while (worldArray[level][r][c] != 'x'); // repeat until an empty cell is found
    worldArray[level][r][c] = object; // place the object in the found empty cell
}

// setValueInWorld
// a specific value is put in the world array
void marioWorld::setValueInWorld (int level, int row, int col, char val) {
    worldArray[level][row][col] = val; // sets the value
}

// printWorld
// outputs the entire game world to the console for debugging purposes
void marioWorld::printWorld(std::ofstream& outputFile, int levelToPrint) {
    outputFile << "\nLevel " << levelToPrint << " world" << std:: endl; // prints level number
    for (int j = 0; j < N; ++j) {
        for (int k = 0; k < N; ++k) {
            outputFile << worldArray[levelToPrint][j][k] << " "; // print each cell in the grid
        }
            outputFile << std::endl; // new line at the end of each row
        }
        outputFile << "==========" << std::endl; // prints separator line
}

