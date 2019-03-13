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

#include <iostream>
#include <string>
#include <vector>

class Board
{
    typedef std::vector<unsigned int> Tiles;
	typedef std::vector<bool> MovableDirections;

    const unsigned int ZERO_TILE = 0u;

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

    bool ReadFromFile(const std::string& fileName);
    bool FindZeroTile();

	void FindMovableDirections();
	bool IsMovable(const MoveDirectionsEnum moveDirection);
	bool MoveToDirection(const MoveDirectionsEnum moveDirection);
	void BranchParentDirection(const MoveDirectionsEnum moveDirection);

	bool IsGoal();

    unsigned int GetTile(const unsigned int row, const unsigned int column) const;
    void SetTile(const unsigned int row, const unsigned int column, const unsigned int value);

    void print() const;

private:
    Tiles tiles;
	MovableDirections directions;
    unsigned int dimension; /* Row and column size */
	unsigned int zeroRow; /* Blank (zero) tile position X */
	unsigned int zeroColumn; /* Blank (zero) tile position Y */
};

#endif // BOARD_H
