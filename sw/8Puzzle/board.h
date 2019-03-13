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
    const unsigned int ZERO_TILE = 0u;

public:
    Board(const std::string& fileName, const unsigned int dimension);
    virtual ~Board();

    bool ReadFromFile(const std::string& fileName);
    bool FindZeroTile();

    unsigned int GetTile(const unsigned int row, const unsigned int column) const;
    void SetTile(const unsigned int row, const unsigned int column, const unsigned int value);

    void print() const;

private:
    Tiles tiles;
    unsigned int dimension; /* Row and column size */
    unsigned int x; /* Blank (zero) tile position X */
    unsigned int y; /* Blank (zero) tile position Y */
};

#endif // BOARD_H
