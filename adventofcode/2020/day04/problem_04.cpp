#include "../utils/file_utils.h"
#include <iostream>
#include <regex>


namespace Problem041
{
    const char* fileName = "input.txt";

    std::string parserFunction(std::string &line)
    {
        return line;
    }

    bool isValidPassPort(std::string &passport)
    {
        size_t fieldCount = std::count(passport.begin(), passport.end(), ':');
        return fieldCount == 8 || (fieldCount == 7 && passport.find("cid") == std::string::npos);
    }

    int countValidPassPort(std::vector<std::string> &inputLines, bool isValidPassPortFun(std::string &passport) = isValidPassPort)
    {
        int count = 0;
        std::string passport;
        for (int index = 0; index <= inputLines.size(); ++index)
        {
            if(index == inputLines.size() || inputLines[index].size() == 0)
            {
                count += isValidPassPortFun(passport);
                passport = "";
            }
            else
            {
                passport.append(" ");
                passport.append(inputLines[index]);
            }
        }

        return count;
    }

    void solve()
    {
        std::vector<std::string> inputLines = FileUtils::fileReader(fileName, parserFunction);
        int count = countValidPassPort(inputLines);
        std::cout << count << std::endl;
    }
}

namespace Problem042
{
    bool isTemplateField(std::string &field, int templateFunc(int))
    {
        auto itr = field.begin(), end = field.end();
        for(;itr != end && templateFunc(*itr); ++itr);
        return itr == end;
    }
    bool isValidField(std::string &field, int minVal, int maxVal)
    {
        if(isTemplateField(field, std::isdigit))
        {
            int fieldVal = std::stoi(field);
            return (minVal <= fieldVal && fieldVal <= maxVal);
        }
        return false;
    }

    std::string parser(const std::string &passport, const std::string &fieldName, int fieldLength)
    {
        size_t index = passport.find(fieldName + ":");
        size_t startIndex = index + fieldName.size() + 1;
        std::string field = passport.substr(startIndex, fieldLength);
        return field;
    }

    bool parseAndValidateIntField(const std::string &passport, const std::string &fieldName, int fieldLength, int minVal, int maxVal)
    {
        std::string field = parser(passport, fieldName, fieldLength);
        return isValidField(field, minVal, maxVal);
    }

    bool parseAndValidateHexField(const std::string &passport, const std::string &fieldName, int fieldLength)
    {
        std::string field = parser(passport, fieldName, fieldLength);
        std::string hexField = field.substr(1);
        return field[0] == '#' && hexField.size() == 6 && isTemplateField(hexField, std::isxdigit);
    }

    std::vector<std::string> eyeTypes{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

    bool validateEye(const std::string &passport, const std::string &fieldName, int fieldLength)
    {
        std::string field = parser(passport, fieldName, fieldLength);
        return std::find(eyeTypes.begin(), eyeTypes.end(), field) != eyeTypes.end();
    }

    bool validatePassPortId(std::string &passport)
    {
        size_t index = passport.find("pid:") + 4;
        size_t end_index = passport.find(" ", index);
        std::string field = passport.substr(index, end_index - index);
        return (isTemplateField(field, std::isdigit) && field.size() == 9);
    }

    bool isValidPassPort(std::string &passport)
    {
        if(Problem041::isValidPassPort(passport))
        {
            int count = parseAndValidateIntField(passport, "byr", 4, 1920, 2002);
            count += parseAndValidateIntField(passport, "iyr", 4, 2010, 2020);
            count += parseAndValidateIntField(passport, "eyr", 4, 2020, 2030);
            if(passport.find("cm") != std::string::npos)
            {
                count += parseAndValidateIntField(passport, "hgt", 3, 150, 193);
            }
            else
            {
                count += parseAndValidateIntField(passport, "hgt", 2, 59, 76);
            }
            count += parseAndValidateHexField(passport, "hcl", 7);
            count += validateEye(passport, "ecl", 3);
            count += validatePassPortId(passport);
            return count == 7;
        }

        return false;
    }

    void solve()
    {
        std::vector<std::string> inputLines = FileUtils::fileReader(Problem041::fileName, Problem041::parserFunction);
        int count = Problem041::countValidPassPort(inputLines, isValidPassPort);
        std::cout << count << std::endl;
    }
}

int main()
{
    Problem041::solve();
    Problem042::solve();

    return 0;
}