#include "board.h"
#include "math.h"
#include <QFile>
#include <QString>
#include <QTextStream>

Board::Board(const std::string &fileName, const unsigned int dimension)
    : dimension(dimension)
{
    if(ReadFromFile(fileName))
    {
        FindZeroTile();
    }
}

Board::~Board()
{
}

bool Board::ReadFromFile(const std::string &fileName)
{
    bool ret = false;
    QString line;
    QFile file(fileName.c_str());

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            unsigned int value;
            in >> value;
            tiles.push_back(value);
        }

        ret = true;
    }
    else
    {
        std::cout << "Can not open file " << fileName << std::endl;
    }

    return ret;
}

bool Board::FindZeroTile()
{
    bool ret = false;

    for(unsigned int rowIndex = 0; rowIndex < dimension; rowIndex++)
    {
        for(unsigned int columnIndex = 0; columnIndex < dimension; columnIndex++)
        {
            if(GetTile(rowIndex, columnIndex) == ZERO_TILE)
            {
                x = rowIndex;
                y = columnIndex;
                ret = true;
            }
        }
    }

    return ret;
}

unsigned int Board::GetTile(const unsigned int row, const unsigned int column) const
{
    return tiles.at(row * dimension + column);
}

void Board::SetTile(const unsigned int row, const unsigned int column, const unsigned int value)
{
    tiles[row * dimension + column] = value;
}

void Board::print() const
{
    std::cout << "ZeroTile " << x << ":" << y << std::endl;

    for(unsigned int rowIndex = 0; rowIndex < dimension; rowIndex++)
    {
        for(unsigned int columnIndex = 0; columnIndex < dimension; columnIndex++)
        {
            std::cout << GetTile(rowIndex, columnIndex) << " ";
        }

        std::cout << std::endl;
    }
}
