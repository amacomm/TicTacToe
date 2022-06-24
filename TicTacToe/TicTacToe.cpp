#include <iostream>
#include "Game.h"

int main()
{
    IGame* game = new Game(10);
    game->Start();
    //delete game;
    return 0;
}