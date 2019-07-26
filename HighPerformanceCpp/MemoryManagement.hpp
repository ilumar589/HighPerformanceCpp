#pragma once

#include <cstdlib>
#include <iostream>

// The new and delete operators can be overriden as global functions or as static member functions of a class

//void* operator new(size_t size) {
//	void* p = std::malloc(size);
//	std::cout << "allocated " << size << " byte(s)" << std::endl;
//	return p;
//}
