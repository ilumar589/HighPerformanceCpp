#pragma once

namespace ConstPropagation {
	// A common mistake when writing const-correct code in C++ is that a const initialized object
	// can still manipulate the values that member pointers points at

	class Foo {
	private:
		int* ptr_{};

	public:
		Foo(int* ptr) : ptr_{ptr} {}
		void setPtrValue(int v) const {
			*ptr_ = v; // compiles despite function being declared const!
		}
	};

	// Revised Foo class
	namespace exp = std::experimental;
	class FooRevised {
	private:
		exp::propagate_const<int*> ptr_{ nullptr };
		int val_{};

	public:
		auto setPtr(int* p) const {
			//ptr_ = p; // will not compile as expected
		}

		auto setVal(int v) const {
			//*ptr_ = v; // will not compile, const is propagated
		}
	};
}