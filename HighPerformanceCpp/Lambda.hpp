#pragma once

#include <iostream>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <functional>
#include <chrono>


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

// LAMBDA VS FUNCTION PERFORMANCE COMPARISON

double testDirectLambda() {
	auto lbd = [](int v) {
		return v * 3;
	};

	using L = decltype(lbd); // nice case for the using keyword
	std::vector<L> fs{};
	fs.resize(1'000'000, lbd);

	int res{ 0 };

	// measure time
	auto start = std::chrono::high_resolution_clock::now();

	for (const L& f : fs) {
		res = f(res);
	}

	auto end = std::chrono::high_resolution_clock::now();

	return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

double testStdFunction() {
	auto lbd = [](int v) {
		return v * 3;
	};

	using F = std::function<int(int)>;
	std::vector<F> fs{};
	fs.resize(1'000'000, lbd);

	int res{ 0 };

	// measure time
	auto start = std::chrono::high_resolution_clock::now();

	for (const F& f : fs) {
		res = f(res);
	}

	auto end = std::chrono::high_resolution_clock::now();

	return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

// Polymorphic lambda - a lambda that accepts auto types as parameters

namespace PolyLambda {

	void polymorphicLambdaExample() {
		int v{ 3 };
		auto lambda = [v](auto v0, auto v1) { return v + v0 * v1; };
	}

	class Lambda {
	private:
		int v_{};

	public:
		Lambda(int v) : v_{ v } {}

		template<typename T0, typename T1>
		auto operator()(T0 v0, T1 v1) const { return v_ + v0 * v1; }
	};



	// Reusable polymorphic lambdas

	enum class Continent { Europe, Asia, America };

	// In case we want a reusable lambda with a capture we have to wrap the capture into a function like this
	template<typename T>
	auto isSecondEqual(const T& x) {
		// a lambda capturing x is returned
		return [&x](const auto& p) { return p.second == x; };
	}

	void reusablePolymorphicLambdaExample() {
		auto farm = std::vector<std::pair<std::string, int>>{
			{"Bear", 5},
			{"Deer", 0},
			{"Pig", 4}
		};

		auto countries = std::vector<std::pair<std::string, Continent>>{
			{"Sweden", Continent::Europe},
			{"India", Continent::Asia},
			{"Belarus", Continent::Europe},
			{"Mexico", Continent::America}
		};

		// I guess we have to wrap the lambda inside a templated function cause there is no other way to declare a template when creating the lambda
		// for polymorphic paramaters
		auto lessBySecond = [](const auto& a, const auto& b) {
			return a.second < b.second;
		};

		// Both vectors can be sorted with the same lambda
		std::sort(farm.begin(), farm.end(), lessBySecond);
		std::sort(countries.begin(), countries.end(), lessBySecond);

		auto numberOfEuropeanCountries = std::count_if(countries.begin(), countries.end(), PolyLambda::isSecondEqual(Continent::Europe));
	}
}
