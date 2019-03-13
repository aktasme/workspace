/*
 * 8Puzzle: Software for solving well known 8 puzzle problem
 *
 * BLG 521E Advanced Artificial Intelligence HW#1
 *
 * Copyright (C)  Mehmet AKTAS 0504181576 13.03.2019
 *
 */

#include "game.h"
#include "board.h"

Game::Game()
{
    std::cout << "Game Started!" << std::endl;
    CreateRoot();
}

Game::~Game()
{
}

void Game::CreateRoot()
{
    Board* root = new Board(":/root.txt", EIGHT_PUZZLE);
    root->print();

	if(root->IsGoal())
		std::cout << "Goal!" << std::endl;

	root->MoveToDirection(Board::MoveDirection_right);
	root->print();

	if(root->IsGoal())
		std::cout << "Goal!" << std::endl;

}
