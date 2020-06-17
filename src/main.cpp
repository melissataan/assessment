#include <iostream>
#include <map>
#include <functional>

#include "../hdr/InputParser.hpp"
#include "../hdr/SkiNode.hpp"

struct NodeCtx
{
    int data = 0;
    int pathLength = 0;
    int tail = 0;
    std::vector<int> vectorPath;

    NodeCtx& operator=(NodeCtx node)
    {
        data = node.data;
        pathLength = node.pathLength;
        tail = node.tail;
        vectorPath = node.vectorPath;

        return *this;
    }
};

NodeCtx findNodePath(const KeyDimension& border,
                     const KeyDimension& currentNode,
                     const std::vector<std::vector<int>>& inputList,
                     std::vector<std::vector<NodeCtx>>& pathList)
{
    KeyDimension northNode(currentNode.row - 1, currentNode.col);
    KeyDimension eastNode(currentNode.row, currentNode.col + 1);
    KeyDimension southNode(currentNode.row + 1, currentNode.col);
    KeyDimension westNode(currentNode.row, currentNode.col - 1);
    NodeCtx northNodeCtx;
    NodeCtx eastNodeCtx;
    NodeCtx southNodeCtx;
    NodeCtx westNodeCtx;

    bool isNoNeighborExist = true;
    NodeCtx& currentNodeCtx = pathList[currentNode.row][currentNode.col];
    int currentNodeValue = inputList[currentNode.row][currentNode.col];
    currentNodeCtx.vectorPath.push_back(currentNodeValue);

    if (northNode.row >= 0)
    {
        int neighborValue = inputList[northNode.row][northNode.col];
        if (neighborValue < currentNodeValue)
        {
            isNoNeighborExist = false;
            if (pathList[northNode.row][northNode.col].pathLength == 0)
            {
                northNodeCtx = findNodePath(border, northNode, inputList, pathList);
            }
            else
            {
                northNodeCtx = pathList[northNode.row][northNode.col];
            }
            northNodeCtx.pathLength += 1;

            LOG(("NORTH\t\tLINE[%u]\t___ CURRENT PATH ROW[%u] COL[%u] DATA[%u] PATH_LENGTH[%u] TAIL[%u]\n", __LINE__, currentNode.row, currentNode.col, currentNodeCtx.data, currentNodeCtx.pathLength, northNodeCtx.tail));
        }
    }

    if (eastNode.col < border.col)
    {
        int neighborValue = inputList[eastNode.row][eastNode.col];
        if (neighborValue < currentNodeValue)
        {
            isNoNeighborExist = false;
            if (pathList[eastNode.row][eastNode.col].pathLength == 0)
            {
                eastNodeCtx = findNodePath(border, eastNode, inputList, pathList);
            }
            else
            {
                eastNodeCtx = pathList[eastNode.row][eastNode.col];
            }
            eastNodeCtx.pathLength += 1;

            LOG(("EAST\t\tLINE[%u]\t___ CURRENT PATH ROW[%u] COL[%u] DATA[%u] PATH_LENGTH[%u] TAIL[%u]\n", __LINE__, currentNode.row, currentNode.col, currentNodeCtx.data, currentNodeCtx.pathLength, eastNodeCtx.tail));
        }
    }

    if (southNode.row < border.row)
    {
        int neighborValue = inputList[southNode.row][southNode.col];
        if (neighborValue < currentNodeValue)
        {
            isNoNeighborExist = false;
            if (pathList[southNode.row][southNode.col].pathLength == 0)
            {
                southNodeCtx = findNodePath(border, southNode, inputList, pathList);
            }
            else
            {
                southNodeCtx = pathList[southNode.row][southNode.col];
            }
            southNodeCtx.pathLength += 1;

            LOG(("SOUTH\t\tLINE[%u]\t___ CURRENT PATH ROW[%u] COL[%u] DATA[%u] PATH_LENGTH[%u] TAIL[%u]\n", __LINE__, currentNode.row, currentNode.col, currentNodeCtx.data, currentNodeCtx.pathLength, southNodeCtx.tail));
        }
    }

    if (westNode.col >= 0)
    {
        int neighborValue = inputList[westNode.row][westNode.col];
        if (neighborValue < currentNodeValue)
        {
            isNoNeighborExist = false;
            if (pathList[westNode.row][westNode.col].pathLength == 0)
            {
                westNodeCtx = findNodePath(border, westNode, inputList, pathList);
            }
            else
            {
                westNodeCtx = pathList[westNode.row][westNode.col];
            }
            westNodeCtx.pathLength += 1;

            LOG(("WEST\t\tLINE[%u]\t___ CURRENT PATH ROW[%u] COL[%u] DATA[%u] PATH_LENGTH[%u] TAIL[%u]\n", __LINE__, currentNode.row, currentNode.col, currentNodeCtx.data, currentNodeCtx.pathLength, westNodeCtx.tail));
        }
    }

    if (isNoNeighborExist)
    {
        currentNodeCtx.data = currentNodeValue;
        currentNodeCtx.tail = currentNodeValue;
        currentNodeCtx.pathLength = 0;
        LOG(("LINE[%u]\t___ CURRENT PATH ROW[%u] COL[%u] DATA[%u] PATH_LENGTH[%u] TAIL[%u]\n", __LINE__, currentNode.row, currentNode.col, currentNodeCtx.data, currentNodeCtx.pathLength, currentNodeCtx.tail));

        NodeCtx returnNode = currentNodeCtx;
        return returnNode;
    }
    else
    {
        int maxLength = std::max(std::max(northNodeCtx.pathLength, southNodeCtx.pathLength),
                                 std::max(eastNodeCtx.pathLength, westNodeCtx.pathLength));

        std::vector<int> tails;
        if (maxLength == northNodeCtx.pathLength)
        {
            tails.push_back(northNodeCtx.tail);
        }
        if (maxLength == eastNodeCtx.pathLength)
        {
            tails.push_back(eastNodeCtx.tail);
        }
        if (maxLength == southNodeCtx.pathLength)
        {
            tails.push_back(southNodeCtx.tail);
        }
        if (maxLength == westNodeCtx.pathLength)
        {
            tails.push_back(westNodeCtx.tail);
        }

        int min_tail = *(std::min_element(tails.begin(), tails.end()));

        if (min_tail == northNodeCtx.tail && maxLength == northNodeCtx.pathLength)
        {
            currentNodeCtx.vectorPath.insert(currentNodeCtx.vectorPath.end(), northNodeCtx.vectorPath.begin(), northNodeCtx.vectorPath.end());
            currentNodeCtx.tail = northNodeCtx.tail;
            currentNodeCtx.data = currentNodeValue;
            currentNodeCtx.pathLength = northNodeCtx.pathLength;
            LOG(("LINE[%u]\t___ CURRENT PATH ROW[%u] COL[%u] DATA[%u] PATH_LENGTH[%u] TAIL[%u]\n", __LINE__, currentNode.row, currentNode.col, currentNodeCtx.data, currentNodeCtx.pathLength, currentNodeCtx.tail));
        }
        else if (min_tail == eastNodeCtx.tail && maxLength == eastNodeCtx.pathLength)
        {
            currentNodeCtx.vectorPath.insert(currentNodeCtx.vectorPath.end(), eastNodeCtx.vectorPath.begin(), eastNodeCtx.vectorPath.end());
            currentNodeCtx.tail = eastNodeCtx.tail;
            currentNodeCtx.data = currentNodeValue;
            currentNodeCtx.pathLength = eastNodeCtx.pathLength;
            LOG(("LINE[%u]\t___ CURRENT PATH ROW[%u] COL[%u] DATA[%u] PATH_LENGTH[%u] TAIL[%u]\n", __LINE__, currentNode.row, currentNode.col, currentNodeCtx.data, currentNodeCtx.pathLength, currentNodeCtx.tail));
        }
        else if (min_tail == southNodeCtx.tail && maxLength == southNodeCtx.pathLength)
        {
            currentNodeCtx.vectorPath.insert(currentNodeCtx.vectorPath.end(), southNodeCtx.vectorPath.begin(), southNodeCtx.vectorPath.end());
            currentNodeCtx.tail = southNodeCtx.tail;
            currentNodeCtx.data = currentNodeValue;
            currentNodeCtx.pathLength = southNodeCtx.pathLength;
            LOG(("LINE[%u]\t___ CURRENT PATH ROW[%u] COL[%u] DATA[%u] PATH_LENGTH[%u] TAIL[%u]\n", __LINE__, currentNode.row, currentNode.col, currentNodeCtx.data, currentNodeCtx.pathLength, currentNodeCtx.tail));
        }
        else if (min_tail == westNodeCtx.tail && maxLength == westNodeCtx.pathLength)
        {
            currentNodeCtx.vectorPath.insert(currentNodeCtx.vectorPath.end(), westNodeCtx.vectorPath.begin(), westNodeCtx.vectorPath.end());
            currentNodeCtx.tail = westNodeCtx.tail;
            currentNodeCtx.data = currentNodeValue;
            currentNodeCtx.pathLength = westNodeCtx.pathLength;
            LOG(("LINE[%u]\t___ CURRENT PATH ROW[%u] COL[%u] DATA[%u] PATH_LENGTH[%u] TAIL[%u]\n", __LINE__, currentNode.row, currentNode.col, currentNodeCtx.data, currentNodeCtx.pathLength, currentNodeCtx.tail));
        }
    }

    LOG(("PRINTING PATHS\n"));
    for (auto i : currentNodeCtx.vectorPath)
    {
        LOG(("%u ", i));
    }
    LOG(("\n"));
    LOG(("LOGGGG\n"));
    return currentNodeCtx;
}

std::vector<int> findLongestSki(const std::vector<std::vector<int>>& input)
{
    int rowLength = input[0][0];
    int colLength = input[0][1];
    KeyDimension skiDimension(rowLength, colLength);

    std::vector<std::vector<int>> skiMatrix(input.begin() + 1, input.end());

    std::vector<NodeCtx> columnValues(skiMatrix[0].size(), NodeCtx());
    std::vector<std::vector<NodeCtx>> pathCtxList(skiMatrix.size(), columnValues);

    int maxLength = 0;

    std::vector<NodeCtx> nodes;

    for (auto row = 0; row < skiMatrix.size(); ++row)
    {
        for (auto col = 0; col < skiMatrix[0].size(); ++col)
        {
            KeyDimension currentNode(row, col);
            if (pathCtxList[row][col].pathLength == 0)
            {
                NodeCtx currentNodeCtx = findNodePath(skiDimension, currentNode, skiMatrix, pathCtxList);
                int currentNodeLength = currentNodeCtx.pathLength;
                LOG(("LINE[%u]\t___ CURRENT PATH ROW[%u] COL[%u] DATA[%u] PATH_LENGTH[%u] TAIL[%u]\n", __LINE__, currentNode.row, currentNode.col, currentNodeCtx.data, currentNodeCtx.pathLength, currentNodeCtx.tail));

                if (maxLength < currentNodeLength)
                {
                    maxLength = currentNodeLength;
                    nodes.clear();
                    nodes.push_back(currentNodeCtx);
                }
                else if (maxLength == currentNodeLength)
                {
                    nodes.push_back(currentNodeCtx);
                }
            }
        }
    }


    for (auto i : nodes)
    {
        LOG(("HEAD NODES: DATA[%u] PATH_LENGTH[%u] TAIL[%u]\n", i.data, i.pathLength, i.tail));
        for (auto elem : i.vectorPath)
        {
            // Do something
            LOG(("%u ", elem));

        }
        LOG(("\n"));
    }

    LOG(("LOGGGG\n"));
    for (auto i : pathCtxList)
    {
        for (auto j : i)
            LOG(("%u ", j.pathLength));
        LOG(("\n"));
    }
    LOG(("\n"));
    LOG(("LOGGGG\n"));

    LOG(("LAST PART__\n"));
    int longestPath = nodes[0].data - nodes[0].tail;
    LOG(("LONGEST PATH: %u", longestPath));
    // for (auto node : nodes)
    // {
    //     LOG("HEAD: [%u]")
    // }

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