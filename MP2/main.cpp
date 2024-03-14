#include <iostream>
#include <fstream>
#include "marioWorld.h"
#include "marioGamePlay.h"

int main() {
  // variables to store game settings
  int levelL, gridN, initialLivesV, coinPercent, nothingPercent, goombaPercent, koopaPercent, mushroomPercent;
 
  std::string outputFileName; // string variable to store output name
  std::string inputFileName; // declare a string variable to store input name

  // prompts user for unput file name and reads input
  std::cout << "\nGive me an input file name: "; 
  std::cin >> inputFileName;
  std::cout << "\ninput file name: " << inputFileName;
  std::ifstream inputFile(inputFileName); // open the input file
  std::cout << "\nGive me an output file name: "; 
  std::cin >> outputFileName; // prompt the user for an output file name and read it
  std::cout << "\noutput file name: " << outputFileName;

  // check if input file opening failed
  if (!inputFile) {
    std::cerr << "Error opening file." << std::endl;
    // return an error code if file opening fails
    return 1; 
  }

    std::ofstream outputFile(outputFileName); // open the output file name
    // check if the input file opening failed
    if (!outputFile) {
      std::cerr << "Error opening file." << std::endl;
      // return an error code if file opening fails
      return 1; 
    }

    
    int num;
    // read game settings from the file and process them 
    inputFile >> num; // read levelL from file
    levelL = num;
    inputFile >> num; // read gridN from file
    gridN = num;
    inputFile >> num; // read initialLives from file
    initialLivesV = num;
    inputFile >> num; // read coinPercent from file
    coinPercent = num;
    inputFile >> num; // read nothingPercent from file
    nothingPercent = num;
    inputFile >> num; // read goombaPercent from file
    goombaPercent = num;
    inputFile >> num; // read koopaPercent from file
    koopaPercent = num;
    inputFile >> num; // read mushroomPercent from file
    mushroomPercent = num;
    inputFile >> num;

    // close the file
    inputFile.close();

    if ((coinPercent+nothingPercent+goombaPercent+koopaPercent+mushroomPercent) != 100) {
      std::cerr << "\nTotal percentages of coins, empty space, goombas, koopas and mushrooms must equal 100, fix the input file and try again." << std::endl;
      // return an error code if file opening fails
      return 1; 
    }
   
    // new marioWorld object with level and grid setting
    marioWorld *gameWorld = new marioWorld(levelL, gridN); // Create a world with levelL levels, each gridNxgrindN
    
    // initialize the game world with random elements
    gameWorld->createMarioWorld();
    gameWorld->setupMarioWorld(coinPercent, nothingPercent, goombaPercent, koopaPercent, mushroomPercent); // setup the world with objects
    // create new marioGamePlay object
    marioGamePlay *gamePlay = new marioGamePlay(gameWorld, initialLivesV);

    // write initial Mario position to the output file
    outputFile << "Mario is starting in position: (" << gamePlay->marioPosRow << "," << gamePlay->marioPosCol << ")\n==========\n";
    // print the initial game world to the output file
    gameWorld->printWorld(outputFile, 0);
    
    // game loop
    do {
      // move Mario if not required to fight a boss again
      if (gamePlay->marioNeedsToFightBossAgain == 0 ) {
        gamePlay->marioMove(); 
      }
      
      gamePlay->marioNeedsToFightBossAgain = 0; // resent boss fight
      // Mario's current position, interaction result, power level, life, and coin count to the output file
      outputFile << "\nMario is at position: (" << gamePlay->marioPosRow << "," << gamePlay->marioPosCol << ") on level " << gamePlay->currentLevel << ".\n" << gamePlay->marioInteraction() << "Mario is at power level " << gamePlay->marioPL << ".\n";
    
      // outputFile << gamePlay->marioInteraction();
      outputFile << "Mario has " << gamePlay->marioLife << " life/lives left. Mario has " << gamePlay->marioCoins << " coin(s).\n";
      // print the updated game world to the output file
      gameWorld->printWorld(outputFile, gamePlay->currentLevel);
    
    // continue the game loop with while Mario is alive
    } while (gamePlay->marioLife && (gamePlay->gameWon == 0));

    // write the game outcome to the output file
    if (gamePlay->gameWon) {
      outputFile << "WE BEAT THE GAME! :)\n";
    }
    else outputFile << "WE LOST THE GAME! :(\n";

    // close the output file
    outputFile.close();
    

}

