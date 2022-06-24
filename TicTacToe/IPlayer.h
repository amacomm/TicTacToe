#pragma once
#include "IBoard.h"

__interface IPlayer {
	virtual void MakeMove(IBoard* board) = 0;
};