#include <fstream>
#include <vector>
#include <string>

namespace FileUtils
{
    template <typename R>
    std::vector<R> fileReader(const std::string filePath, R parserFunction(std::string&))
    {
        std::ifstream inFileStream(filePath);
        std::string line;
        std::vector<R> inputList;

        while (std::getline(inFileStream, line))
        {
            inputList.push_back(parserFunction(line));
        }

        return std::move(inputList);
    }
} // namespace FileUtils