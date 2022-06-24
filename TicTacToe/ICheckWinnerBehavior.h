#pragma once
#include "EnumClass.h"

__interface ICheckWinnerBehavior {
public:
	virtual TypeField CheckWinner() = 0;
};