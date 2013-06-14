/*
 * Alloc.hpp
 *
 *  Created on: 17 avr. 2013
 *      Author: pierre
 */

#ifndef ALLOC_HPP_
#define ALLOC_HPP_


#ifdef DEBUG

#include "MemoryManager.hpp"


inline void* operator new(std::size_t size, const char* file, int line) {
	return debug::MemoryManager::add(size, file, line, false);
}

inline void* operator new[](std::size_t size, const char* file, int line) {
	return debug::MemoryManager::add(size, file, line, true);
}

#define new new(__FILE__, __LINE__)

inline void operator delete(void* Ptr)
{
	debug::MemoryManager::remove(Ptr, false);
}

inline void operator delete[](void* Ptr)
{
	debug::MemoryManager::remove(Ptr, true);
}

#endif

#endif /* ALLOC_HPP_ */
