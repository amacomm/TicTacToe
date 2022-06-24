#pragma once
#include "IBoard.h"
#include "GUI.h"
#include "CheckWinnerOne.h"

class Board: public IBoard {
	TypeField CheckWindow(int size, int offsetI, int offsetJ);
public:
	ICheckWinnerBehavior* checkWinner;
	TypeField* board;
	int boardSize;
	Board(int boardSize);
	~Board();
	void FieldChange(TypePlayer type, int i, int j) override;
	TypeField CheckWinner() override;
	bool CheckFull() override;
	void Show(int i, int j) override;
	TypeField* ShowField() override;
	int ShowSize() override;
};

class CheckWinnerOne :public ICheckWinnerBehavior {
public:
	TypeField CheckWinner() override {

	}
};