#include <iostream>
#include <map>

#include "../hdr/input_parser.hpp"

// struct SkiNode
// {
// };

// struct SkiRelation
// {
// };

struct KeyDimension
{
    KeyDimension(int row, int col)
    {
        this->row = row;
        this->col = col;
    }

    bool operator=(const KeyDimension& key)
    {
        return row == key.row && col == key.col;
    }

    bool operator<(const KeyDimension& key) const {
         return (row < key.row  || (row == key.row  && col < key.col ));
    }

    int row = 0;
    int col = 0;
};

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

std::vector<int> findLongestSki(const std::vector<std::vector<int>>& input)
{
    std::vector<int> result;

    std::map<KeyDimension, int> keyMap;

    int rowLength = input[0][0];
    int colLength = input[0][1];

    std::vector<std::vector<int>> inputCopy(input.begin() + 1, input.end());

    // print input data
    printInput(inputCopy);

    for (auto row = 0; row < rowLength; ++row)
    {
        for (auto col = 0; col < colLength; ++col)
        {
            KeyDimension key(row,col);
            keyMap[key] = inputCopy[row][col];
        }
    }

    // Print row, col, and value
    // for (auto i : keyMap)
    // {
    //     LOG(("Row[%u] Col[%u]: Value[%u]\n\n", i.first.row, i.first.col, i.second));
    // }

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

    findLongestSki(vectorInput);

    return 0;
}