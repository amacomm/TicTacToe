#include <iostream>
#include "Board.h"

Board::Board(int boardSize) {
	this->boardSize = boardSize;
	board = new TypeField[boardSize * boardSize];
	for (int i = 0; i < boardSize * boardSize; i++)
	{
		board[i] = TypeField::Empty;
	}
}

Board::~Board() {
	delete board;
}

//void Board::FieldChange(TypePlayer type) {
//	int i, j;
//	while (true) {
//		std::cin >> i >> j;
//		if (i < boardSize || j < boardSize) {
//			if (board[i * boardSize + j] == TypeField::Empty) {
//				board[i * boardSize + j] = (TypeField)type;
//				break;
//			}
//		}
//		std::cout << "Your move is bad, repeat" << std::endl;
//	}
//}

void Board::FieldChange(TypePlayer type,int i, int j) {
	board[i * boardSize + j] = (TypeField)type;
}

TypeField Board::CheckWindow(int size, int offsetI, int offsetJ) {
	bool toright, toleft, cols, rows;
	for (TypeField type = (TypeField)1; (int)type < 3; type = (TypeField)((int)type + 1)) {
		toright = true;
		toleft = true;
		for (int i = 0; i < size; i++) {
			toright &= (board[(i+offsetI) * boardSize + (i+offsetI)] == type);
			toleft &= (board[(size-1 - i + offsetI) * boardSize + (i + offsetI)] == type);
			cols = true;
			rows = true;
			for (int j = 0; j < size; j++)
			{
				cols &= (board[(i + offsetI) * boardSize + (j + offsetJ)] == type);
				rows &= (board[(j + offsetJ) * boardSize + (i + offsetI)] == type);
			}
			if (cols || rows) return type;
		}
		if (toright || toleft) return type;
	}
	return TypeField::Empty;
}

TypeField Board::CheckWinner() {
	int size = 5;
	TypeField res;
	for (int i = 0; i <= boardSize - size; i++) {
		for (int j = 0; j <= boardSize - size; j++) {
			res = CheckWindow(size, i, j);
			if (res != TypeField::Empty)return res;
		}
	}
	return TypeField::Empty;
}

bool Board::CheckFull() {
	for (int i = 0; i < boardSize*boardSize; i++)
	{
		if (board[i] == TypeField::Empty) return false;
	}
	return true;
}

TypeField* Board::ShowField() {
	TypeField* answer = new TypeField[boardSize * boardSize];
	for (int i = 0; i < boardSize * boardSize; i++) answer[i] = board[i];
	return answer;
}

void Board::Show(int i, int j) {
	IGUI* gui = new GUI;
	gui->ShowGame(board, boardSize, i, j);
	//delete gui;
}
int Board::ShowSize() {
	return boardSize;
}