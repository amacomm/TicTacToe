#include "Bot.h"
#include<iostream>
#include <conio.h>
#include <ctime>

Bot::Bot(TypePlayer type) {
	this->type = type;
}

double countWeight(TypePlayer type, TypeField* board, int boardSize, int i);

void Bot::MakeMove(IBoard* board) {
	int boardSize = board->ShowSize();
	TypeField* boardSeems = board->ShowField();
	double* Matrix = new double[boardSize * boardSize];
	double maximum = -1000;
	int coordinates = 0;
	srand(time(0));

	for (int i = 0; i < boardSize * boardSize; i++) {
		boardSeems[i] != TypeField::Empty ? Matrix[i] = -20000 : Matrix[i] = countWeight(type, boardSeems, boardSize, i);
		double a = Matrix[i];
		if (Matrix[i] > maximum) { 
			maximum = Matrix[i];
			coordinates = i; 
		}
	}

	//delete[] Matrix;

	int i = coordinates / boardSize;
	int j = coordinates % boardSize;
	board->FieldChange(type, i, j);
	board->Show(i, j);
	/*int code;
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
	}*/
}

class Atack {
	double Weights(int power, int potential) {
		switch (potential)
		{
		case 0:
			if (power == 5)
				return 200;
			else return 0;
		case 1:
			switch (power)
			{
			case 1:
				return 0.1;
			case 2:
				return 2;
			case 3:
				return 4;
			case 4:
				return 6;
			case 5:
				return 200;
			}
		case 2:
			switch (power)
			{
			case 1:
				return 0.25;
			case 2:
				return 5;
			case 3:
				return 7;
			case 4:
				return 100;
			case 5:
				return 200;
			}
		default:
			return 0;
		}
	}
public:
	int cap;
	int pot;
	int div;

	Atack(int cap = 0, int pot = 0, int div = 1) {
		this->cap = cap;
		this->pot = pot;
		this->div = div;
	}

	double countWeights() {
		return Weights(cap, pot) / div;
	}
};

class checkLine {
	TypePlayer type;
	Atack* curAtack;
	int iter;
	bool checkEdge;
	TypeField* board;
	int boardSize;

	void push(Atack atack) {
		Atack* newAtack = new Atack[checkSize++];
		for (int i = 0; i < checkSize-1; i++)
		{
			newAtack[i] = atacks[i];
		}
		newAtack[checkSize - 1] = atack;
		//delete[] atacks;
		atacks = newAtack;
	}

	bool checkCell(int x, int y) {
		bool empty = (x>=boardSize||x<0|| y>=boardSize || y < 0);
		TypeField type;
		if (!empty) type = board[x * boardSize + y];
		else type = TypeField::Empty;

		if (iter == 4 && (TypePlayer)type == this->type)
			checkEdge = true;
		else if (iter == 5) {
			if (checkEdge) {
				if ((TypePlayer)type == this->type || type == TypeField::Empty)
					curAtack->pot++;
				push(curAtack[0]);
			}
			return false;
		}
		iter++;

		if (type == TypeField::Circle || type == TypeField::Cross) {
			if ((TypePlayer)type != this->type) {
			push(curAtack[0]);
			return true;
			}
			else {
				curAtack->cap++;
				attackPlace++;
			}
		}
		else if (empty) {
			push(curAtack[0]);
			return true;
		}
		else {
			if (curAtack->cap) {
				curAtack->pot++;
				push(curAtack[0]);
				curAtack = new Atack;
				curAtack->pot++;
			}
			curAtack->div++;
			attackPlace++;
		}
		return false;
	}

	void turnAround() {
		iter = 1;
		checkEdge = false;
		curAtack[0] = atacks[0];
		Atack* atacks2 = new Atack[4];
		for (int i = 1; i < checkSize; i++)
			atacks2[i - 1] = atacks[i];
		//delete[] atacks;
		atacks = atacks2;
	}

public:
	int attackPlace;
	Atack* atacks;
	int checkSize;

	checkLine(TypePlayer type, TypeField* board, int boardSize){
		this->type = type;
		this->atacks = new Atack[1];
		this->curAtack = new Atack;
		this->iter = 1;
		this->checkEdge = false;
		this->attackPlace = 1;
		this->board = board;
		this->boardSize=boardSize;
		this->checkSize = 0;
	}

	~checkLine() {
		//delete[] atacks;
		//delete curAtack;
	}

	Atack* getAtacks(int i, int j, int dx, int dy) {
		for (int x = i - dx, y = j - dy; sqrt(abs(x - i)^2+  abs(y - j)^2) < 6; x -= dx, y -= dy)
			if (checkCell(x, y))
				break;
		turnAround();
		for (int x = i + dx, y = j + dy; sqrt(abs(x - i) ^ 2 + abs(y - j) ^ 2) < 6; x += dx, y += dy)
			if (checkCell(x, y))
				break;
		return atacks;
	}
};

Atack* filtterAtacks(checkLine* check, int& countAtack) {
	Atack* res = new Atack[1];
	int resSize = 0;
	if (check->attackPlace > 4) {
		Atack a;
		for (int i = 0; i < check->checkSize; i++) {
			a = (check->atacks)[i];
			if (a.cap && a.pot || a.cap > 4) {
				Atack* res2 = new Atack[resSize++];
				for (int j = 0; j < resSize-1; j++)
					res2[j] = res[j];
				res2[resSize] = a;
				//delete[] res;
				res = res2;
			}
		}
	}
	//check->atacks = res;
	//check->checkSize = resSize;
	countAtack = resSize;
	return res;
}

Atack* getAtacksLine(int i, int j, TypePlayer type, int dx, int dy, TypeField* board, int boardSize, int& countAtack) {
	checkLine* check = new checkLine(type, board, boardSize);
	check->getAtacks(i, j, dx, dy);
	Atack* res = filtterAtacks(check, countAtack);
	//delete[] check;
	return res;
}

Atack** getAllAttacks(int i, int j, TypePlayer type, TypeField* board, int boardSize, int* countAtack) {
	Atack** atacks= new Atack*[4];
	atacks[0] = getAtacksLine(i, j, type, 1,  0, board, boardSize, countAtack[0]);
	atacks[1] = getAtacksLine(i, j, type, 0,  1, board, boardSize, countAtack[1]);
	atacks[2] = getAtacksLine(i, j, type, 1, -1, board, boardSize, countAtack[2]);
	atacks[3] = getAtacksLine(i, j, type, 1,  1, board, boardSize, countAtack[3]);

	return atacks;
}

bool isBreackPoint(Atack* check, int checkSize) {
	if (!check || !checkSize)
		return false;
	Atack* atack = new Atack;
	for (int i = 0; i < checkSize; i++)
		if (check[i].div == 1)
			atack[0] = check[i];

	if (atack->cap > 3) return true;
	if (atack->pot == 2 && atack->cap > 2) return true;
	bool res = false;
	int score;
	for (int i = 0; i < checkSize; i++) {
		score = atack->cap;
		if (check[i].div == 2) {
			if (atack->pot == 2 && check[i].pot == 2) score++;
			if (score + check[i].cap > 3) {
				res = true;
				return res;
			}
		}
	}
	return res;
}

double count(Atack** atacks, TypePlayer type, int* countAtack) {
	double weight=0;
	double breakPoint = 0;
	for (int i = 0; i <4; i++)
	{
		if (isBreackPoint(atacks[i], countAtack[i])) {
			if (++breakPoint == 2) {
				weight += 100;
				return weight;
			}
		}
		for (int j = 0; j < countAtack[i]; j++)
		{
			if (atacks[i][j].cap > 5)
				atacks[i][j].cap = 5;
			if (atacks[i][j].cap == 5 && type == TypePlayer::Circle)
				weight += 100;
			weight += atacks[i][j].countWeights();
		}
	}
	return weight;
}

double countWeight(TypePlayer type, TypeField* board, int boardSize, int i) {
	int j = i % boardSize;
	i /= boardSize;
	int* countAtack=new int[4];
	Atack** atacks = getAllAttacks(i, j, type, board, boardSize, countAtack);
	double sum = 0;
	sum += count(atacks, type, countAtack);
	//for (int i = 0; i < 4; i++)
	//	delete[] atacks[i];
	//delete[] atacks;
	//delete[] countAtack;
	return sum;
}