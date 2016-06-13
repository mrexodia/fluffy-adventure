#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class PointMatrix
{
public:
    explicit PointMatrix(int size)
    {
        mMatrix.resize(size * size);
        for(size_t i = 0; i < mMatrix.size(); i++)
            mMatrix[i] = 0;
    }

    int & at(int x, int y)
    {
        return mMatrix[x * x + y];
    }

private:
    std::vector<int> mMatrix;
};

class Binviz
{
public:
    explicit Binviz(unsigned char* data, size_t size)
        : mData(data),
          mSize(size)
    {
    }

    void ProducePoints(PointMatrix & points, int & maxDups)
    {
        maxDups = 0;
        for(size_t i=0; i < mSize - 1; i++)
        {
            int & p = points.at(mData[i], mData[i + 1]);
            p++;
            if(p > maxDups)
                maxDups = p;
        }
    }

private:
    unsigned char* mData;
    size_t mSize;
};

#endif // GRAPH_H

