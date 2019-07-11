#pragma once

#include <vector>


void exampleContainer() {
	// prerequisite
	std::vector<int> vals = std::vector<int>{ 1, 3, 2, 5, 4 };
	
	// number to look for
	int three = 3;

	int nrOfElementsFound = std::count(vals.begin(), vals.end(), three);

	// look for a number which is larger than 3

	auto isAboveThree = [](int v) { return v > 3; }; // this is where I would really use auto

	int nrOfElementsAboveThreeFound = std::count(vals.begin(), vals.end(), isAboveThree);
}