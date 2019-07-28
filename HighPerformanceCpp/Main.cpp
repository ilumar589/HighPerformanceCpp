#include "Lambda.hpp"
#include "TemplateMetaprogramming.hpp"

int main() {

	//printValuesAboveDesiredValue(1);

	//clickButtons();

	//std::cout << "Direct lambda call time:" << testDirectLambda() << std::endl;
	//std::cout << "Std function call time:" << testStdFunction() << std::endl;

	auto x = TemplateExamples::const_pow_n<2, float>(4.0f);

	std::cout << "Value : " << x << std::endl;

	return 0;
}