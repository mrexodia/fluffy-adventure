#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <set>
#include <unordered_map>
#include <QDebug>

#define MATRIX_SIZE 256

class PointMatrix
{
public:
    explicit PointMatrix()
    {
        for(size_t i = 0; i < MATRIX_SIZE; i++)
            for(size_t j = 0; j < MATRIX_SIZE; j++)
                mMatrix[i][j] = 0;
    }

    void inc(int x, int y)
    {
        mMatrix[x][y]++;
    }

    unsigned long long get(int x, int y)
    {
        return mMatrix[x][y];
    }

    void getDistribution(std::vector<unsigned long long> & plot)
    {
        plot.clear();
        std::set<unsigned long long> s;
        for(size_t x = 0; x < MATRIX_SIZE; x++)
            for(size_t y = 0; y < MATRIX_SIZE; y++)
                s.insert(mMatrix[x][y]);
        plot.reserve(s.size());
        for(auto y : s)
            plot.push_back(y);
    }

    void sliceDistribution(int count, const std::vector<unsigned long long> & plot, std::unordered_map<unsigned long long, int> & slices)
    {
        slices.clear();
        int size = int(plot.size()) / count;
        for(int i = 0; i < count; i++)
            for(int j = 0; j < size; j++)
                slices[plot.at(i * size + j)] = i;
    }

    int size()
    {
        return MATRIX_SIZE;
    }

private:
    unsigned long long mMatrix[MATRIX_SIZE][MATRIX_SIZE];
};

class Binviz
{
public:
    explicit Binviz(unsigned char* data, size_t size)
        : mData(data),
          mSize(size)
    {
    }

    void ProducePoints(PointMatrix & points)
    {
        for(size_t i = 0; i < mSize - 1; i++)
            points.inc(mData[i], mData[i + 1]);
        std::vector<unsigned long long> plot;
    }

private:
    unsigned char* mData;
    size_t mSize;
};

#endif // GRAPH_H

