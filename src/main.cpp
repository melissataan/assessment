#include <iostream>
#include <map>
#include <functional>

#include "../hdr/InputParser.hpp"
#include "../hdr/SkiNode.hpp"

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

void setNodes(const KeyDimension& border, const KeyDimension& currentPoint,
              std::map<KeyDimension, SkiNode>& keyCollection, SkiNode& ski)
{
    KeyDimension northPoint(currentPoint.row - 1, currentPoint.col);
    KeyDimension eastPoint(currentPoint.row, currentPoint.col + 1);
    KeyDimension southPoint(currentPoint.row + 1, currentPoint.col);
    KeyDimension westPoint(currentPoint.row, currentPoint.col - 1);

    auto& currentSki = keyCollection[currentPoint];

    if (northPoint.row >= 0)
    {
        // add node child
        // TODO: constraint that checks if child data is less than current node data before addChild
        ski.addChild(keyCollection[northPoint]);
    }

    if (eastPoint.col < border.col)
    {
        // add node child
        // TODO: constraint that checks if child data is less than current node data before addChild
        ski.addChild(keyCollection[eastPoint]);
    }

    if (southPoint.row < border.row)
    {
        // add node child
        // TODO: constraint that checks if child data is less than current node data before addChild
        ski.addChild(keyCollection[southPoint]);
    }

    if (westPoint.col >= 0)
    {
        // add node child
        // TODO: constraint that checks if child data is less than current node data before addChild
        ski.addChild(keyCollection[westPoint]);
    }
}

std::vector<int> findLongestSki(const std::vector<std::vector<int>>& input)
{
    std::vector<int> result;

    std::map<KeyDimension, SkiNode> keyCollection;

    int rowLength = input[0][0];
    int colLength = input[0][1];

    KeyDimension skiDimension(rowLength, colLength);

    std::vector<std::vector<int>> inputCopy(input.begin() + 1, input.end());

    // print input data
    printInput(inputCopy);


    // populate keyCollection
    for (auto row = 0; row < rowLength; ++row)
    {
        for (auto col = 0; col < colLength; ++col)
        {
            KeyDimension key(row,col);
            SkiNode skihead(key, inputCopy[row][col]);
            keyCollection.insert(std::pair<KeyDimension, SkiNode>(key, skihead));

            LOG(("Row[%u] Col[%u]: Value[%u]\n", keyCollection[key].getPoint().row,
                    keyCollection[key].getPoint().col, keyCollection[key].getData()));
        }
        LOG(("========================================================================\n\n"));
    }

    // Print row, col, and value of items in key collection
    for (auto& i : keyCollection)
    {
        setNodes(skiDimension, i.first, keyCollection, i.second);
        LOG(("Row[%u] Col[%u]: Value[%u] isChildEmpty[%u] pointer[%p]\n\n",
            i.first.row,
            i.first.col,
            i.second.getData(),
            i.second.getNumOfChild(), &(i.second)));
    }

    return result;
}

int main()
{
    std::vector<std::vector<int>> vectorInput = utils::readInput();
    int rowSize = 0;
    int colSize = 0;

    if (vectorInput.size() == 0 || vectorInput[0].size() < 2)
    {
        LOG(("Incorrect input."));
    }

    rowSize = vectorInput[0][0];
    colSize = vectorInput[0][1];

    LOG(("Dimension is : %ux%u\n", rowSize, colSize));
    KeyDimension skiDimension(rowSize, colSize);

    findLongestSki(vectorInput);

    return 0;
}