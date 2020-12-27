#include <iostream>
#include "../utils/file_utils.h"

namespace Problem121
{
    const char* fileName = "input.txt";

    std::pair<char, int> parseInput(std::string &line)
    {
        return {line[0], std::stoi(line.substr(1))};
    }

    int getManhattanDistance(std::vector<std::pair<char, int>> &inputPairs)
    {
        int x = 0, y = 0, direction = 0, turn;
        for(std::pair<char, int> &instruction : inputPairs)
        {
            switch (instruction.first)
            {
            case 'F':
                if(direction == 0)
                {
                    x += instruction.second;
                }
                else if(direction == 1)
                {
                    y += instruction.second;
                }
                else if(direction == 2)
                {
                    x -= instruction.second;
                }
                else if(direction == 3)
                {
                    y -= instruction.second;
                }
                break;

            case 'L': turn = (instruction.second / 90) % 4;
                direction = (direction + turn) % 4;
                break;

            case 'R': turn = 4 - ((instruction.second / 90) % 4);
                direction = (direction + turn) % 4;
                break;

            case 'N': y += instruction.second;
                break;

            case 'S': y -= instruction.second;
                break;

            case 'E': x += instruction.second;
                break;

            case 'W': x -= instruction.second;
                break;
            }
        }

        return std::abs(x) + std::abs(y);
    }

    void solve()
    {
        std::vector<std::pair<char, int>> inputPairs = FileUtils::fileReader<std::pair<char, int>>(fileName, parseInput);
        std::cout << getManhattanDistance(inputPairs) << std::endl;
    }
}

namespace Problem122
{
    int getManhattanDistance(std::vector<std::pair<char, int>> &instructions)
    {
        int sx = 0, sy = 0, wx = 10, wy = 1, turn, swapVar;
        for(std::pair<char, int> &instruction : instructions)
        {
            switch (instruction.first)
            {
            case 'F':
                sx += wx * instruction.second;
                sy += wy * instruction.second;
                break;

            case 'L': turn = (instruction.second / 90) % 4;
            case 'R':
                if(instruction.first == 'R')
                {
                    turn = (4 - ((instruction.second / 90) % 4)) % 4;
                }
                switch (turn)
                {
                case 3:
                    swapVar = wy;
                    wy = -wx;
                    wx = swapVar;
                    break;
                case 2:
                    wx *= -1;
                    wy *= -1;
                    break;
                case 1:
                    swapVar = -wy;
                    wy = wx;
                    wx = swapVar;
                    break;
                }
                break;

            case 'N': wy += instruction.second;
                break;

            case 'S': wy -= instruction.second;
                break;

            case 'E': wx += instruction.second;
                break;

            case 'W': wx -= instruction.second;
                break;
            }
        }

        return std::abs(sx) + std::abs(sy);
    }

    void solve()
    {
        std::vector<std::pair<char, int>> inputPairs = FileUtils::fileReader<std::pair<char, int>>(Problem121::fileName, Problem121::parseInput);
        std::cout << getManhattanDistance(inputPairs) << std::endl;
    }
}

int main()
{
    Problem121::solve();
    Problem122::solve();

    return 0;
}