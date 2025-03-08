
#include "Grid.h"
#include "TestManager.h"
#include "GameWindow.h"

#include <iostream>
#include <vector>
#include <SDL.h>
#include <cstdlib>
#include <SDL_ttf.h>

using namespace std;

void Test() //runs a series of tests checking major functions are operational
{
	TestManager tester;
	tester.TryTests();
}

void Play() //runs the 2048 game
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	TTF_Init();

	GameWindow game = GameWindow();

	game.grid.CreateNumber(true);
	game.LoadTextures();

	while (game.grid.playing == true)
	{
		game.grid.CreateNumber(false);
	
		game.Score();
		game.ScreenDisplay();
		game.WindowMovement();

		system("cls");

		if (not game.grid.stacker.OverallCheck(game.grid.array)) {
			game.ScreenDisplay();
			SDL_Delay(2500);
			game.WindowLoss();
			break;

		}else if(not (game.grid.Win())) {
			game.ScreenDisplay();
			SDL_Delay(3000);
			game.WindowWin();
			break;
		}
	}

	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char** argv)
{
	Test();
	Play();
	
	return 0;
}