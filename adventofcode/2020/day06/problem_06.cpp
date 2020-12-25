#include "../utils/file_utils.h"
#include <iostream>
#include <numeric>

namespace Problem061
{
    const char* fileName = "input.txt";

    std::string parserFunction(std::string &line)
    {
        return line;
    }

    class Form
    {
        public:
            int bitMap, yesCount;
    };

    std::vector<Form> parseInput(std::vector<std::string> inputLines)
    {
        std::vector<Form> returnVal;
        int bitMap = 0, yesCount = 0;

        for(int index = 0; index <= inputLines.size(); ++index)
        {
            if(index == inputLines.size() || inputLines[index].size() == 0)
            {
                Form formObj;
                formObj.bitMap = bitMap;
                formObj.yesCount = yesCount;
                returnVal.push_back(formObj);
                bitMap = 0;
                yesCount = 0;
            }
            else
            {
                std::string line = inputLines[index];
                for(auto startItr = line.begin(); startItr != line.end(); ++startItr)
                {
                    if(((bitMap >> (*startItr - 'a')) & 1) == 0)
                    {
                        bitMap |= 1 << (*startItr - 'a');
                        ++yesCount;
                    }
                }
            }
        }

        return returnVal;
    }

    int summer(int lhs, const Form &formObj)
    {
        return lhs + formObj.yesCount;
    }

    void solve()
    {
        std::vector<std::string> inputLines = FileUtils::fileReader<std::string>(fileName, parserFunction);
        std::vector<Form> parsedInputLines = parseInput(inputLines);
        int totalCount = std::accumulate(parsedInputLines.begin(), parsedInputLines.end(), 0, summer);
        std::cout << totalCount << std::endl;
    }
}

namespace Problem062
{
    int countSetBit(int bitMap)
    {
        int count = 0;
        for(int index = 0; index < 26; ++index)
        {
            count += ((bitMap >> index) & 1);
        }

        return count;
    }

    std::vector<Problem061::Form> parseInput(std::vector<std::string> inputLines)
    {
        std::vector<Problem061::Form> returnVal;
        int bitMap = (1<<26) - 1;

        for(int index = 0; index <= inputLines.size(); ++index)
        {
            if(index == inputLines.size() || inputLines[index].size() == 0)
            {
                Problem061::Form formObj;
                formObj.bitMap = bitMap;
                formObj.yesCount = countSetBit(bitMap);
                returnVal.push_back(formObj);
                bitMap = (1<<26) - 1;
            }
            else
            {
                int newBitMap = 0;
                std::string line = inputLines[index];
                for(auto startItr = line.begin(); startItr != line.end(); ++startItr)
                {
                    if(((newBitMap >> (*startItr - 'a')) & 1) == 0)
                    {
                        newBitMap |= 1 << (*startItr - 'a');
                    }
                }
                bitMap &= newBitMap;
            }
        }

        return returnVal;
    }

    void solve()
    {
        std::vector<std::string> inputLines = FileUtils::fileReader<std::string>(Problem061::fileName, Problem061::parserFunction);
        std::vector<Problem061::Form> parsedInputLines = parseInput(inputLines);
        int totalCount = std::accumulate(parsedInputLines.begin(), parsedInputLines.end(), 0, Problem061::summer);
        std::cout << totalCount << std::endl;
    }
}

int main()
{
    Problem061::solve();
    Problem062::solve();

    return 0;
}