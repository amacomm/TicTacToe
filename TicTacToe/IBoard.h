#pragma once
#include "EnumClass.h"

__interface IBoard {
	virtual void FieldChange(TypePlayer type, int i, int j) = 0;
	virtual TypeField CheckWinner() = 0;
	virtual bool CheckFull() = 0;
	virtual void Show(int i, int j) = 0;
	virtual TypeField* ShowField() = 0;
	virtual int ShowSize() = 0;
};