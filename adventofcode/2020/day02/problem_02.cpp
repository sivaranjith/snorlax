#include "../utils/file_utils.h"
#include <iostream>
#include <regex>

namespace Problem021
{
    const char* fileName = "input.txt";

    class Password
    {
        public:
            char letter;
            int startCount, endCount;
            std::string password;
    };

    Password parserFunction(std::string &line)
    {
        Password passwd;

        std::regex regex{"(\\d+)\\-(\\d+)\\s([a-z])\\:\\s([a-z]+)"};
        std::smatch matches;

        if(std::regex_search(line, matches, regex))
        {
            passwd.startCount = std::stoi(matches[1]);
            passwd.endCount = std::stoi(matches[2]);
            passwd.letter = matches[3].str()[0];
            passwd.password = matches[4];
        }

        return passwd;
    }

    int countOccurance(const std::string password, const char letter)
    {
        int count = 0;
        for(const char &passwordLetter : password)
        {
            if (letter == passwordLetter)
            {
                ++count;
            }
        }

        return count;
    }

    void validatePassword(const std::vector<Password> &inputLines)
    {
        int count = 0;
        for(const Password &passwd : inputLines)
        {
            int occurance = countOccurance(passwd.password, passwd.letter);
            if(passwd.startCount <= occurance && occurance <= passwd.endCount)
            {
                ++count;
            }
        }

        std::cout << count << std::endl;
    }

    void solve()
    {
        std::vector<Password> inputLines = FileUtils::fileReader(fileName, parserFunction);
        validatePassword(inputLines);
    }
}

namespace Problem022
{
    void testPassword(const std::vector<Problem021::Password> &inputLines)
    {
        int count = 0;
        for(const Problem021::Password &passwd : inputLines)
        {
            const int totalCount = (passwd.password[passwd.startCount - 1] == passwd.letter) + (passwd.password[passwd.endCount - 1] == passwd.letter);
            if(totalCount == 1)
            {
                ++count;
            }
        }

        std::cout << count << std::endl;
    }

    void solve()
    {
        std::vector<Problem021::Password> inputLines = FileUtils::fileReader(Problem021::fileName, Problem021::parserFunction);
        testPassword(inputLines);
    }
}

int main()
{
    Problem021::solve();
    Problem022::solve();

    return 0;
}