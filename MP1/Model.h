#ifndef MODEL_H
#define MODEL_H

#include <string>

class Model {
    public:
        Model(); // default constructor
        ~Model(); // default destructor

        std::string translateSingleConsonant(char c); // translates a single consonant
        std::string translateSingleVowel(char c); // translates a single vowel

};

#endif 
