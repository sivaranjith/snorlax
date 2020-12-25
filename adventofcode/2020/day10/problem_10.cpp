#include <iostream>
#include "../utils/file_utils.h"
#include <algorithm>
#include <map>

namespace Problem101
{
    const char* fileName = "input.txt";

    int parseInput(std::string &line)
    {
        return std::stoi(line);
    }

    std::map<int, int> getDiffCount(const std::vector<int> &inputList)
    {
        std::map<int, int> diffCounter;
        for(int index = 0; index < inputList.size() - 1; ++index)
        {
            int diff = inputList[index + 1] - inputList[index];
            if(diffCounter.find(diff) == diffCounter.end())
            {
                diffCounter[diff] = 0;
            }
            diffCounter[diff] += 1;
        }

        return diffCounter;
    }

    std::vector<int> getInputVals()
    {
        std::vector<int> inputList = FileUtils::fileReader<int>(fileName, parseInput);
        inputList.push_back(0);
        std::sort(inputList.begin(), inputList.end());
        inputList.push_back(inputList[inputList.size() - 1] + 3);
        return inputList;
    }

    void solve()
    {
        std::vector<int> inputList = getInputVals();
        std::map<int, int> diffCounter = getDiffCount(inputList);
        std::cout << diffCounter[1] << "*" << diffCounter[3] << "=" << diffCounter[1] * diffCounter[3] << std::endl;
    }
}

namespace Problem102
{
    int max = 0;
    long long _getCombinations(const int continousCount)
    {
        if(continousCount > max)
        {
            max = continousCount;
        }
        long long int result = 1 << continousCount;
        if(continousCount == 3)
        {
            --result;
        }
        else if(continousCount == 4)
        {
            result -= 4;
        }
        else if(continousCount == 5)
        {
            result -= 6;
        }
        // std::cout << continousCount << "::" << result << std::endl;
        return result;
    }

    long long getCombinations(std::vector<int> &inputList)
    {
        long long productVal = 1;
        int continousCount = 0;
        for(int index = 1; index < inputList.size() - 1; ++index)
        {
            if((inputList[index] - inputList[index - 1]) != 3 && (inputList[index + 1] - inputList[index]) != 3)
            {
                ++continousCount;
            }
            else
            {
                // std::cout << "calling::" << continousCount << "::" << inputList[index] << std::endl;
                productVal *= _getCombinations(continousCount);
                continousCount = 0;
            }

        }
        // std::cout << max << std::endl;
        return productVal;
    }

    void solve()
    {
        std::vector<int> inputList = Problem101::getInputVals();
        std::cout << "ans::" << getCombinations(inputList) << std::endl;
    }
}

int main()
{
    Problem101::solve();
    Problem102::solve();
    return 0;
}