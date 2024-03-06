#include "Model.h"

Model::Model() {} // default constructor
Model::~Model() {} // default destructor 

// takes a single consonant character as input and returns a string representing its encoding in Rövarspråket
std::string Model::translateSingleConsonant(char c) {

   // checks if character is not a vowel
   if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U') {
      // return the charachter followed by 'o' and the character again
      return std::string(1, c) + "o" + c;
   }
   return std::string(""); // if it's a vowel, just return as empty string
}

// translates a single vowel charachter 
std::string Model::translateSingleVowel(char c) {
   // checks if character is a vowel
   if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
      // returns the character 
      return std::string(1, c); 
   }
   // if its not a vowel, return an empty string
   return std::string(""); 
}
