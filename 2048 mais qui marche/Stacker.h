#pragma once

#include <vector>

class Box;

using namespace std;

class Stacker
{
public:
	vector<Box> storage;
	int direction;//to lower memory consumption, each direction is represented by a single digit

	Stacker();

	void Retrieve(int slot, vector<Box>& array);
	void Squish();
	void Send(int slot, vector<Box>& array);
	void Launch(int direction, vector<Box>& array);

	bool Playable();
	bool OverallCheck(vector<Box>& array);
};