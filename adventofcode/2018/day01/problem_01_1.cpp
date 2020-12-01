#include <iostream>
#include <string>
#include <functional>
#include "../utils/file_utils.h"

using namespace std::placeholders;

class Problem011
{
private:
    long count;
public:
    Problem011(): count(0)
    {
    }

    Problem011(const Problem011 &probObj)
    {
        std::cout << "copy constructor\n";
    }

    const void lineParser(const std::string line)
    {
        this->count += std::stoi(line);
    }

    const void printSolution()
    {
        std::cout << "problem011: " << this->count << "\n";
    }
};

int main()
{
    Problem011 probObj;
    FileUtils::fileParser("input.txt", std::bind(&Problem011::lineParser, &probObj, _1), std::bind(&Problem011::printSolution, &probObj));
    return 0;
}