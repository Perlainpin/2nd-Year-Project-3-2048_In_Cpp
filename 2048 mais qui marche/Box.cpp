#include "Box.h"

#include <string> 
#include <SDL.h>
#include <SDL_image.h>
using namespace std;


Box::Box(int value, const char* name, int sizeW, int sizeH, int posX, int posY) :GameObject(name, sizeW, sizeH, posX, posY)
{
	box_value = value;
};

Box::Box(int value) :GameObject("box", 0, 0, 0, 0)
{
	box_value = value;
};

Box::Box() :Box(0)
{
	box_value = 0;
};

void Box::BoxDisplay(int screenH, int screenW, map<string, SDL_Texture*> textureList, SDL_Renderer* renderer)
{

	SDL_Rect dstrect;

	// each box have an unique rect that change of position when the box position change

	dstrect.x = screenW / 2 - screenH / 2 + (screenH / 4) * positionX + (screenH / 80);
	dstrect.y = (screenH / 4) * positionY + (screenH / 80);
	dstrect.w = (screenH / 4) - (screenH / 40);
	dstrect.h = (screenH / 4) - (screenH / 40);

	SDL_RenderCopy(renderer, textureList[to_string(box_value)], NULL, &dstrect);

	SDL_RenderPresent(renderer);
}