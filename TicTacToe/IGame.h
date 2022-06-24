#pragma once
#include <iostream>
#include "EnumClass.h"

__interface IGame {
	virtual void Start() = 0;
	virtual void End(EndGame res) = 0;
};