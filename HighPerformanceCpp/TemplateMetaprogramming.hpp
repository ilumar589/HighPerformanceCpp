#pragma once
#include <assert.h>
#include <type_traits>
#include <iostream>

namespace TemplateExamples {
	template <int N, typename T>
	auto const_pow_n(const T& v) {
		assert(N > 0);
		auto product = T{ 1 };
		for (int i = 0; i < N; ++i) {
			product *= v;
		}
		return product;
	}
}

namespace TypeTraits {
	// * Type traits that return information about a type as a boolean or an integer value
	// * Type traits that return a new type

	auto sign_function = [](const auto& v) -> int {
		using reference_type = decltype(v);
		using value_type = std::remove_reference_t(reference_type);

		if (std::is_unsigned_v<value_type>) {
			return 1;
		}

		return v < 0 ? -1 : 1;
	};
}

namespace ConstExpression {
	// The constexpr keyword tells the compiler that a certain function is intended to be
	// evaluated at compile time if all the conditions allowing for compile - time evaluation are
	// fulfilled.Otherwise, it will execute at runtime, like a regular function.

	constexpr auto sum(int x, int y, int z) { return x + y + z; }

	const auto value = sum(3, 4, 5);

	// in this case the compiler will generate the following regular c++ code const auto value = 12 then it's compiled to machine code as usual

	// nice feature - if constexpr gives the ability to ignore the else branch and we can see in this example that such a simple feature let's us 
	// create a form of compile time polymorphism which is much more performant than runtime polymorphism which uses indirection and vtables

	struct Bear { auto roar() const { std::cout << "roar"; } };
	struct Duck { auto quack() const { std::cout << "quack"; } };

	template<typename Animal>
	auto speak(const Animal& a) {
		if constexpr (std::is_same_v<Animal, Bear>) {
			a.roar();
		} else if constexpr (std::is_same_v<Animal, Duck>) {
			a.quack();
		}
	}
}