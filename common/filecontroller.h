#ifndef __FILE_CONTROLLER_CPP__
#define __FILE_CONTROLLER_CPP__

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>
#include <iostream>

class FileController {
public:
    bool fileExists(const std::string& filePath);
    bool readFileContent(const std::string& filePath, std::string& content);
};

#endif // __FILE_CONTROLLER_CPP__
