/*
 * 8Puzzle: Software for solving well known 8 puzzle problem
 *
 * BLG 521E Advanced Artificial Intelligence HW#1
 *
 * Copyright (C)  Mehmet AKTAS 0504181576 13.03.2019
 *
 */

#include "game.h"
#include <QElapsedTimer>

Game::Game()
{
    std::cout << "Game Started!" << std::endl;

    /* For calculating elapsed time */
    QElapsedTimer elapsedTimer;
    elapsedTimer.start();

	DepthFirstSearch();

    std::cout << "Game Finished! (" << static_cast<float>(elapsedTimer.elapsed() / 1000) << " seconds)" << std::endl;
}

Game::~Game()
{
}

void Game::DepthFirstSearch()
{
    /* Initial state is created from given file */
	Board* root = new Board(":/root.txt", EIGHT_PUZZLE);

    std::cout << "Initial state:" << std::endl;
    root->print();

	if(root->IsSolvable())
	{
        std::cout << "This puzzle can be solved!" << std::endl;
		root->DepthFirstSearch();
	}
	else
	{
		std::cout << "This puzzle is not solvable!" << std::endl;
	}

	delete root;
}

