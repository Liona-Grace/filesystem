#include "filecontroller.h"

namespace fs = std::filesystem;

bool FileController::fileExists(const std::string& filePath)
{
    std::error_code ec;

    return fs::exists(filePath, ec)
        && fs::is_regular_file(filePath, ec);
}

bool FileController::readFileContent(const std::string& filePath, std::string& content)
{
    if (!fileExists(filePath))
    {
        std::cerr << "File does not exist or is not a regular file: "
                  << filePath << '\n';
        return false;
    }

    std::ifstream file(filePath, std::ios::in | std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Cannot open file for reading: "
                  << filePath << '\n';
        return false;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();

    if (file.bad())
    {
        std::cerr << "Error while reading file: "
                  << filePath << '\n';
        return false;
    }

    content = buffer.str();
    return true;
}
