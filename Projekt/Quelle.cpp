#include <iostream>
#include "tetris.h"
#include "olcCOnsoleGameEngine.h"
using namespace std;

int main()
{
	Tetris game;
	game.ConstructConsole(80, 50, 16, 16); //W,H,Pixels
	game.Start();

	return 0;
}