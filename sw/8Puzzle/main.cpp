/*
 * 8Puzzle: Software for solving well known 8 puzzle problem
 *
 * BLG 521E Advanced Artificial Intelligence HW#1
 *
 * Copyright (C)  Mehmet AKTAS 0504181576 13.03.2019
 *
 */

#include <QCoreApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Game game;

    return a.exec();
}
