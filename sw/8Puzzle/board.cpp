/*
 * 8Puzzle: Software for solving well known 8 puzzle problem
 *
 * BLG 521E Advanced Artificial Intelligence HW#1
 *
 * Copyright (C)  Mehmet AKTAS 0504181576 13.03.2019
 *
 */

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
		FindMovableDirections();
	}
}

Board::Board(const Board &parent, const Board::MoveDirectionsEnum direction)
{
	this->tiles = parent.tiles;
	this->dimension = parent.dimension;
	this->zeroRow = parent.zeroRow;
	this->zeroColumn = parent.zeroColumn;

	MoveToDirection(direction);
	FindMovableDirections();
	BranchParentDirection(direction);
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
				zeroRow = rowIndex;
				zeroColumn = columnIndex;
                ret = true;
            }
        }
    }

	return ret;
}

void Board::FindMovableDirections()
{
	directions.resize(MoveDirectionCount, true);

	if(zeroRow == 0)
	{
		directions[Board::MoveDirection_up] = false;
	}
	else if(zeroRow == (dimension - 1))
	{
		directions[Board::MoveDirection_down] = false;
	}
	else
	{
		/* Movable up and down */
	}

	if(zeroColumn == 0)
	{
		directions[Board::MoveDirection_left] = false;
	}
	else if(zeroColumn == (dimension - 1))
	{
		directions[Board::MoveDirection_right] = false;
	}
	else
	{
		/* Movable up and down */
	}
}

bool Board::IsMovable(const Board::MoveDirectionsEnum moveDirection)
{
	unsigned int directionPos = static_cast<unsigned int>(moveDirection);
	return directions.at(directionPos);
}

bool Board::MoveToDirection(const Board::MoveDirectionsEnum moveDirection)
{
	bool ret = false;

	if(IsMovable(moveDirection))
	{
		ret = true;

		switch(moveDirection)
		{
			case Board::MoveDirection_right:
			{
				/* Swap zero tile with the tile on its right */
				unsigned int value = GetTile(zeroRow, zeroColumn + 1);
				SetTile(zeroRow, zeroColumn, value);
				SetTile(zeroRow, zeroColumn + 1, ZERO_TILE);
				zeroColumn++;
				break;
			}

			case Board::MoveDirection_left:
			{
				/* Swap zero tile with the tile on its left */
				unsigned int value = GetTile(zeroRow, zeroColumn - 1);
				SetTile(zeroRow, zeroColumn, value);
				SetTile(zeroRow, zeroColumn - 1, ZERO_TILE);
				zeroColumn--;
				break;
			}

			case Board::MoveDirection_up:
			{
				/* Swap zero tile with the tile on its up */
				unsigned int value = GetTile(zeroRow - 1, zeroColumn);
				SetTile(zeroRow, zeroColumn, value);
				SetTile(zeroRow - 1, zeroColumn, ZERO_TILE);
				zeroRow--;
				break;
			}

			case Board::MoveDirection_down:
			{
				/* Swap zero tile with the tile on its right */
				unsigned int value = GetTile(zeroRow + 1, zeroColumn);
				SetTile(zeroRow, zeroColumn, value);
				SetTile(zeroRow + 1, zeroColumn, ZERO_TILE);
				zeroRow++;
				break;
			}

			default:
				break;
		}
	}

	return ret;
}

void Board::BranchParentDirection(const Board::MoveDirectionsEnum moveDirection)
{
	switch(moveDirection)
	{
		case Board::MoveDirection_right:
		{
			/* Branch left move */
			directions[MoveDirection_left] = false;
			break;
		}

		case Board::MoveDirection_left:
		{
			/* Branch right move */
			directions[MoveDirection_right] = false;
			break;
		}

		case Board::MoveDirection_up:
		{
			/* Branch down move */
			directions[MoveDirection_down] = false;
			break;
		}

		case Board::MoveDirection_down:
		{
			/* Branch up move */
			directions[MoveDirection_up] = false;
			break;
		}

		default:
			break;
	}
}

bool Board::IsGoal()
{
	bool ret = true;
	unsigned int currentValue = 1;

	if(tiles.back() != 0)
	{
		ret = false;
	}
	else
	{
		for(unsigned int index = 0; index < tiles.size() - 1; index++)
		{
			if(tiles.at(index) != currentValue)
			{
				ret = false;
				break;
			}

			currentValue++;
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
	std::cout << std::endl << "ZeroTile " << zeroRow << ":" << zeroColumn << std::endl;

    for(unsigned int rowIndex = 0; rowIndex < dimension; rowIndex++)
    {
        for(unsigned int columnIndex = 0; columnIndex < dimension; columnIndex++)
        {
            std::cout << GetTile(rowIndex, columnIndex) << " ";
        }

        std::cout << std::endl;
    }
}
