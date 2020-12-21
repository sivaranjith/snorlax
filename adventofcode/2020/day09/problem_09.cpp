#include <iostream>
#include "../utils/file_utils.h"
#include <set>

namespace Problem091
{
    const char* fileName = "input.txt";
    const int preambleLength = 25;
    long parseInput(std::string &line)
    {
        return std::stol(line);
    }

    std::pair<int, long> findFirstNonMatchingNumber(std::vector<long> &inputList, std::set<long> &inputBucket)
    {
        bool isMatched;
        for(int index = preambleLength; index < inputList.size(); ++index)
        {
            isMatched = false;
            for(const int val : inputBucket)
            {
                if(inputBucket.find(inputList[index] - val) != inputBucket.end())
                {
                    isMatched = true;
                }
            }

            if(!isMatched)
            {
                return {index, inputList[index]};
            }
            else
            {
                inputBucket.erase(inputList[index - preambleLength]);
                inputBucket.insert(inputList[index]);
            }

        }

        return {-1, -1};
    }

    void solve()
    {
        std::vector<long> inputList = FileUtils::fileReader(fileName, parseInput);
        std::set<long> inputBucket(inputList.begin(), inputList.begin() + preambleLength);
        std::cout << findFirstNonMatchingNumber(inputList, inputBucket).second << std::endl;
    }
}

namespace Problem092
{
    std::pair<int, int> findLongestSequence(std::vector<long> &inputList, std::pair<int, long> &result)
    {
        int start = 0, end = 1;
        long long int sum = inputList[start] + inputList[end];
        while(start < end && end < result.first)
        {
            if(sum < result.second)
            {
                ++end;
                sum += inputList[end];
            }
            else if(sum > result.second)
            {
                sum -= inputList[start];
                ++start;
            }
            else
            {
                break;
            }

        }

        return {start, end};
    }

    long getEncryptionWeakness(std::vector<long> &inputList, std::pair<int, int> &startAndEndPos)
    {
        long minVal = inputList[startAndEndPos.first], maxVal=0;
        for(int index = startAndEndPos.first; index <= startAndEndPos.second; ++index)
        {
            if(inputList[index] < minVal)
            {
                minVal = inputList[index];
            }
            if(inputList[index] > maxVal)
            {
                maxVal = inputList[index];
            }
        }

        return minVal + maxVal;
    }

    void solve()
    {
        std::vector<long> inputList = FileUtils::fileReader(Problem091::fileName, Problem091::parseInput);
        std::set<long> inputBucket(inputList.begin(), inputList.begin() + Problem091::preambleLength);
        std::pair<int, long> result = Problem091::findFirstNonMatchingNumber(inputList, inputBucket);

        std::pair<int, int> startAndEndPos = findLongestSequence(inputList, result);
        std::cout << getEncryptionWeakness(inputList, startAndEndPos) << std::endl;
    }
}

int main()
{
    Problem091::solve();
    Problem092::solve();

    return 0;
}