#pragma once
#include "IGame.h"
#include "Player.h"
#include "Board.h"
#include "Bot.h"

class Game : public virtual IGame {
	IPlayer* playerOne;
	IPlayer* playerTwo;
	IBoard* board;
	int gameSize;
	bool CheckEnd();
	void End(EndGame res) override;
public:
	Game();
	Game(int gameSize);
	~Game();

	void Start() override;
};