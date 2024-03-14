#include "marioGamePlay.h"
#include "marioWorld.h"
#include <iostream>

// constructor
marioGamePlay::marioGamePlay(marioWorld *world, int life) 
    : noOfPlayLevels(world->L), // initializes the number of levels
      noOfPlayDimensionOfGrid(world->N), // initializes dimensions of the grid
      marioLife(life), // initiliazes Mario's life
      currentLevel(0), // start Mario at level 0
      marioPosRow(0), // initializes Mario's row position
      marioPosCol(0), // initializes Mario's column position
      marioPL(0), // initiliazes Mario's power level
      marioCoins(0) { // initializes Mario's coin count
        marioPosRow = rand() % noOfPlayDimensionOfGrid; // Mario's random row position on the grid
        marioPosCol = rand() % noOfPlayDimensionOfGrid; // Mario's random column position on the grid
        world3D = world->worldArray; // local 3D world array
        while (world3D[currentLevel][marioPosRow][marioPosCol] == 'b'|| 
                world3D[currentLevel][marioPosRow][marioPosCol] == 'w') { // make sure boss or warp pipe is not in the random location where Mario will start at 
            marioPosRow = rand() % noOfPlayDimensionOfGrid; // get Mario's random row position on the grid again
            marioPosCol = rand() % noOfPlayDimensionOfGrid; // get Mario's random column position on the grid again
        }
    world3D[currentLevel][marioPosRow][marioPosCol]= 'H'; // puts Mario at a random position
    
}
// destructor
marioGamePlay::~marioGamePlay() {

}

std::string marioGamePlay::marioInteraction() {
    char cellContent = world3D[currentLevel][marioPosRow][marioPosCol]; // the cell where Mario is
    int win; // store the results of the battles
    if (defeatedEnemies > 6) { // if Mario defeated more than 6 enemies, his life increases
        marioLife++;
        defeatedEnemies = 0;
    }
    switch(cellContent) { // switch case based on what is in the cell
        case 'c': // if it's a coin
            collectCoin(); // call method to collect a coin
            return "Mario collected a coin. ";
        case 'm': // if it's a mushroom
            eatMushroom(); // call method to collect a mushroom
            return "Mario got a mushroom. ";
        case 'g': // goomba
            win = fightGoomba(); // fight a Goomba and store the result
            if (win == 1) {
                defeatedEnemies++;
                return "Mario encountered a Goomba and won. ";
            }
            else if (win == -1) {
                defeatedEnemies = 0;
                return "Mario encountered a Goomba and lost. ";
            }
            else return "Mario encountered a Goomba and died. ";
        case 'k': // koopa
            win = fightKoopa(); // fight a Koopa and store the result
            if (win == 1) {
                defeatedEnemies++;
                return "Mario encountered a Koopa and won. ";
            }
            else if (win == -1) {
                defeatedEnemies = 0;
                return "Mario encountered a Koopa and lost. ";
            }
            else return "Mario encountered a Koopa and died. ";
        case 'b': // if its a boss
            win = fightBoss(); // fight a boss and store the result
            if (win == 1) {
                if (currentLevel == noOfPlayLevels - 1) gameWon = 1; // check if game is won
                defeatedEnemies++;
                return "Mario encoutered a boss and won. ";
            }
            else if (win == -1) {
                defeatedEnemies = 0; // reset defeated enemies count if lost but still alive
                marioNeedsToFightBossAgain = 1; // set to fight boss again
                return "Mario encountered a boss and lost. ";
            }
            else return "Mario encountered a boss and died. ";
        case 'x': // if its an empty space
            marioEmptySpace();
            return "Mario moved to an empty space. ";
        case 'w': // if its a warped pipe
            marioWarped();
            return "Mario will WARP. ";
        default: // if its something unknown
            return "Unknown object encountered. "; 
    }
}

void marioGamePlay::marioMove() {
    int direction = rand() % 4; // random number between 0-3
    // replace Mario's current position with 'x' to show that he has moved away
    if (world3D[currentLevel][marioPosRow][marioPosCol] == 'H') 
        world3D[currentLevel][marioPosRow][marioPosCol] = 'x';
    // move Mario based on the random direction
    switch (direction) {
        case 0: // move left
            if (marioPosCol > 0) {
                marioPosCol--;
            }
            else marioPosCol = noOfPlayDimensionOfGrid - 1; // wrap around if at edge
            break;
        case 1: // move right
            if (marioPosCol < noOfPlayDimensionOfGrid - 1) {
                marioPosCol++;
            }
            else marioPosCol = 0;
            break;
        case 2: // move up
            if (marioPosRow > 0) {
                marioPosRow--;
            }
            else marioPosRow = noOfPlayDimensionOfGrid - 1; // wrap around if at edge
            break;
        case 3: // move down
            if (marioPosRow < noOfPlayDimensionOfGrid - 1) {
                marioPosRow++;
            }
            else marioPosRow = 0;
            break;
    }
}

// definitions for collectCoin, eatMushroom, fightGoomba, fightKoopa, and fightBoss
// they adjust Mario's state (coins, life, power level) based on the interaction and update the world3D array
void marioGamePlay::collectCoin() {
    marioCoins++; // add 1 to marioCoins
    world3D[currentLevel][marioPosRow][marioPosCol] = 'x'; // added
    if (marioCoins == 20) {
        marioLife++; // add 1 to marioLife
        marioCoins = 0; // reset marioCoins to 0
    }
    world3D[currentLevel][marioPosRow][marioPosCol] = 'H';
}

void marioGamePlay::marioEmptySpace() {
    world3D[currentLevel][marioPosRow][marioPosCol] = 'H'; //put Mario in empty space
}
void marioGamePlay::eatMushroom() {
    if (marioPL < 2) {
        world3D[currentLevel][marioPosRow][marioPosCol] = 'H'; // added
        marioPL++; // add 1 to marioPL but do not exceed 2
    }
    world3D[currentLevel][marioPosRow][marioPosCol] = 'H';
}

int marioGamePlay::fightGoomba() {
    int chance = rand() % 100;
    if (chance < 80) { // Mario wins
        world3D[currentLevel][marioPosRow][marioPosCol] = 'H';
        return 1;
    } else { // Handle loss
        if (marioPL > 0) marioPL--;
        else marioLife--;
        return (marioLife > 0) ? -1 : 0;
    }
}

int marioGamePlay::fightKoopa() {
    // 65% probability to defeat koopa
    if (rand() % 100 < 65) {
        world3D[currentLevel][marioPosRow][marioPosCol] = 'H';
        return 1; // Mario won
    } else {
        if (marioPL > 0) {
            marioPL--; // decrease power level by 1
        } else {
            marioLife--; // lose a life if at PL0
            if (marioLife > 0) {
                marioPL = 0; // reset power level to 0
                return -1; // mario lost but has more lives
            } else {
                return 0; // mario lost and no lives left
            }
        }
    }
    return -1; // Mario lost but did not die
}

int marioGamePlay::fightBoss() {
    // fighting the boss
    // 50% probability to defeat the level boss
    if (rand() % 100 < 50) {
        world3D[currentLevel][marioPosRow][marioPosCol] = 'H';
        return 1; // Mario won
    } else {
        if (marioPL > 1) {
            marioPL -= 2; // decrease power level by 2
        } else {
            marioLife--; // lose a life if at PL0 or PL1
            if (marioLife > 0) {
                marioPL = 0; // reset power level to 0
                return -1; // mario lost but has more lives
            } else {
                return 0; // mario lost and died (no lives left)
            }
        }
    }
    return -1; // mario lost but did not die
}

void marioGamePlay::marioWarped() {
    currentLevel++;
}
