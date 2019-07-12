#pragma once

#include <iostream>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <functional>


void exampleContainer() {
	// prerequisite
	std::vector<int> vals = std::vector<int>{ 1, 3, 2, 5, 4 };
	
	// number to look for
	const int three = 3;

	int64_t nrOfElementsFound = std::count(vals.begin(), vals.end(), three);

	// look for a number which is larger than 3

	auto isAboveThree = [](int v) { return v > 3; }; // this is where I would really use auto

	int64_t nrOfElementsAboveThreeFound = std::count_if(vals.begin(), vals.end(), isAboveThree);
}

int countValueAbove(const std::vector<int>& vals, int th) {
	auto isAbove = [th](int v) { return v > th; };

	return std::count_if(vals.begin(), vals.end(), isAbove);
}

void printValuesAboveDesiredValue(int desiredValue) {
	std::vector<int> valueList{ 1, 3, 2, 5, 4, 5, 5, 3 };

	std::cout << countValueAbove(valueList, desiredValue) << " where found that are bigger than " << desiredValue << std::endl;
}

// example of a simple button class using a lambda function

class Button {
private:
	std::function<void(void)> m_clickFunction{};

public:
	Button(std::function<void(void)> clickFunction) : m_clickFunction{ clickFunction } {}
	void onClick() const {
		m_clickFunction();
	}
};

std::vector<Button> makeButtons() {
	Button beepButton{ [beepCount = 0] () mutable {
		std::cout << "Beep: " << beepCount << "! ";
		++beepCount;
} };

	Button bopButton{ []() {
		std::cout << "Bop. ";
	} };

	Button silentButton{ []() {} };

	std::vector<Button> buttons{ beepButton, bopButton, silentButton };

	return buttons;
}

void clickButtons() {
	std::vector<Button> buttons = makeButtons();

	for (const Button& b : buttons) {
		b.onClick();
	}

	buttons.front().onClick();
}