#include <iostream>
#include <string>
#include <sstream>
#include "../utils/file_utils.h"

namespace Problem131
{
    const char* fileName = "input.txt";

    int getResult(std::vector<std::string> &inputLines)
    {
        int startTime = std::stoi(inputLines[0]), minVal = -1, tempVal, busId, tempBusId;
        std::string tempInput;
        std::stringstream ss(inputLines[1]);

        while(getline(ss, tempInput, ','))
        {
            if (tempInput == "x")
            {
                continue;
            }
            tempBusId = std::stoi(tempInput);
            tempVal = tempBusId - (startTime % tempBusId);
            if(minVal > tempVal || minVal == -1)
            {
                minVal = tempVal;
                busId = tempBusId;
            }
        }

        return minVal * busId;
    }

    void solve()
    {
        std::vector<std::string> inputLines = FileUtils::fileReader<std::string>(fileName, [](std::string &line){return line;});
        std::cout << getResult(inputLines) << std::endl;
    }
}

namespace Problem132
{
    long long calculateChineseReminderTheorem(std::string &line)
    {
        long long product = 1, chineseReminder = 0;
        std::vector<std::pair<long, long>> inputData;
        long count = 0, tempBusId;

        std::string tempInput;
        std::stringstream ss(line);

        while(getline(ss, tempInput, ','))
        {
            ++count;
            if (tempInput == "x")
            {
                continue;
            }
            tempBusId = std::stoi(tempInput);
            long modVal = (tempBusId - (count - 1)) % tempBusId;
            modVal = modVal < 0 ? tempBusId + modVal : modVal;
            inputData.push_back({tempBusId, modVal});
            product *= tempBusId;
        }

        for(std::pair<long, long> &parsedInput : inputData)
        {
            long remaining = product / parsedInput.first;
            count = 1;
            while((remaining * count) % parsedInput.first != parsedInput.second)
            {
                ++count;
            }

            chineseReminder += (remaining * count);
        }

        return chineseReminder % product;
    }

    void solve()
    {
        std::vector<std::string> inputLines = FileUtils::fileReader<std::string>(Problem131::fileName, [](std::string &line){return line;});
        std::cout << calculateChineseReminderTheorem(inputLines[1]) << std::endl;
    }
}

int main()
{
    Problem131::solve();
    Problem132::solve();

    return 0;
}