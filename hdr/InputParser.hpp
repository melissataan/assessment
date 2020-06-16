#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>

#define LOG(pargs) printf pargs
#define LOGN() printf("\n")

namespace logger
{
    template <typename T>
    void vectorPrint(std::vector<T> in)
    {
        for (auto i : in)
        {
            LOG(("%u ", i));
        }
        LOGN();
    }
} // namespace logger

namespace utils
{

std::vector<std::vector<int>> readInput()
{
    std::ifstream inFile;
    std::string fileName = "map.txt";
    inFile.open(fileName);
    if (!inFile) {
        std::cerr << "Unable to open file \n" + fileName + "\n";
        exit(1);
    }

    // read lines from input file
    std::string line;
    std::vector<std::string> vecOfStrs;
    while (std::getline(inFile, line))
    {
        if(line.size() > 0)
            vecOfStrs.push_back(line);
    }

    std::vector<std::vector<int>> returnInput;
    for (auto i : vecOfStrs)
    {
        std::vector<int> inputPerLine;
        std::string      tmpString = "";
        auto             stringToInt =  [&inputPerLine](std::string tmpStr)
                                        {
                                            double tmp = 0;
                                            std::stringstream(tmpStr) >> tmp;
                                            inputPerLine.push_back(tmp);
                                        };

        // traverse characters per line
        for (auto character : i)
        {
            if (character == ' ')
            {
                stringToInt(tmpString);
                tmpString = "";
            }
            else
            {
                tmpString += character;
            }
        }

        stringToInt(tmpString);
        returnInput.push_back(inputPerLine);
    }

    return returnInput;
}

} // namespace utils
