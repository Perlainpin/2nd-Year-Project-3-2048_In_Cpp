#pragma once

#include "stacker.h"
#include "Test.h"

#include <vector>

class TestManager {
public:
	vector<Test> testList;
	Stacker stacker;

	TestManager();

	bool TryTests();
};