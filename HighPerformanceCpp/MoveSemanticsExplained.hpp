#pragma once

#include <initializer_list>
#include <algorithm>
#include <vector>

namespace MoveSemanticsExplained {
	class Buffer {
	private:
		size_t size_{ 0 };
		float* ptr_{ nullptr };
	public:
		// Constructor
		Buffer(const std::initializer_list<float>& values) : size_{ values.size() } {
			ptr_ = new float[values.size()];
			std::copy(values.begin(), values.end(), ptr_);
		}

		// 1. Copy constructor
		Buffer(const Buffer& other) : size_{ other.size_ } {
			ptr_ = new float[other.size_];
			std::copy(other.ptr_, other.ptr_ + size_, ptr_);
		}

		// 2. Copy assignement
		auto& operator=(const Buffer& other) {
			delete[] ptr_;
			ptr_ = new float[other.size_];
			size_ = other.size_;
			std::copy(other.ptr_, other.ptr_ + size_, ptr_);

			return *this;
		}

		// 4. Move constructor !! Do not forget to mark your move-constructors and move-assignment
	    //						  operators as noexcept (unless they might throw an exception, of course).
		//						  Not marking them noexcept prevents STL containersand algorithms
		//						  from utilizing themand resorts to a regular copy / assignment under
		//						  certain conditions.
		Buffer(Buffer&& other) noexcept : size_{ other.size_ }, ptr_{other.ptr_} {
			other.size_ = 0;
			other.ptr_ = nullptr;
		}

		// 5. Move operator
		auto& operator=(Buffer&& other) noexcept {
			size_ = other.size_;
			ptr_ = other.ptr_;

			other.size_ = 0;
			other.ptr_ = nullptr;

			return *this;
		}

		// 5. Destructor
		~Buffer() {
			delete[] ptr_; // Note, it is valid to delete a nullptr
			ptr_ = nullptr;
		}
	};


	// Problem area move semantics solve: So if we were to return a Buffer instance created on a function stack 
	// the whole float array would be copied. So we can either implement move semantics in the class or create another 
	// level of indirection inside the function by dynamically allocationg the buffer instance and returning the pointer,
	// so only the pointer would be copied

	Buffer* makeBuffer() {
		Buffer* p_Buffer = new Buffer{ {2.0f, 4.0f, 6.0f, 8.0f} };
		return p_Buffer; // returns a copy of the pointer. The problem is that now we have to manually handle the lifetime of the 
						 // dynamically allocated Buffer instance inside the calling function or wherever we decide to propagate it to
	}

	Buffer makeBufferByCopyOrMove() {
		Buffer p_Buffer{ {2.0f, 4.0f, 6.0f, 8.0f} };
		return p_Buffer; // now this either returns a copy of the Buffer instance which implicitly means it does a copy
		                 // of the whole float array managed by the buffer class or if we have move semantics implemented
						 // inside the class a new instance in the calling function will point to the already created/managed
						 // float array and our p_Buffer instance will point to nothing and will be released at the end of the function call
	}

	// ! Move semantics are applied by the compiler to r-values
	// R-values are just values that are not tied to a named variable for either of the following reasons:
	//		* It's comming straight out of a function
	//		* We make a variable an r-value by using std::move(...)

	// Example where a class contains both primitives and complex classes
	class TowerList {
	public:
		std::vector<float> towerHeights_{};
		int maxHeightIndex_{ -1 };

		TowerList() : maxHeightIndex_{ 1 }, towerHeights_{ 25.0f, 44.0f, 12.0f } {}

		TowerList(TowerList&& other) noexcept {
			std::swap(towerHeights_, other.towerHeights_);
			std::swap(maxHeightIndex_, other.maxHeightIndex_);
		}

		auto& operator=(TowerList&& other) noexcept {
			std::swap(towerHeights_, other.towerHeights_);
			std::swap(maxHeightIndex_, other.maxHeightIndex_);

			return *this;
		}
	};

	// Example of && applied to a functions wich means that function is only permited to be executed on an r-value
	struct FunctionContainer {
		auto func() && {}
	};

	void useFunctionContainer() {
		auto a = FunctionContainer{};
		//a.func(); will not compile
		std::move(a).func();
		FunctionContainer{}.func();
	}
}