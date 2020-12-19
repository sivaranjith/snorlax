#include "../utils/file_utils.h"
#include <iostream>
#include <map>
#include <set>
#include <regex>
#include <sstream>

namespace Problem071
{
    const char* fileName = "input.txt";

    void parserFunction(std::map<std::string, std::set<std::string>> &adjacent_list, std::string &line)
    {
        std::string delimter = "bag";

        unsigned int start = 0U;
        auto end = line.find(delimter);

        std::string containerBag = line.substr(start, end - start);
        if(containerBag.size() > 0)
        {
            containerBag = containerBag.substr(0, containerBag.size() - 1);
        }
        start = end + delimter.length();
        end = line.find(delimter, start);

        while(end != std::string::npos)
        {
            std::string innerBag = line.substr(start, end - start);
            if(innerBag == "s contain no other")
            {
                break;
            }
            else
            {
                std::stringstream checker(innerBag);
                std::string result;
                int count = -1;
                std::string backName;
                while(std::getline(checker, result, ' '))
                {
                    if(count != -1)
                    {
                        backName += (backName != "" ? " " : "") + result;
                    }
                    if(result[0] >= 48 && result[0] <= 57)
                    {
                        count = result[0] - 48;
                    }
                }

                // std::cout << "size::" << backName.size() << "::" << backName << "::" << std::endl;
                // std::cout << "checking::" << (adjacent_list.find(backName) == adjacent_list.end()) << std::endl;
                if(adjacent_list.find(backName) == adjacent_list.end())
                {
                    std::set<std::string> innerBags;
                    innerBags.insert(containerBag);
                    adjacent_list.insert({backName, std::move(innerBags)});
                }
                else
                {
                    // for(auto &it : adjacent_list.find(backName)->second)
                    // {
                        // std::cout << backName << "::" << it << "::" << containerBag << std::endl;
                    // }
                    adjacent_list.find(backName)->second.insert(containerBag);
                }

            }

            start = end + delimter.length();
            end = line.find(delimter, start);
        }
    }

    std::string dumyParse(std::string &line)
    {
        return line;
    }

    int _countShinyGoldBag(const std::map<std::string, std::set<std::string>> &adjacent_list, const std::string &targetBagName, std::set<std::string> &memoziation)
    {
        auto it = adjacent_list.find(targetBagName);
        int count = 0;
        if(it != adjacent_list.end())
        {
            for(auto &it1 : it->second)
            {
                if(memoziation.find(it1) == memoziation.end())
                {
                    count += 1;
                    memoziation.insert(it1);
                    count += _countShinyGoldBag(adjacent_list, it1, memoziation);
                }
            }
        }
        return count;
    }

    int countShinyGoldBag(const std::map<std::string, std::set<std::string>> &adjacent_list, const std::string &targetBagName)
    {
        std::set<std::string> memoziation;
        return _countShinyGoldBag(adjacent_list, targetBagName, memoziation);
    }

    void solve()
    {
        std::vector<std::string> lines = FileUtils::fileReader(fileName, dumyParse);

        std::map<std::string, std::set<std::string>> adjacent_list;
        for(std::string line : lines)
        {
            parserFunction(adjacent_list, line);
        }

        std::cout << countShinyGoldBag(adjacent_list, "shiny gold") << std::endl;
    }
}

namespace Problem072
{
    void parserFunction(std::map<std::string, std::map<std::string, int>> &adjacent_list, std::string &line)
    {
        std::string delimter = "bag";

        unsigned int start = 0U;
        auto end = line.find(delimter);

        std::string containerBag = line.substr(start, end - start);
        if(containerBag.size() > 0)
        {
            containerBag = containerBag.substr(0, containerBag.size() - 1);
        }
        start = end + delimter.length();
        end = line.find(delimter, start);

        std::map<std::string, int> containerBagDetails;
        while(end != std::string::npos)
        {
            std::string innerBag = line.substr(start, end - start);
            if(innerBag == "s contain no other")
            {
                break;
            }
            else
            {
                std::stringstream checker(innerBag);
                std::string result;
                int count = 0;
                std::string backName;
                while(std::getline(checker, result, ' '))
                {
                    if(count > 0)
                    {
                        backName += (backName != "" ? " " : "") + result;
                    }
                    if(result[0] >= 48 && result[0] <= 57)
                    {
                        count = result[0] - 48;
                    }
                }

                if(count > 0)
                {
                    containerBagDetails.insert({backName, count});
                }
            }

            start = end + delimter.length();
            end = line.find(delimter, start);
        }

        adjacent_list.insert({containerBag, containerBagDetails});
    }

    int _getBagCount(const std::map<std::string, std::map<std::string, int>> &adjacent_list, const std::string &targetBag, std::map<std::string, int> &memoziation)
    {
        int count = 0;
        auto it = adjacent_list.find(targetBag);
        if(memoziation.find(it->first) == memoziation.end())
        {
            for(auto it1 = it->second.begin(); it1 != it->second.end(); ++it1)
            {
                if(memoziation.find(it1->first) == memoziation.end())
                {
                    _getBagCount(adjacent_list, it1->first, memoziation);
                }
                count += it1->second * (1 + memoziation.find(it1->first)->second);
            }
            memoziation.insert({it->first, count});
        }
        return memoziation.find(targetBag)->second;
    }

    int getBagCount(std::map<std::string, std::map<std::string, int>> &adjacent_list, const std::string &targetBag)
    {
        std::map<std::string, int> memoziation;
        return _getBagCount(adjacent_list, targetBag, memoziation);
    }

    void solve()
    {
        std::vector<std::string> lines = FileUtils::fileReader(Problem071::fileName, Problem071::dumyParse);

        std::map<std::string, std::map<std::string, int>> adjacent_list;
        for(std::string line : lines)
        {
            parserFunction(adjacent_list, line);
        }

        std::cout << getBagCount(adjacent_list, "shiny gold") << std::endl;
    }
}

int main()
{
    Problem071::solve();
    Problem072::solve();
    return 0;
}