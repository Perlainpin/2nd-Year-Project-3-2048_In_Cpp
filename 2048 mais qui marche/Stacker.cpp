#include "Stacker.h"
#include "Box.h"

#include <iostream>


Stacker::Stacker() 
{
	storage = {};

	for (int u = 0; u < 4; u++)
	{
		storage.push_back(Box());
	}
	direction = 0; //	0 = up		1 = down	2 = left	3 = right
}

void Stacker::Retrieve(int slot, vector<Box>& array) //updates the stacker's storage with the boxes from the row that will be processed, pulled from a specified array
{
	for (int boxes = 0; boxes < 4; boxes++) {
		if (direction == 0) {//up
			storage[boxes] = array[boxes * 4 + slot];
		}
		else if (direction == 1) {//down
			storage[boxes] = array[(12 - boxes * 4) + slot];
		}
		else if (direction == 2) {//left
			storage[boxes] = array[boxes + slot * 4];
		}
		else if (direction == 3) {//right
			storage[boxes] = array[3 - boxes + slot * 4];
		}
	}
}

void Stacker::Squish() 
{

	//checking for a merge on each box of the storage
	for (int i = 0; i < 3; i++) {
		if (storage[i].box_value == 0)
			continue;

		for (int j = i + 1; j < 4; j++) {
			if (storage[j].box_value == 0)
				continue;

			if (storage[j].box_value == storage[i].box_value) {
				storage[j].box_value = 0;
				storage[i].box_value = storage[i].box_value * 2;
			}

			break;
		}
	}
	
	//moving all the 0's to the back of the line
	for (int i = 0; i < 3; i++) {
		if (storage[i].box_value != 0)
			continue;

		for (int j = i + 1; j < 4; j++) {
			if (storage[j].box_value == 0)
				continue;

			storage[i].box_value = storage[j].box_value;
			storage[j].box_value = 0;

			break;
		}
	}
}

bool Stacker::Playable() //checks if there are any available moves on the current studied row
{
	for (int i = 0; i < 3; i++) {
		if (storage[i].box_value == 0)
			return true;

		for (int j = i + 1; j < 4; j++) {
			if (storage[j].box_value == storage[i].box_value || storage[j].box_value == 0)
				return true;

			break;
		}
	}
	return false;
}

void Stacker::Send(int slot, vector<Box>& array) //returns the new updates boxes to the original array
{
	for (int boxes = 0; boxes < 4; boxes++) {
		if (direction == 0) {//up
			array[boxes * 4 + slot] = storage[boxes];
		}
		else if (direction == 1) {//down
			array[(12 - boxes * 4) + slot] = storage[boxes];
		}
		else if (direction == 2) {//left
			array[boxes + slot * 4] = storage[boxes];
		}
		else if (direction == 3) {//right
			array[3 - boxes + slot * 4] = storage[boxes];
		}
	}
}

bool Stacker::OverallCheck(vector<Box>& array) //checks if there is at least a single possible move in an entire array
{
	for (direction = 0; direction < 4; direction++) {
		for (int slot = 0; slot < 4; slot++) {
			Retrieve(slot, array);
			if (Playable()) {
				return true;
			}
		}
	}
	cout << "you lose!" << endl;
	return false;
}

void Stacker::Launch(int newDirection, vector<Box>& array) //runs a procedure of pulling, modifying and updating each row from a selected direction 
{
	direction = newDirection;
	for (int slot = 0; slot < 4; slot++) {
		Retrieve(slot, array);
		Squish();
		Send(slot, array);
	}
}