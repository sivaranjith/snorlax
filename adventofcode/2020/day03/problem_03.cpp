#include "../utils/file_utils.h"
#include<iostream>
#include <string>

namespace Problem031
{
    const char* fileName = "input.txt";

    std::string parserFunction(std::string &line)
    {
        return line;
    }

    int countTree(const std::vector<std::string> &inputLines, const int rowInc, const int colInc)
    {
        int count = 0, colLength = inputLines[0].size();
        for (int rowIndex = 0, colIndex = 0; rowIndex < inputLines.size(); rowIndex += rowInc, colIndex = (colIndex + colInc) % colLength)
        {
            if(inputLines[rowIndex][colIndex] == '#')
            {
                ++count;
            }
        }

        return count;
    }

    void solve()
    {
        std::vector<std::string> inputLines = FileUtils::fileReader<std::string>(fileName, parserFunction);
        int count = countTree(inputLines, 1, 3);
        std::cout << "count:: " << count << std::endl;
    }
}

namespace Problem032
{
    long compute(std::vector<std::string> inputLines)
    {
        long product = 1;
        int incVals[5][2] = {{1, 1}, {1, 3}, {1, 5}, {1, 7}, {2, 1}};
        for (auto &incVal : incVals)
        {
            product *= Problem031::countTree(inputLines, incVal[0], incVal[1]);
        }
        return product;
    }

    void solve()
    {
        std::vector<std::string> inputLines = FileUtils::fileReader<std::string>(Problem031::fileName, Problem031::parserFunction);
        long product = compute(inputLines);
        std::cout << "product:: " << product << std::endl;
    }
}

int main()
{
    Problem031::solve();
    Problem032::solve();

    return 0;
}