#ifndef FILEPROCESSORL_H
#define FILEPROCESSORL_H

#include <string>

class FileProcessor {
    public:
        FileProcessor(); // default constructor
        ~FileProcessor(); // default destructor

        void processFile(std::string inputFileName, std::string outputFileName); // member function declared to process file
};
#endif 