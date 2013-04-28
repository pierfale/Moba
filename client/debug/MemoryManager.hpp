/*
 * MemoryManager.hpp
 *
 *  Created on: 17 avr. 2013
 *      Author: pierre
 */

#ifndef MEMORYMANAGER_HPP_
#define MEMORYMANAGER_HPP_

#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>


namespace debug {

	class MemoryManager {
	public:
		struct Block {
			std::size_t size;
			const char* file;
			int line;
			bool array;
		};

		static void* add(std::size_t size, const char* file, int line, bool array);
		static void remove(void* ptr, bool array);
		static void report(std::string path);

	private:
		MemoryManager();
		static MemoryManager* getInstance();
		static MemoryManager* m_instance;

		std::map<void*, Block> m_blocks;

	};
}


#endif /* MEMORYMANAGER_HPP_ */
