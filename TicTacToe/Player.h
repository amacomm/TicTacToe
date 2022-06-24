#pragma once
#include "IPlayer.h"

class Player : public virtual IPlayer {
	TypePlayer type;
public:
	Player(TypePlayer type);
	~Player() {};
	void MakeMove(IBoard* board) override;
};