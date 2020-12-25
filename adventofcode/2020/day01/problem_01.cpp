#include "../utils/file_utils.h"
#include "iostream"
#include "bits/stdc++.h"

namespace Problem011
{
    const int FINAL_VAL = 2020;
    const std::string fileName = "input.txt";

    int inputParser(std::string &line)
    {
        return std::stoi(line);
    }

    void travse(const std::vector<int> &inputList);
    const std::vector<int> find_two_vals(const std::vector<int> &inputList, int idxFromLeft, int idxFromRight, const int finalValue);

    void solve()
    {
        std::vector<int> inputList = FileUtils::fileReader<int>(fileName, inputParser);

        // sorting the inputList
        std::sort(inputList.begin(), inputList.end());

        travse(inputList);
    }

    void travse(const std::vector<int> &inputList)
    {
        std::vector<int> result = find_two_vals(inputList, 0, inputList.size() - 1, Problem011::FINAL_VAL);
        if (result.size() > 1)
        {
            std::cout << result[0] * result[1] << std::endl;
        }
    }

    const std::vector<int> find_two_vals(const std::vector<int> &inputList, int idxFromLeft, int idxFromRight, const int finalValue)
    {
        std::vector<int> result;
        for (; idxFromLeft < idxFromRight;)
        {
            int sum = inputList[idxFromLeft] + inputList[idxFromRight];
            if (sum < finalValue)
            {
                ++idxFromLeft;
            }
            else if (sum > finalValue)
            {
                --idxFromRight;
            }
            else
            {
                result.push_back(inputList[idxFromLeft]);
                result.push_back(inputList[idxFromRight]);
                break;
            }
        }

        return result;
    }
} // namespace Problem011

namespace Problem012
{
    void travse(const std::vector<int> &inputList);
    const std::vector<int> find_three_vals(const std::vector<int> &inputList, int idxFromLeft, int idxFromRight, const int finalValue);

    void solve()
    {
        std::vector<int> inputList = FileUtils::fileReader<int>(Problem011::fileName, Problem011::inputParser);

        // sorting the inputList
        std::sort(inputList.begin(), inputList.end());

        travse(inputList);
    }

    void travse(const std::vector<int> &inputList)
    {
        const std::vector<int> result = find_three_vals(inputList, 2, inputList.size() - 1, Problem011::FINAL_VAL);
        if (result.size() > 1)
        {
            std::cout << result[0] * result[1] * result[2] << std::endl;
        }
    }

    const std::vector<int> find_three_vals(const std::vector<int> &inputList, int idxFromLeft, int idxFromRight, const int finalValue)
    {
        for (; idxFromLeft < idxFromRight; --idxFromRight)
        {
            std::vector<int> result = Problem011::find_two_vals(inputList, 0, idxFromRight - 1, finalValue - inputList[idxFromRight]);
            if (result.size() > 1)
            {
                result.push_back(inputList[idxFromRight]);
                return result;
            }
        }
        std::vector<int> result;
        return result;
    }
} // namespace Problem012

int main()
{
    Problem011::solve();
    Problem012::solve();
    return 0;
}