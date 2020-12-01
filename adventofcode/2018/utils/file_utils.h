#include <fstream>

class FileUtils
{
public:
    static void fileParser(const std::string &fileName, const std::function<void(std::string)> &lineParser, const std::function<void()> &runner)
    {
        std::ifstream inputFile(fileName);
        if(inputFile.is_open())
        {
            std::string line;
            while(getline(inputFile, line))
            {
                lineParser(line);
            }

            inputFile.close();
        }

        runner();
    }
};