#pragma once

class GameObject
{
public:
	
	const char* objectName;
	int width;
	int height;
	int positionX;
	int positionY;

	GameObject(const char* name, int width, int height, int positionX, int positionY);
};