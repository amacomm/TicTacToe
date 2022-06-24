#pragma once
#include "IGUI.h"
#include <iostream>

class GUI :public IGUI {
public:
	void ShowGame(TypeField* board, int boardSize, int k, int t) override;
};