#include <iostream>
#include <map>
#include <functional>

#include "../hdr/InputParser.hpp"
#include "../hdr/KeyDimensions.hpp"

struct NodeCtx
{
    int data = 0;
    int pathLength = 0;
    int tail = 0;
    bool isChecked = false;
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
                     std::vector<std::vector<NodeCtx>>& pathList);

void processNeighborNode(const KeyDimension& border,
                         const KeyDimension& neighborNode,
                         NodeCtx& neighborNodeCtx,
                         const std::vector<std::vector<int>>& inputList,
                         std::vector<std::vector<NodeCtx>>& pathList,
                         int currentNodeValue,
                         bool& isNoNeighborExist)
{
    int neighborValue = inputList[neighborNode.row][neighborNode.col];
    if (neighborValue < currentNodeValue)
    {
        isNoNeighborExist = false;
        if (!pathList[neighborNode.row][neighborNode.col].isChecked)
        {
            neighborNodeCtx = findNodePath(border, neighborNode, inputList, pathList);
        }
        else
        {
            neighborNodeCtx = pathList[neighborNode.row][neighborNode.col];
        }
        neighborNodeCtx.pathLength += 1;
    }
}

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

    int currentNodeValue = inputList[currentNode.row][currentNode.col];

    NodeCtx& currentNodeCtx = pathList[currentNode.row][currentNode.col];
    currentNodeCtx.vectorPath.push_back(currentNodeValue);
    currentNodeCtx.isChecked = true;

    if (northNode.row >= 0)
    {
        processNeighborNode(border, northNode, northNodeCtx, inputList, pathList, currentNodeValue, isNoNeighborExist);
        // int neighborValue = inputList[northNode.row][northNode.col];
        // if (neighborValue < currentNodeValue)
        // {
        //     isNoNeighborExist = false;
        //     if (!pathList[northNode.row][northNode.col].isChecked)
        //     {
        //         northNodeCtx = findNodePath(border, northNode, inputList, pathList);
        //     }
        //     else
        //     {
        //         northNodeCtx = pathList[northNode.row][northNode.col];
        //     }
        //     northNodeCtx.pathLength += 1;
        // }
    }

    if (eastNode.col < border.col)
    {
        processNeighborNode(border, eastNode, eastNodeCtx, inputList, pathList, currentNodeValue, isNoNeighborExist);
        // int neighborValue = inputList[eastNode.row][eastNode.col];
        // if (neighborValue < currentNodeValue)
        // {
        //     isNoNeighborExist = false;
        //     if (!pathList[eastNode.row][eastNode.col].isChecked)
        //     {
        //         eastNodeCtx = findNodePath(border, eastNode, inputList, pathList);
        //     }
        //     else
        //     {
        //         eastNodeCtx = pathList[eastNode.row][eastNode.col];
        //     }
        //     eastNodeCtx.pathLength += 1;
        // }
    }

    if (southNode.row < border.row)
    {
        processNeighborNode(border, southNode, southNodeCtx, inputList, pathList, currentNodeValue, isNoNeighborExist);
        // int neighborValue = inputList[southNode.row][southNode.col];
        // if (neighborValue < currentNodeValue)
        // {
        //     isNoNeighborExist = false;
        //     if (!pathList[southNode.row][southNode.col].isChecked)
        //     {
        //         southNodeCtx = findNodePath(border, southNode, inputList, pathList);
        //     }
        //     else
        //     {
        //         southNodeCtx = pathList[southNode.row][southNode.col];
        //     }
        //     southNodeCtx.pathLength += 1;
        // }
    }

    if (westNode.col >= 0)
    {
        processNeighborNode(border, westNode, westNodeCtx, inputList, pathList, currentNodeValue, isNoNeighborExist);
        // int neighborValue = inputList[westNode.row][westNode.col];
        // if (neighborValue < currentNodeValue)
        // {
        //     isNoNeighborExist = false;
        //     if (!pathList[westNode.row][westNode.col].isChecked)
        //     {
        //         westNodeCtx = findNodePath(border, westNode, inputList, pathList);
        //     }
        //     else
        //     {
        //         westNodeCtx = pathList[westNode.row][westNode.col];
        //     }
        //     westNodeCtx.pathLength += 1;
        // }
    }

    if (isNoNeighborExist)
    {
        currentNodeCtx.data = currentNodeValue;
        currentNodeCtx.tail = currentNodeValue;
        currentNodeCtx.pathLength = 0;
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

        std::function<void(NodeCtx&)> storeContext = [&currentNodeCtx, &currentNodeValue](NodeCtx& neighborNodeCtx)
                                             {
                                                currentNodeCtx.vectorPath.insert(currentNodeCtx.vectorPath.end(),
                                                                                 neighborNodeCtx.vectorPath.begin(),
                                                                                 neighborNodeCtx.vectorPath.end());
                                                currentNodeCtx.tail = neighborNodeCtx.tail;
                                                currentNodeCtx.data = currentNodeValue;
                                                currentNodeCtx.pathLength = neighborNodeCtx.pathLength;
                                             };

        if (min_tail == northNodeCtx.tail && maxLength == northNodeCtx.pathLength)
        {
            storeContext(northNodeCtx);
            // currentNodeCtx.vectorPath.insert(currentNodeCtx.vectorPath.end(), northNodeCtx.vectorPath.begin(), northNodeCtx.vectorPath.end());
            // currentNodeCtx.tail = northNodeCtx.tail;
            // currentNodeCtx.data = currentNodeValue;
            // currentNodeCtx.pathLength = northNodeCtx.pathLength;
        }
        else if (min_tail == eastNodeCtx.tail && maxLength == eastNodeCtx.pathLength)
        {
            storeContext(eastNodeCtx);
            // currentNodeCtx.vectorPath.insert(currentNodeCtx.vectorPath.end(), eastNodeCtx.vectorPath.begin(), eastNodeCtx.vectorPath.end());
            // currentNodeCtx.tail = eastNodeCtx.tail;
            // currentNodeCtx.data = currentNodeValue;
            // currentNodeCtx.pathLength = eastNodeCtx.pathLength;
        }
        else if (min_tail == southNodeCtx.tail && maxLength == southNodeCtx.pathLength)
        {
            storeContext(southNodeCtx);
            // currentNodeCtx.vectorPath.insert(currentNodeCtx.vectorPath.end(), southNodeCtx.vectorPath.begin(), southNodeCtx.vectorPath.end());
            // currentNodeCtx.tail = southNodeCtx.tail;
            // currentNodeCtx.data = currentNodeValue;
            // currentNodeCtx.pathLength = southNodeCtx.pathLength;
        }
        else if (min_tail == westNodeCtx.tail && maxLength == westNodeCtx.pathLength)
        {
            storeContext(westNodeCtx);
            // currentNodeCtx.vectorPath.insert(currentNodeCtx.vectorPath.end(), westNodeCtx.vectorPath.begin(), westNodeCtx.vectorPath.end());
            // currentNodeCtx.tail = westNodeCtx.tail;
            // currentNodeCtx.data = currentNodeValue;
            // currentNodeCtx.pathLength = westNodeCtx.pathLength;
        }
    }

    return currentNodeCtx;
}

std::vector<int> findLongestNodePath(const std::vector<NodeCtx>& nodes)
{
    if (nodes.size() == 0) return std::vector<int>();

    int dropValue = nodes[0].data - nodes[0].tail;
    auto longestSkiNode = nodes[0].vectorPath;
    for (auto node : nodes)
    {
        int tmpDropValue = node.data - node.tail;
        if (tmpDropValue > dropValue)
        {
            longestSkiNode = node.vectorPath;
            dropValue = tmpDropValue;
        }
    }

    LOG(("LONGEST PATH IS: \n"));
    for (auto i : longestSkiNode)
    {
        LOG(("%u ", i));
    }
    LOG(("\n"));

    LOG(("DROP: %u\n", dropValue));
    LOG(("LENGTH: %u\n", (int)(longestSkiNode.size())));
    return longestSkiNode;
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
            if (!pathCtxList[row][col].isChecked)
            {
                NodeCtx currentNodeCtx = findNodePath(skiDimension, currentNode, skiMatrix, pathCtxList);
                int currentNodeLength = currentNodeCtx.pathLength;
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


    auto longestSkiNode = findLongestNodePath(nodes);

    return longestSkiNode;
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

    KeyDimension skiDimension(rowSize, colSize);

    auto result = findLongestSki(vectorInput);

    return 0;
}