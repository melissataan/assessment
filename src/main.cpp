#include <iostream>
#include <map>
#include <functional>

#include "../hdr/InputParser.hpp"
#include "../hdr/SkiNode.hpp"


int setNodes(const KeyDimension& border, const KeyDimension& currentPoint,
              const std::vector<std::vector<int>>& input, std::vector<std::vector<int>>& lengthMatrix);

void printInput(const std::vector<std::vector<int>>& input)
{
    LOG(("INPUT\n"));
    for (auto i : input)
    {
        for (auto j : i)
            LOG(("%u ", j));
        LOG(("\n"));
    }
    LOG(("\n"));
}

int getPathLength(const KeyDimension& border, int currentSki, const int& childNode, int& lengthValue, KeyDimension point,
    const std::vector<std::vector<int>>& input, std::vector<std::vector<int>>& lengthMatrix)
{
    int pathLength = 0;

    if (childNode < currentSki)
    {
        if (lengthValue != 0)
        {
            pathLength = lengthValue + 1;
        }
        else
        {
            pathLength = setNodes(border, point, input, lengthMatrix) + 1;
        }
    }

    return pathLength;
}

int setNodes(const KeyDimension& border, const KeyDimension& currentPoint,
              const std::vector<std::vector<int>>& input, std::vector<std::vector<int>>& lengthMatrix)
{
    KeyDimension northPoint(currentPoint.row - 1, currentPoint.col);
    KeyDimension eastPoint(currentPoint.row, currentPoint.col + 1);
    KeyDimension southPoint(currentPoint.row + 1, currentPoint.col);
    KeyDimension westPoint(currentPoint.row, currentPoint.col - 1);

    int northPathLength = 0;
    int eastPathLength = 0;
    int southPathLength = 0;
    int westPathLength = 0;

    auto& currentSki = input[currentPoint.row][currentPoint.col];

    if (northPoint.row >= 0)
    {
        auto& childNode = input[northPoint.row][northPoint.col];
        auto& lengthValue = lengthMatrix[northPoint.row][northPoint.col];
        northPathLength = getPathLength(border, currentSki, childNode, lengthValue, northPoint, input, lengthMatrix);
    }

    if (eastPoint.col < border.col)
    {
        auto& childNode = input[eastPoint.row][eastPoint.col];
        auto& lengthValue = lengthMatrix[eastPoint.row][eastPoint.col];
        eastPathLength = getPathLength(border, currentSki, childNode, lengthValue, eastPoint, input, lengthMatrix);
    }

    if (southPoint.row < border.row)
    {
        auto& childNode = input[southPoint.row][southPoint.col];
        auto& lengthValue = lengthMatrix[southPoint.row][southPoint.col];
        southPathLength = getPathLength(border, currentSki, childNode, lengthValue, southPoint, input, lengthMatrix);
    }

    if (westPoint.col >= 0)
    {
        auto& childNode = input[westPoint.row][westPoint.col];
        auto& lengthValue = lengthMatrix[westPoint.row][westPoint.col];
        westPathLength = getPathLength(border, currentSki, childNode, lengthValue, westPoint, input, lengthMatrix);
        /*if (childNode < currentSki)
        {
            if (lengthValue != 0)
            {
                westPathLength = lengthValue + 1;
            }
            else
            {

            }
        }*/
    }

    int maxLength = std::max(std::max(northPathLength, southPathLength), std::max(eastPathLength, westPathLength));

    lengthMatrix[currentPoint.row][currentPoint.col] = maxLength;

    return maxLength;
}

std::vector<int> findLongestSki(const std::vector<std::vector<int>>& input)
{
    int rowLength = input[0][0];
    int colLength = input[0][1];
    KeyDimension skiDimension(rowLength, colLength);

    std::vector<std::vector<int>> inputCopy(input.begin() + 1, input.end());

    std::vector<int> columnValues(inputCopy[0].size(), 0);
    std::vector<std::vector<int>> lengthMatrix(inputCopy.size(), columnValues);

    // print input
    printInput(inputCopy);

    int maxLength = 0;
    std::vector<KeyDimension> nodes;

    for (auto row = 0; row < inputCopy.size(); ++row)
    {
        for (auto col = 0; col < inputCopy[0].size(); ++col)
        {
            KeyDimension currentPoint(row, col);
            int tail = 0;
            int currentNodeLength = setNodes(skiDimension, currentPoint, inputCopy, lengthMatrix);
            if (maxLength < currentNodeLength)
            {
                maxLength = currentNodeLength;
                nodes.clear();
                nodes.push_back(currentPoint);
            }
            else if (maxLength == currentNodeLength)
            {
                nodes.push_back(currentPoint);
            }
        }
    }

    for (auto i : nodes)
    {
        LOG(("HEAD NODES: ROW[%u] COL[%u]\n", i.row, i.col, i));
    }

    LOG(("LOGGGG\n"));
    for (auto i : lengthMatrix)
    {
        for (auto j : i)
            LOG(("%u ", j));
        LOG(("\n"));
    }
    LOG(("\n"));
    LOG(("LOGGGG\n"));

    return input[0];
}

int main()
{
    std::vector<std::vector<int>> vectorInput = utils::readInput();
    int rowSize = 0;
    int colSize = 0;

    if (vectorInput.size() == 0 || vectorInput[0].size() < 2)
    {
        // LOG(("Incorrect input."));
    }

    rowSize = vectorInput[0][0];
    colSize = vectorInput[0][1];

    // LOG(("Dimension is : %ux%u\n", rowSize, colSize));
    KeyDimension skiDimension(rowSize, colSize);

    findLongestSki(vectorInput);

    return 0;
}