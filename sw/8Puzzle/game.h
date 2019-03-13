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
