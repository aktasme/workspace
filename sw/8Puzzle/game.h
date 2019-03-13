/*
 * 8Puzzle: Software for solving well known 8 puzzle problem
 *
 * BLG 521E Advanced Artificial Intelligence HW#1
 *
 * Copyright (C)  Mehmet AKTAS 0504181576 13.03.2019
 *
 */

#ifndef GAME_H
#define GAME_H


class Game
{
    enum GameType
    {
        EIGHT_PUZZLE = 3
    };

public:
    Game();
    virtual ~Game();

    void CreateRoot();
};

#endif // GAME_H
