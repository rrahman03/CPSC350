#include "Translator.h"
#include "Model.h"
#include <string>
#include <sstream>

Translator::Translator() {} // default constructor
Translator::~Translator() {} // default destructor 

// translates an English word to Robber Language
std::string Translator::translateEnglishWord(std::string englishWord){
    char readCharacter; // stores each character of the English word
    Model cModel; // instance of the model class
    std::string returnString; // stores the translated word
    int stringLength; // stores the length of the English word
    
    stringLength = englishWord.length(); // gets the length of the English word
    for (int i = 0; i < stringLength; i++) {

        readCharacter = englishWord[i];  // gets each character of the English word
        // checks punctuation
        if (readCharacter == '.' || readCharacter == '!' || readCharacter == ','|| readCharacter == ':'|| readCharacter == ';' || readCharacter == '?' || readCharacter == '"'|| readCharacter == '\'') {
            returnString += readCharacter; // appends the punctuation mark
        }
        else {
            // appends the translated Robber Language character
            returnString.append(cModel.translateSingleConsonant(readCharacter));
            returnString.append(cModel.translateSingleVowel(readCharacter));
        }
    
        
    }
    return(returnString); // returns the translated word

}

// translates an English sentence into Robber Language
std::string Translator::translateEnglishSentence(std::string englishSentence){
    std::string convertWord; // stores each word of the English sentence
    std::string returnString=""; // stores the translation of the sentence
    std::istringstream iss(englishSentence);
    // breaks down the sentence word by word
    while (iss >> convertWord) {
        returnString.append(translateEnglishWord(convertWord)); 
        
    }
    return(returnString); // returns the Robber Language translation of the sentence
    
}