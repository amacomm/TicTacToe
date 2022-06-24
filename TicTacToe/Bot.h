#pragma once
#include "IPlayer.h"

class Bot :public IPlayer {
	TypePlayer type;
public:
	Bot(TypePlayer type);
	~Bot() {};
	void MakeMove(IBoard* board) override;
};