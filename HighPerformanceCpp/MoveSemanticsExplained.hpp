#pragma once

#include <initializer_list>
#include <algorithm>

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

		// 3. Destructor
		~Buffer() {
			delete[] ptr_; // Note, it is valid to delete a nullptr
			ptr_ = nullptr;
		}
	};
}