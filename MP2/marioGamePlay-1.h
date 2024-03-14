#ifndef MARIOGAMEPLAY_H
#define MARIOGAMEPLAY_H
#include "marioWorld.h"
#include <string>

class marioGamePlay {

public:
    char*** world3D; // 3D array representing the game world
    int noOfPlayLevels; // number of levels in the game
    int noOfPlayDimensionOfGrid; // dimension of the grid (world) in each level
    int currentLevel; // current level the player is on 
    int marioPosRow; // Mario's current position, row
    int marioPosCol; // Mario's current position, column
    int marioPL; // Mario's power level
    int marioCoins; // number of coins Mario has collected
    int marioLife; // Mario's remaining lives
    int gameWon = 0; // indicates whether or not the game has been won or lost
    int defeatedEnemies = 0; // number of enemies Mario has defeated
    int marioNeedsToFightBossAgain = 0; // indicates whether Mario needs to fight the bos again or not
    
    // constructor
    marioGamePlay(marioWorld *world3D, int marioLife);
    // destructor
    ~marioGamePlay();

    void playGame(); // method to play the game
    void marioMove(); // method to handle Mario's movement
    std::string marioInteraction(); // method to handle Mario's interaction with the game world

    void collectCoin(); // method to collect a coin
    void eatMushroom(); // method to collect a mushroom
    int fightBoss(); // method to fight a boss
    int fightGoomba(); // method to fight a goomba
    int fightKoopa(); // method to fight a koopa
    void marioWarped(); // method to handle Mario being warped
    void marioEmptySpace(); // method to handle Mario moving into an empty space

};

#endif // MARIOGAMEPLAY_H
