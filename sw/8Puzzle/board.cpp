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

unsigned int Board::staticID = 0;
bool Board::finished = false;
Board::Boards Board::boards;

static std::vector<unsigned int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0}; /* Goal State */

/**
 * @brief Board::Board
 * Constructor
 * Creates root (initial) tile from given file
 * @param fileName
 * @param dimension
 */
Board::Board(const std::string &fileName, const unsigned int dimension)
    : dimension(dimension)
	, id(staticID)
	, level(0u)
{
	staticID++;

    if(ReadFromFile(fileName))
	{
        FindZeroTile();
		FindMovableDirections();
        boards.push_back(this);
	}
}

/**
 * @brief Board::Board
 * Constructor
 * Creates tiles according to its parent and the zero tile move
 * @param parent
 * @param direction
 */
Board::Board(const Board &parent, const Board::MoveDirectionsEnum direction)
	: id(staticID)
	, level(parent.getLevel() + 1)
{
	staticID++;

	this->tiles = parent.tiles;
	this->dimension = parent.dimension;
	this->zeroRow = parent.zeroRow;
	this->zeroColumn = parent.zeroColumn;

	FindMovableDirections();
	BranchParentDirection(direction);
	MoveToDirection(direction);
}

/**
 * @brief Board::~Board
 * Destructor
 */
Board::~Board()
{
}

/**
 * @brief Board::operator ==
 * Compares boards
 * @param other
 * @return
 */
bool Board::operator==(const Board &other)
{
	bool same = false;

	if(tiles == other.tiles)
	{
		same = true;
	}

	return same;
}

/**
 * @brief Board::ReadFromFile
 * Reads tiles from file
 * @param fileName
 * @return
 */
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

/**
 * @brief Board::FindZeroTile
 * Finds the row and cloumn position of the zero (blank) tile.
 * @return
 */
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

/**
 * @brief Board::IsSolvable
 * Finds if the 8 puzzle problem is solvable or not
 * This algorithm is belongs to Mark Ryan of THE UNIVERSITY OF BIRMINGHAM
 * https://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html
 * @return
 */
bool Board::IsSolvable()
{
	bool ret = false;
	unsigned int invertionsCount = 0;

	for(unsigned int firstTileIndex = 0; firstTileIndex < tiles.size(); firstTileIndex++)
	{
		for(unsigned int secondTileIndex = firstTileIndex + 1; secondTileIndex < tiles.size(); secondTileIndex++)
		{
			if(tiles.at(firstTileIndex) && tiles.at(secondTileIndex) &&
			   tiles.at(firstTileIndex) > tiles.at(secondTileIndex))
			{
				invertionsCount++;
			}
		}
	}

	if(invertionsCount % 2 == 0)
	{
		ret = true;
	}

	return ret;
}

/**
 * @brief Board::FindMovableDirections
 * Finds which directions zero tile can move
 */
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

/**
 * @brief Board::IsMovable
 * Finds if zero tile can move to given direction
 * @param moveDirection
 * @return
 */
bool Board::IsMovable(const Board::MoveDirectionsEnum moveDirection)
{
	unsigned int directionPos = static_cast<unsigned int>(moveDirection);
	return directions.at(directionPos);
}

/**
 * @brief Board::MoveToDirection
 * Moves zero tile to given direction
 * @param moveDirection
 * @return
 */
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

/**
 * @brief Board::BranchParentDirection
 * Block zero tile move direction where it comes from
 * @param moveDirection
 */
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

/**
 * @brief Board::IsBoardExist
 * Controls if the same board processed before
 * @param board
 * @return
 */
bool Board::IsBoardExist(const Board &board)
{
	bool ret = false;

	for(const auto boardI: boards)
	{
		if(*boardI == board)
		{
			ret = true;
			break;
		}
	}

	return ret;
}

/**
 * @brief Board::IsGoal
 * Controls if solution is found
 * @return
 */
bool Board::IsGoal()
{
	bool ret = false;

	if(tiles == goal)
	{
		ret = true;
	}

	return ret;
}

/**
 * @brief Board::DepthFirstSearch
 * Depth First Seach Algorithm
 */
void Board::DepthFirstSearch()
{
    if(!finished)
    {
        for(unsigned int direction = Board::MoveDirection_right; direction < Board::MoveDirectionCount; direction++)
        {
            if(IsMovable(static_cast<MoveDirectionsEnum>(direction)))
            {
                Board* child = new Board(*this, static_cast<MoveDirectionsEnum>(direction));
                if(child->IsGoal())
                {
                    boards.push_back(child);
                    finished = true;
                    std::cout << std::endl << "Solution Found! (" << boards.size() - 1 << " moves)" << std::endl;
                    printSolution();
                    break;
                }
                else if(IsBoardExist(*child))
                {
                    delete child;
                    continue;
                }
                else if(child->level == Board::MAX_MOVE_COUNT)
                {
                    /* Limit depth of the algorithm.  */
                    /* Referance: Complete Solution of the Eight-Puzzle and the Benefit of Node Ordering in IDA* by Alexander Reinefeld */
                    delete child;
                    break;
                }
                else
                {
                    boards.push_back(child);
                    child->DepthFirstSearch();
                }

                boards.pop_back();
                delete child;
            }
        }
    }
}

unsigned int Board::GetTile(const unsigned int row, const unsigned int column) const
{
    return tiles.at(row * dimension + column);
}

void Board::SetTile(const unsigned int row, const unsigned int column, const unsigned int value)
{
	tiles[row * dimension + column] = value;
}

unsigned int Board::getID() const
{
	return id;
}

void Board::print() const
{
    for(unsigned int rowIndex = 0; rowIndex < dimension; rowIndex++)
    {
        for(unsigned int columnIndex = 0; columnIndex < dimension; columnIndex++)
        {
            std::cout << GetTile(rowIndex, columnIndex) << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void Board::printSolution() const
{
    for(const auto boardI: boards)
    {
        boardI->print();
    }
}

bool Board::getFinished()
{
    return finished;
}

unsigned int Board::getLevel() const
{
    return level;
}

unsigned int Board::getZeroColumn() const
{
	return zeroColumn;
}

unsigned int Board::getZeroRow() const
{
	return zeroRow;
}
