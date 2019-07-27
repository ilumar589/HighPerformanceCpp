#pragma once

#include <cstdlib>
#include <iostream>

// The new and delete operators can be overriden as global functions or as static member functions of a class

//void* operator new(size_t size) {
//	void* p = std::malloc(size);
//	std::cout << "allocated " << size << " byte(s)" << std::endl;
//	return p;
//}




// Memory alignement example

namespace Padding {
	class Document {
		bool isCached_{}; // 1 byte
		// char padding1[7] // Invisible padding added by the compiler to not segment memory. So another 7 bytes to get to the start of the rank_ variable address
		double rank_{}; // 8 bytes
		int id_{};
		// char padding2[4] // Added by the compiler. The biggest variable inside a class determines the alignement of the whole class. In our case it's rank_.
							// so our class has a memory alignement of multiple of 8. The last padding was added to satisfy this requirement. 4 * 4 bytes
	};

	class RearangedDocument {
		double rank_{};
		int id_{};
		bool isCached_{};
		// char padding[3] // We now realize we can rearange the members of the class in order to minimize the padding added by the compiler by starting with the largest sized variable
	};

	// From a performance perspective, there can also be cases where you want to align objects to
	//	cache lines to minimize the number of cache lines an object spans over.While we are on the
	//	subject of cache friendliness, it should also be mentioned that it can be beneficial to place
	//	multiple data members that are frequently used together next to each other.
}

namespace CustomMemoryAllocators {

	template<size_t N>
	class Arena {
		static constexpr size_t alignement = alignof(std::max_align_t);
	private:
		char* ptr_{nullptr};
		alignas(alignement) char buffer_[N]; // alignas forces the N sized char array to have an alignement equal to our variable(alignement) which is std::max_align_t)


		bool pointerInBuffer(const char* p) const noexcept {
			return buffer_ <= p && p <= buffer_ + N;
		}

		static size_t alignUp(size_t n) noexcept {
			return (n + (alignement - 1)) & ~(alignement - 1);
		}
	public:
		Arena() noexcept : ptr_{buffer_} {}
		Arena(const Arena&) = delete;
		Arena& operator=(const Arena&) = delete;

		void reset() noexcept { ptr_ = buffer; }

		// check the book for the rest
	};
}
