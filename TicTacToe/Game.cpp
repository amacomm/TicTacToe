#include "Game.h"

bool Game::CheckEnd() {
	TypeField con = board->CheckWinner();
	bool full = board->CheckFull();
	if (con == TypeField::Empty && full)
	{
		End(EndGame::Draw);
		return true;
	}
	else if (con == TypeField::Cross)
	{
		End(EndGame::WinnerOne);
		return true;
	}
	else if (con == TypeField::Circle)
	{
		End(EndGame::WinnerTwo);
		return true;
	}
	return false;
}

void Game::End(EndGame res) {
	board->Show(-1,-1);
	if (res == EndGame::WinnerOne)	std::cout << "Player one is win!" << std::endl;
	if (res == EndGame::WinnerTwo)	std::cout << "Player two is win!" << std::endl;
	if (res == EndGame::Draw)	std::cout << "Drow, play again." << std::endl;
	std::cout << "Game is end." << std::endl;
}

Game::Game(int gameSize) {
	playerOne = new Player(TypePlayer::Cross);
	playerTwo = new Player(TypePlayer::Circle);
	this->gameSize = gameSize;
	board = new Board(gameSize);
}

Game::Game() {
	playerOne = new Player(TypePlayer::Cross);
	playerTwo = new Player(TypePlayer::Circle);
	this->gameSize = 3;
	board = new Board(this->gameSize);
}

Game::~Game() {
	delete playerOne;
	delete playerTwo;
	delete board;
}

void Game::Start(){
	std::cout << "Game is start." << std::endl;
	while (true) {
		playerOne->MakeMove(board);
		if (CheckEnd())
			break;
		playerTwo->MakeMove(board);
		if (CheckEnd())
			break;
	}
} 