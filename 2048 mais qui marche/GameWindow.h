#pragma once

#include "Grid.h"

#include <vector>
#include <map>
#include <string> 
#include <SDL_ttf.h>

using namespace std;

class GameObject;
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class GameWindow
{
public:
	map<string, SDL_Texture*> textureList;
	vector<GameObject*> objectList;
	vector<int> windowSize;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Grid grid;


	TTF_Font* font;
	SDL_Color color;

	GameWindow();
	
	void ScreenDisplay();
	void LoadTextures();
	void Score();
	void WindowMovement();
	void WindowWin();
	void WindowLoss();
};
