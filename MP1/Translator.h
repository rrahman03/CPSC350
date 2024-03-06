#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>

class Translator {
    public:
        Translator(); // default constructor
        ~Translator(); // default destructor

        std::string translateEnglishWord(std::string englishWord); // function to translate a single English word
        std::string translateEnglishSentence(std::string englishSentence);  // function to translate an English sentence 

};

#endif 