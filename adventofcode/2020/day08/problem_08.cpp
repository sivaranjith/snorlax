#include <iostream>
#include <string>
#include "../utils/file_utils.h"

namespace Problem081
{
    const char* fileName = "input.txt";
    class Instruction
    {
        public:
            std::string operation;
            const int val;
            bool is_checked;

            Instruction(std::string operation, const int val): operation(operation), val(val), is_checked(false)
            {}
    };

    Instruction parseInput(std::string &line)
    {
        int val = std::stoi(line.substr(5, line.size() - 1)) * (line[4] == '+' ? 1 : -1);
        return Instruction{line.substr(0, 3), val};
    }

    int getAccValAtLoopStart(std::vector<Instruction> &instructionList)
    {
        int index = 0, accVal = 0;
        while(!instructionList[index].is_checked)
        {
            Instruction &instructionObj = instructionList[index];
            instructionObj.is_checked = true;
            if(instructionObj.operation == "acc")
            {
                accVal += instructionObj.val;
            }
            else if (instructionObj.operation == "jmp")
            {
                index += instructionObj.val;
                continue;
            }
            ++index;
        }

        return accVal;
    }

    void solve()
    {
        std::vector<Instruction> instructionList = FileUtils::fileReader<Instruction>(fileName, parseInput);
        std::cout << getAccValAtLoopStart(instructionList) << std::endl;
    }
}

namespace Problem082
{
    std::pair<int, int> getChangeableIndexies(std::vector<Problem081::Instruction> &instructionList, int startIndex=0, bool canChange=true, int acc=0)
    {
        std::vector<int> indexes;
        int index = startIndex;

        while(index < instructionList.size())
        {
            Problem081::Instruction &instructionObj = instructionList[index];

            if(instructionObj.is_checked)
            {
                for(int visitedIdx = indexes.size() - 1; visitedIdx >= 0; --visitedIdx)
                {
                    int visitedIndex = indexes[visitedIdx];
                    Problem081::Instruction &visitedInstructionObj = instructionList[visitedIndex];
                    visitedInstructionObj.is_checked = false;
                    if(visitedInstructionObj.operation == "acc")
                    {
                        acc -= visitedInstructionObj.val;
                    }
                    else if(canChange)
                    {
                        std::string actual_value = visitedInstructionObj.operation;
                        if(actual_value == "jmp")
                        {
                            visitedInstructionObj.operation = "nop";
                        }
                        else
                        {
                            visitedInstructionObj.operation = "jmp";
                        }

                        std::pair<int, int> returnVal = getChangeableIndexies(instructionList, visitedIndex, false, acc);
                        if(returnVal.first)
                        {
                            return returnVal;
                        }

                        visitedInstructionObj.operation = actual_value;
                    }
                }
                return {0, acc};
            }

            instructionObj.is_checked = true;
            indexes.push_back(index);
            if(instructionObj.operation == "acc")
            {
                acc += instructionObj.val;
            }
            else if (instructionObj.operation == "jmp")
            {
                index += instructionObj.val;
                continue;
            }
            ++index;
        }

        return {1, acc};
    }

    void solve()
    {
        std::vector<Problem081::Instruction> instructionList = FileUtils::fileReader<Problem081::Instruction>(Problem081::fileName, Problem081::parseInput);
        std::pair<int, int> changeableIndexies = getChangeableIndexies(instructionList);
        std::cout << changeableIndexies.second << std::endl;
    }
}

int main()
{
    Problem081::solve();
    Problem082::solve();

    return 0;
}