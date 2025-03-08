#include "GameObject.h"


GameObject::GameObject(const char* name, int sizeW, int sizeH, int posX, int posY)
{
	objectName = name;
	width = sizeW;
	height = sizeH;
	positionX = posX;
	positionY = posY;
};