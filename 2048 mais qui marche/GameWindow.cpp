#include "GameWindow.h"
#include "GameObject.h"
#include "Box.h"
#include "Grid.h"

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>
#include <SDL_ttf.h>

using namespace std;

GameWindow::GameWindow()
{
	// variable for the sdl window
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM); 
	windowSize = { DM.w, DM.h }; // {largeur, hauteur}
	window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize[0], windowSize[1], SDL_WINDOW_FULLSCREEN_DESKTOP);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetWindowTitle(window, "2048");

	// variable for the font use by ttf
	color = { 255, 255,255 };
	font = TTF_OpenFont("font/KrabbyPatty.ttf", 120);
	
	objectList = {
		new GameObject("mainBG", windowSize[1], windowSize[1], windowSize[0] / 2 - windowSize[1] / 2, 0),
		new GameObject("scoreText", ((windowSize[0]-windowSize[1])/20) * 8, windowSize[1] / 8, (windowSize[0] - windowSize[1]) / 20, 0),
		new GameObject("score", ((windowSize[0] - windowSize[1]) / 20) * 8, windowSize[1] / 8, (windowSize[0] - windowSize[1]) / 20, windowSize[1] / 8)
	};
};

void GameWindow::LoadTextures() {
	textureList["0"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/fond-case.png"));
	textureList["2"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/2.png"));
	textureList["4"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/4.png"));
	textureList["8"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/8.png"));
	textureList["16"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/16.png"));
	textureList["32"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/32.png"));
	textureList["64"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/64.png"));
	textureList["128"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/128.png"));
	textureList["256"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/256.png"));
	textureList["512"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/512.png"));
	textureList["1024"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/1024.png"));
	textureList["2048"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/2048.png"));
	textureList["mainBG"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/fond-jeu.png"));
	textureList["secondaryBG"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/fond-side.jpg"));
	textureList["lossTransition"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/loss-transition.png"));
	textureList["loss"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/Davy-Jones-skeleton.png"));
	textureList["winTransition"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/winTransition.png"));
	textureList["win"] = SDL_CreateTextureFromSurface(renderer, IMG_Load("img/win.png"));
	textureList["scoreText"] = SDL_CreateTextureFromSurface(renderer, TTF_RenderUTF8_Blended(font, "Score:", color));
}

void GameWindow::Score(){
	// this parts need to be load every time a move is down 
	
	// transform the int from grid.score into char* 
	char str[4];
	snprintf(str, sizeof(str), "%d", grid.score);

	// set this char* into the texturelist
	textureList["score"] = SDL_CreateTextureFromSurface(renderer, TTF_RenderUTF8_Blended(font, str, color));
}

void GameWindow::ScreenDisplay() {

	SDL_RenderCopy(renderer, textureList["secondaryBG"], NULL, NULL);

	SDL_Rect rect;

	// the variable set in objectlist are use as variable for the rect of principal textures
	for (int i = 0; i < objectList.size(); i++) {

		rect.w = objectList[i]->width;
		rect.h = objectList[i]->height;
		rect.x = objectList[i]->positionX;
		rect.y = objectList[i]->positionY;
		SDL_RenderCopy(renderer, textureList[objectList[i]->objectName], NULL, &rect);
	}

	SDL_RenderPresent(renderer);

	for (int i = 0; i < 16; i++) {
		grid.array[i].BoxDisplay(windowSize[1], windowSize[0], textureList, renderer);

	}
}

void GameWindow::WindowWin() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, textureList["winTransition"], NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
	SDL_RenderCopy(renderer, textureList["win"], NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_Delay(4000);
}

void GameWindow::WindowLoss() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, textureList["lossTransition"], NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
	SDL_RenderCopy(renderer, textureList["loss"], NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_Delay(4000);
}

void GameWindow::WindowMovement() {
	SDL_Event event;
	bool choosing= true;
	while (SDL_WaitEvent(&event) && choosing)
	{
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_UP) {
				grid.stacker.Launch(0, grid.array);
				choosing = false;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				grid.stacker.Launch(1, grid.array);
				choosing = false;
			}
			else if (event.key.keysym.sym == SDLK_LEFT) {
				grid.stacker.Launch(2, grid.array);
				choosing = false;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				grid.stacker.Launch(3, grid.array);
				choosing = false;
			}
		}
	}
}