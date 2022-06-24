#pragma once

enum class TypePlayer
{
	Cross = 1, Circle
};

enum class TypeField
{
	Empty, Cross, Circle
};

enum class EndGame {
	WinnerOne, WinnerTwo, Draw
};
char static Char[3] = { ' ', 'x', 'o' };
