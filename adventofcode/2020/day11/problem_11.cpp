#include <iostream>
#include "../utils/file_utils.h"

namespace Problem11Common
{
    const char* fileName = "input.txt";

    void print(std::vector<std::string> &inputList)
    {
        for(int rowIdx = 0; rowIdx < inputList.size(); ++rowIdx)
        {
            for(int colIdx = 0; colIdx < inputList[rowIdx].size(); ++colIdx)
            {
                std::cout << inputList[rowIdx][colIdx];
            }
            std::cout << std::endl;
        }
    }

    /*
     * T must be of type int adjacentCount(const std::vector<std::string> &copyVector, const int rowIdx, const int colIdx)
     */
    template<typename T>
    void loopTillNoChangeInState(T adjacentCount, std::vector<std::string> &inputList, const int vacateThreshold)
    {
        bool isSeatingChanged = false;
        do
        {
            isSeatingChanged = false;
            const std::vector<std::string> copyVector = inputList;
            for(int rowIdx = 0; rowIdx < inputList.size(); ++rowIdx)
            {
                for(int colIdx = 0; colIdx < inputList[rowIdx].size(); ++colIdx)
                {
                    char c = copyVector[rowIdx][colIdx];
                    int count = adjacentCount(copyVector, rowIdx, colIdx);
                    if (c == 'L' && count == 0)
                    {
                        inputList[rowIdx][colIdx] = '#';
                        isSeatingChanged = true;
                    }
                    else if(c == '#' && count >= vacateThreshold)
                    {
                        inputList[rowIdx][colIdx] = 'L';
                        isSeatingChanged = true;
                    }
                }
            }
            // print(inputList);
            // std::cout << "\n\n";
        }while(isSeatingChanged);
    }

    int countSeatedLocation(const std::vector<std::string> &inputList)
    {
        int count = 0;
        for(int rowIdx = 0; rowIdx < inputList.size(); ++rowIdx)
        {
            for(int colIdx = 0; colIdx < inputList[rowIdx].size(); ++colIdx)
            {
                count += (inputList[rowIdx][colIdx] == '#');
            }
        }
        return count;
    }

    template<typename T>
    void findOccupiedSeats(T adjacentCount, const int vacateThreshold)
    {
        std::vector<std::string> inputList = FileUtils::fileReader<std::string>(fileName, [](std::string &line){return line;});

        loopTillNoChangeInState(adjacentCount, inputList, vacateThreshold);
        std::cout << countSeatedLocation(inputList) << std::endl;
    }
}

namespace Problem110
{
    int checkRow(const std::string &row, const int colVal, bool is_same_row = false)
    {
        return (colVal > 0 && (row[colVal - 1] == '#')) +
               (colVal < (row.size() - 1) && row[colVal + 1] == '#') +
               ((!is_same_row) * row[colVal] == '#');
    }

    int adjacentCount(const std::vector<std::string> &copyVector, const int rowIdx, const int colIdx)
    {
        int count = 0;
        if(rowIdx > 0)
        {
            count += checkRow(copyVector[rowIdx - 1], colIdx);
        }
        if(rowIdx < copyVector.size() - 1)
        {
            count += checkRow(copyVector[rowIdx + 1], colIdx);
        }
        count += checkRow(copyVector[rowIdx], colIdx, true);

        return count;
    }

    void solve()
    {
        Problem11Common::findOccupiedSeats(adjacentCount, 4);
    }
}

namespace Problem111
{
    template <typename T>
    int moveInsideRow(const std::vector<std::string> &copyVector, const int rowStartVal, const int colStartVal, int direction, T endChecker)
    {
        int returnVal = 0;
        for(int colIndex = colStartVal + direction; endChecker(colIndex); colIndex += direction)
        {
            if(copyVector[rowStartVal][colIndex] != '.')
            {
                returnVal = (copyVector[rowStartVal][colIndex] == '#');
                break;
            }
        }
        return returnVal;
    }

    template <typename T>
    int moveInsideCol(const std::vector<std::string> &copyVector, const int rowStartVal, const int colStartVal, const int direction, T endChecker)
    {
        int returnVal = 0;
        for(int rowIndex = rowStartVal + direction; endChecker(rowIndex); rowIndex += direction)
        {
            if(copyVector[rowIndex][colStartVal] != '.')
            {
                returnVal = (copyVector[rowIndex][colStartVal] == '#');
                break;
            }
        }
        return returnVal;
    }

    template <typename T>
    int moveDiagonal(const std::vector<std::string> &copyVector, const int rowStartVal, const int colStartVal, const int direction, T endChecker)
    {
        int returnVal = 0;
        for(int rowIndex = rowStartVal + direction, colIndex = colStartVal + direction; endChecker(rowIndex, colIndex); rowIndex += direction, colIndex += direction)
        {
            if(copyVector[rowIndex][colIndex] != '.')
            {
                returnVal = (copyVector[rowIndex][colIndex] == '#');
                break;
            }
        }
        return returnVal;
    }

    template <typename T>
    int moveOtherDiagonal(const std::vector<std::string> &copyVector, const int rowStartVal, const int colStartVal, const int rowDirection, const int colDirection, T endChecker)
    {
        int returnVal = 0;
        for(int rowIndex = rowStartVal + rowDirection, colIndex = colStartVal + colDirection; endChecker(rowIndex, colIndex); rowIndex += rowDirection, colIndex += colDirection)
        {
            if(copyVector[rowIndex][colIndex] != '.')
            {
                returnVal = (copyVector[rowIndex][colIndex] == '#');
                break;
            }
        }
        return returnVal;
    }

    int adjacentCount(const std::vector<std::string> &copyVector, const int rowIdx, const int colIdx)
    {
        const int maxCol = copyVector[0].size(), maxRow = copyVector.size();
        int count = moveInsideRow(copyVector, rowIdx, colIdx, 1, [&maxCol](int val){return val < maxCol;});
        count += moveInsideRow(copyVector, rowIdx, colIdx, -1, [](int val){return val >= 0;});
        count += moveInsideCol(copyVector, rowIdx, colIdx, 1, [&maxRow](int val){return val < maxRow;});
        count += moveInsideCol(copyVector, rowIdx, colIdx, -1, [](int val){return val >= 0;});
        count += moveDiagonal(copyVector, rowIdx, colIdx, 1, [&maxCol, &maxRow](int rowVal, int colVal){return rowVal < maxRow && colVal < maxCol;});
        count += moveDiagonal(copyVector, rowIdx, colIdx, -1, [](int rowVal, int colVal){return rowVal >= 0 && colVal >= 0;});
        count += moveOtherDiagonal(copyVector, rowIdx, colIdx, 1, -1, [&maxRow](int rowVal, int colVal){return rowVal < maxRow && colVal >= 0;});
        count += moveOtherDiagonal(copyVector, rowIdx, colIdx, -1, 1, [&maxCol](int rowVal, int colVal){return rowVal >= 0 && colVal < maxCol;});
        return count;
    }

    void solve()
    {
        Problem11Common::findOccupiedSeats(adjacentCount, 5);
    }
}

int main()
{
    Problem110::solve();
    Problem111::solve();
    return 0;
}