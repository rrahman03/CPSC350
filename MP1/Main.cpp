#include <iostream>
#include "Model.h" 
#include "Translator.h"
#include "FileProcessor.h"
#include "Model.cpp"
#include "Translator.cpp"
#include "FileProcessor.cpp"


int main() {
    FileProcessor myProcessor; // instance of FileProcessor class
    std::string outputFileName; // string variable to store output name
    std::string inputFileName; // declare a string variable to store input name
    // prompts user for unput file name and reads input
    std::cout << "\nGive me an input file name: "; 
    std::cin >> inputFileName;
    std::cout << "\ninput file name: " << inputFileName;
    // prompts user for output file name and reads input
    std::cout << "\nGive me an output file name: ";
    std::cin >> outputFileName;
    std::cout << "\noutput file name: " << outputFileName;
    std::cout << "\n";

    // process the input file and write the tranlated content to the output file
    myProcessor.processFile(inputFileName, outputFileName);

}
