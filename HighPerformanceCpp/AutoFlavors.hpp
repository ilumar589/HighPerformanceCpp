#pragma once

struct Foo {
	int member{};

	int val() const {
		return member;
	}

	const int& cref() const {
		return member;
	}

	int& mref() {
		return member;
	}
};

// auto equivalent

struct AutoFoo {
	int member{};

	auto val() const {
		return member;
	}

	auto& cref() const {
		return member;
	}

	auto& mref() {
		return member;
	}
};


// auto&& or for a template T&& is something called a forwarding reference, which binds to anything. Not to be confused with && for a specific type which is an r-value