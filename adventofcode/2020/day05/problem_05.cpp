#include "../utils/file_utils.h"
#include <algorithm>
#include <iostream>
#include "bits/stdc++.h"

namespace Problem051
{
    const char* fileName = "input.txt";

    class Seat
    {
        private:
            int rowId, colId, seatId;
        public:
            Seat(int rowId, int colId): rowId(rowId), colId(colId), seatId(rowId * 8 + colId)
            {}

            int operator<(const Seat& other) const
            {
                return this->seatId < other.seatId;
            }

            int getSeatId() const
            {
                return this->seatId;
            }
    };

    Seat parserFunction(std::string &line)
    {
        int rowId = 0, colId = 0;
        for(int index = 0, powVal = (1 << 6); index < 7; ++index, powVal >>= 1)
        {
            rowId += (line[index] == 'F' ? 0 : 1) * powVal;
        }

        for(int index = 7, powVal = (1 << 2); index < 10; ++index, powVal >>= 1)
        {
            colId += (line[index] == 'L' ? 0 : 1) * powVal;
        }

        Seat seatObj = Seat(rowId, colId);
        return seatObj;
    }

    void solve()
    {
        std::vector<Seat> inputList = FileUtils::fileReader(fileName, parserFunction);
        auto largestPtr = std::max_element(inputList.begin(), inputList.end());
        std::cout << largestPtr->getSeatId() << std::endl;
    }
}

namespace Problem052
{

    void solve()
    {
        std::vector<Problem051::Seat> inputList = FileUtils::fileReader(Problem051::fileName, Problem051::parserFunction);
        std::sort(inputList.begin(), inputList.end());
        for(int index = 0; index < inputList.size() - 1; ++index)
        {
            if(inputList[index + 1].getSeatId() - inputList[index].getSeatId() == 2)
            {
                std::cout << (inputList[index].getSeatId() + 1) << std::endl;
                break;
            }
        }
    }
}

int main()
{
    Problem051::solve();
    Problem052::solve();

    return 0;
}