#include "FileProcessor.h"
#include "Translator.h"
#include <fstream>
#include <iostream>

FileProcessor::FileProcessor() {} // default constructor
FileProcessor::~FileProcessor() {} // default destructor 

void FileProcessor::processFile(std::string inputFileName, std::string outputFileName){
    // opens input and output files
    std::ifstream inFile(inputFileName); // open input file for reading
    std::ofstream outFile(outputFileName); // open output file for reading
    std::string word; // storing a word
    std::string inputSentence; // storing input sentence
    std::string translatedSentence; // storing translated sentenced
    Translator sentenceTranslation; // instance of translator class
    char readChar; // storing read characters from a file

    // checking if files are open
    if (!inFile.is_open() || !outFile.is_open()) {
        std::cout << "Error opening file" << std::endl; // output error message
        return; // exiting function
    }
    
    // writing HTML file header
    outFile << "<!DOCTYPE html>\n"; // HTML declaration
    outFile << "<html>\n"; 
    outFile << "<head>\n";
    outFile << "<title>Robber Language Translation</title>\n";
    outFile << "</head>\n";
    outFile << "<body>\n";

    outFile << "<b>\n"; 

    // read characters from input file 
    while (inFile.get(readChar)) {
        outFile << readChar; // writes character to output file
    }
    outFile << "\n</b>\n"; 
    outFile << "<p></p>\n"; 
    inFile.close(); // closes input file
    inFile.open(inputFileName); // reopens input file

    // reopens the input file and starts from the beginning
    if (!inFile.is_open()){
        std::cout << "\rError opening file\r" << std::endl; // output error message
        return; // exits function
    }

    // starts writing italicized sentences
    inputSentence.clear(); // clear input sentences
    outFile << "<i>\n"; // italic

    // read from input file and looks through sentences
    while (inFile.get(readChar)) { // clears input sentence
        inputSentence += readChar;
        // when the sentence ends, it tranlates and is written to output file
        if (readChar == '.' || readChar == '!' || readChar == '?') {
            translatedSentence = sentenceTranslation.translateEnglishSentence(inputSentence); // translate input
            outFile << translatedSentence << std::endl; // writes translation to output file
            outFile << "<br>\n"; // break
            inputSentence.clear(); // clear input sentence for next 
        }
    }

    outFile << "</i>\n";
    outFile << "</body>\n";
    outFile << "</html>\n";
    inFile.close(); // close input file
    outFile.close(); // close output file

}