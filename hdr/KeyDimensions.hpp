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
