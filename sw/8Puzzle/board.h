/*
 * 8Puzzle: Software for solving well known 8 puzzle problem
 *
 * BLG 521E Advanced Artificial Intelligence HW#1
 *
 * Copyright (C)  Mehmet AKTAS 0504181576 13.03.2019
 *
 */

#ifndef BOARD_H
#define BOARD_H

#include "definitions.h"

class Board
{
    typedef std::vector<unsigned int> Tiles;
    typedef std::vector<bool> MovableDirections;
    typedef std::vector<Board*> Boards;

    const unsigned int ZERO_TILE = 0u;

    /* Complete Solution of the Eight-Puzzle and the Benefit of Node Ordering in IDA* by Alexander Reinefeld */
    const unsigned int MAX_MOVE_COUNT = 31;

public:
	enum MoveDirectionsEnum
	{
		MoveDirection_right = 0,
		MoveDirection_left = 1,
		MoveDirection_up = 2,
		MoveDirection_down = 3,
		MoveDirectionCount
	};

    Board(const std::string& fileName, const unsigned int dimension);
	Board(const Board& parent, const MoveDirectionsEnum direction);
    virtual ~Board();

	bool operator==(const Board& other);

    bool ReadFromFile(const std::string& fileName);
    bool FindZeroTile();
	bool IsSolvable();

	void FindMovableDirections();
	bool IsMovable(const MoveDirectionsEnum moveDirection);
	bool MoveToDirection(const MoveDirectionsEnum moveDirection);
	void BranchParentDirection(const MoveDirectionsEnum moveDirection);
	bool IsBoardExist(const Board& board);
	bool IsGoal();

	void DepthFirstSearch();

    unsigned int GetTile(const unsigned int row, const unsigned int column) const;
    void SetTile(const unsigned int row, const unsigned int column, const unsigned int value);

	unsigned int getID() const;
	unsigned int getZeroRow() const;
	unsigned int getZeroColumn() const;
    unsigned int getLevel() const;
    static bool getFinished();

    void print() const;
    void printSolution() const;

private:
    Tiles tiles; /* The order of tiles */
    MovableDirections directions; /* Directions that zero tile can move */
    unsigned int dimension; /* Row and column size */
	unsigned int zeroRow; /* Blank (zero) tile position X */
	unsigned int zeroColumn; /* Blank (zero) tile position Y */

    unsigned int id; /* Increasing identifier for all created boards */
    static unsigned int staticID; /* To assing id */
    unsigned int level; /* Level of the node */
    static bool finished; /* True if the algoithm finds the solution */
    static Boards boards; /* The boards through route. Branch-and-bound method is used. */
};

#endif // BOARD_H
