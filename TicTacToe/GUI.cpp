#include "GUI.h"

void GUI::ShowGame(TypeField* board, int boardSize, int k, int t) {
	system("cls");
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (i == k && j == t) std::cout << '|' << '+';
			else std::cout << '|' << Char[(int)board[i * boardSize + j]];
		}
		std::cout << '|' << std::endl;
	}
}