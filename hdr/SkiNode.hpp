#include <iostream>


struct KeyDimension
{
    KeyDimension() = default;
    KeyDimension(int r, int c)
    {
        row = r;
        col = c;
    }

    bool operator=(const KeyDimension& key)
    {
        return row == key.row && col == key.col;
    }

    bool operator<(const KeyDimension& key) const {
         return ((row < key.row) || (row == key.row  && col < key.col ));
    }

    int row = 0;
    int col = 0;
};

class SkiNode
{

public:
    SkiNode() = default;
    SkiNode(KeyDimension key, int data) : arrayPoint(key), value(data)
    {}

    SkiNode(KeyDimension key, std::function<int(int)> callback) : arrayPoint(key)
    {
        headUpdateHeightCbk = callback;
    }

    void addChild(SkiNode& child)
    {
        childNode.emplace_back(child);

        // update this node's height
        updateHeight(child.getHeight());


        if (headUpdateHeightCbk)
        {
            // update parent node's height
            headUpdateHeightCbk(height);
        }
    }

    void setCallBakc(std::function<int(int)> callback)
    {
        headUpdateHeightCbk = callback;
    }

    int getHeight()
    {
        return height;
    }

    int getData()
    {
        return value;
    }

    KeyDimension getPoint()
    {
        return arrayPoint;
    }

    int getNumOfChild()
    {
        return childNode.size();
    }

    bool isChildEmpty()
    {
        return (childNode.size() == 0);
    }

    std::function<int(int)> updateHeight = [&](const int childHeight)
                                              {
                                                 height = (childHeight + 1 > height) ? childHeight + 1 : height;
                                                 if (headUpdateHeightCbk)
                                                 {
                                                    // update parent node's height
                                                    headUpdateHeightCbk(height);
                                                 }
                                                 return height;
                                              };

private:

    int height{};
    int value{};
    KeyDimension arrayPoint;
    std::vector<SkiNode> childNode;

    std::function<int(int)> headUpdateHeightCbk;
};