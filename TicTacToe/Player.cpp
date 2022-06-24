#include "Player.h"
#include<iostream>
#include <conio.h>

Player::Player(TypePlayer type) {
	this->type = type;
}

void Player::MakeMove(IBoard* board) {
	int boardSize = board->ShowSize();
	TypeField* boardSeems = board->ShowField();
	int i = 1, j = 1;
	int code;
	while (true) {
		board->Show(i, j);
		std::cout << "Player " << Char[(int)type] << " make move" << std::endl;
		code = _getch();
		switch (code)
		{
		case 75:
			(j > 0 && j < boardSize) ? j-- : 0;
			break;
		case 77:
			(j >= 0 && j < boardSize - 1) ? j++ : 0;
			break;
		case 72:
			(i > 0 && i < boardSize) ? i-- : 0;
			break;
		case 80:
			(i >= 0 && i < boardSize - 1) ? i++ : 0;
			break;
		case 13:
			if (boardSeems[i * boardSize + j] == TypeField::Empty) {
				board->FieldChange(type, i, j);
				board->Show(i, j);
				return;
			}
			break;
		}
	}
}