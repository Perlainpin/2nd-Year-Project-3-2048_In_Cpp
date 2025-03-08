#include "Grid.h"
#include "Box.h"

#include <iostream>
#include <string>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


Grid::Grid() 
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			array.push_back(Box(0, "box", 0, 0, j, i));
		}
	}

	playing = true;
	score = 0;
	oldScore = 0;
	stacker = Stacker();
	directionArray = {"up","down","left","right"};

	srand(time(NULL));
};

void Grid::CreateNumber(bool isFirst)
{
	bool placing = false;

	for (int i = 0; i < 16; i++) {
		if (array[i].box_value == 0) {
			placing = true;
		}
	}

	// random spawn of 2 or 4 in game
	int rng = rand() % 16;

	if (isFirst)
	{
		array[rng].box_value = 2;
	} 
	else 
	{
		while (placing) {
			if (array[rng].box_value == 0) {

				if (rand() % 10 == 9)
				{
					array[rng].box_value = 4; 
				}
				else {
					array[rng].box_value = 2;
				}
				placing = false;
			}
			else {
				rng = rand() % 16;
			}
		}
	}

	//calculation of the score
	oldScore = score;

	for (int i = 0; i < 16; i++) {

		score += (array[i].box_value);

	}

	score -= oldScore;
}

bool Grid::Win()
{
	for (int i = 0; i < 16; i++) {
		if (array[i].box_value == 2048) {
			cout << "you win" << endl;

			return false;
		}
	}

	return true;
};

