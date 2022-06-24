#pragma once
#include "EnumClass.h"

__interface IGUI {
	virtual void ShowGame(TypeField* board, int boardSize, int k, int t) = 0;
};