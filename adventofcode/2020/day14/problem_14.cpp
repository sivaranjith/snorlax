#include <iostream>
#include <map>
#include "../utils/file_utils.h"

namespace Problem141
{
    const char* fileName = "input.txt";
    const int MASK_LINE = 0, MEM_LINE = 1;

    std::pair<int, std::pair<long, long>> parseInput(std::string &line)
    {
        std::pair<int, std::pair<long, long>> returnVal;
        if(line.find("mask") != std::string::npos)
        {
            std::string val = line.substr(line.find(" = ") + 3);
            long andVal = (1L << 36) - 1, orVal = 0;
            int valLen = val.length();
            for(int index = 0; index <= valLen; ++index)
            {
                if(val[index] == '0')
                {
                    andVal = andVal - (1L << (valLen - index - 1));
                }
                else if(val[index] == '1')
                {
                    orVal = orVal + (1L << (valLen - index - 1));
                }
            }
            returnVal.first = MASK_LINE;
            returnVal.second.first = andVal;
            returnVal.second.second = orVal;
        }
        else
        {
            returnVal.first = MEM_LINE;
            int startPos = line.find('[') + 1;
            // std::cout << line.substr(startPos, line.find(']') - startPos) << std::endl;
            returnVal.second.first = std::stol(line.substr(startPos, line.find(']') - startPos));
            // std::cout << line.substr(line.find(" = ") + 3) << std::endl;
            returnVal.second.second = std::stol(line.substr(line.find(" = ") + 3));
        }

        // std::cout << returnVal.first << "::" << returnVal.second.first << "::" << returnVal.second.second << std::endl;
        return returnVal;
    }

    long computeSumOfMem(std::vector<std::pair<int, std::pair<long, long>>> &inputLines)
    {
        std::map<long, long> memory;
        long andVal = 0, orVal = 0, result = 0;
        for (std::pair<int, std::pair<long, long>> &inputLine : inputLines)
        {
            if(inputLine.first == MASK_LINE)
            {
                andVal = inputLine.second.first;
                orVal = inputLine.second.second;
            }
            else
            {
                // std::cout << inputLine.second.first << "::" << inputLine.second.second << "::" << andVal << "::" << orVal << "::" << ((inputLine.second.second & andVal) | orVal) << std::endl;
                memory[inputLine.second.first] = ((inputLine.second.second & andVal) | orVal);
            }
        }

        for(auto itr = memory.begin(); itr != memory.end(); ++itr)
        {
            // std::cout << itr->first << "::" << itr->second << std::endl;
            result += itr->second;
        }
        return result;
    }

    void solve()
    {
        std::vector<std::pair<int, std::pair<long, long>>> inputLines = FileUtils::fileReader<std::pair<int, std::pair<long, long>>>(fileName, parseInput);
        std::cout << computeSumOfMem(inputLines) << std::endl;
    }
}

namespace Problem142
{
    const char* fileName = "sample2.txt";

    std::pair<std::string, std::string> parseFunction(std::string& line)
    {
        std::pair<std::string, std::string> returnVal;
        if(line.find("mask") != std::string::npos)
        {
            returnVal.first = line.substr(line.find(" = ") + 3);
            returnVal.second = "";
        }
        else
        {
            int startPos = line.find('[') + 1;
            returnVal.first = line.substr(startPos, line.find(']') - startPos);
            returnVal.second = line.substr(line.find(" = ") + 3);
        }

        return returnVal;
    }

    long computeSumMemory(std::vector<std::pair<std::string, std::string>>& parsedLines)
    {
        std::map<long, long> memory;
        long result = 0;
        std::string mask;

        for(std::pair<std::string, std::string> &inputKeyVal : parsedLines)
        {
            if(inputKeyVal.second == "")
            {
                mask = inputKeyVal.first;
            }
            else
            {
                std::vector<int> floatLocations;
                std::string maskCpy = mask;
                for(int idx = 0; idx < maskCpy.length(); ++idx)
                {
                    if(maskCpy[idx] == 'X')
                    {
                        floatLocations.push_back(35 - idx);
                        maskCpy[idx] = '0';
                    }
                }

                long maskVal = std::stoull(maskCpy, 0, 2);
                std::vector<long> cache;
                long address = std::stol(inputKeyVal.first);
                long val = std::stol(inputKeyVal.second);

                for(int &idx : floatLocations)
                {
                    address &= ~(1L << idx);
                }

                memory[address | maskVal] = val;
                cache.push_back(address | maskVal);

                for(int &idx : floatLocations)
                {
                    int cacheSize = cache.size();
                    for(int itr = 0; itr < cacheSize; ++itr)
                    {
                        long addressVal = cache[itr];
                        addressVal |= (1L << idx);

                        memory[addressVal] = val;
                        cache.push_back(addressVal);
                    }
                }
            }

        }

        for(auto itr = memory.begin(); itr != memory.end(); ++itr)
        {
            result += itr->second;
        }

        return result;
    }

    void solve()
    {
        std::vector<std::pair<std::string, std::string>> parsedLines = FileUtils::fileReader<std::pair<std::string, std::string>>(Problem141::fileName, parseFunction);
        std::cout << computeSumMemory(parsedLines) << std::endl;
    }
}

int main()
{
    Problem141::solve();
    Problem142::solve();

    return 0;
}