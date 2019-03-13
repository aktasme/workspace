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
}
