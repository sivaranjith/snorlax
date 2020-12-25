#include <fstream>
#include <vector>
#include <string>
#include <functional>

namespace FileUtils
{
    /*
     * T must be of type std::function<R(std::string&)>
     */
    template <typename R, typename T>
    std::vector<R> fileReader(const std::string filePath, T parserFunction)
    {
        std::ifstream inFileStream(filePath);
        std::string line;
        std::vector<R> inputList;

        while (std::getline(inFileStream, line))
        {
            inputList.push_back(parserFunction(line));
        }

        return inputList;
    }
} // namespace FileUtils