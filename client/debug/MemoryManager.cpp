/*
 * MemoryManager.cpp
 *
 *  Created on: 17 avr. 2013
 *      Author: pierre
 */

#include "MemoryManager.hpp"
#include "../log/Log.hpp"
#include "../util/Util.hpp"

namespace debug {

	MemoryManager* MemoryManager::m_instance = NULL;

	MemoryManager::MemoryManager() {

	}

	MemoryManager* MemoryManager::getInstance() {
		if(m_instance == NULL)
			m_instance = new MemoryManager();
		return m_instance;
	}

	void* MemoryManager::add(std::size_t size, const char* file, int line, bool array) {
		Block block;
		block.size = size;
		block.file = file;
		block.line = line;
		block.array = array;

		void* ptr = malloc(size);
		getInstance()->m_blocks[ptr] = block;
		return ptr;
	}

	 void MemoryManager::remove(void* ptr, bool array) {
		 getInstance()->m_blocks.erase(ptr);
		free(ptr);
	}

	void MemoryManager::report(std::string path) {
		std::ofstream file(path.c_str(), std::ios::out | std::ios::trunc);
		if(!file) {
			log_err "Error : unable to open "+path end_log_err;
			return;
		}
		int n = 0;
		for(std::map<void*,Block>::const_iterator it = getInstance()->m_blocks.begin(); it != getInstance()->m_blocks.end(); ++it) {
			std::string array = it->second.array ? "array" : "";
			file << it->first << "\t: " << it->second.size << "o " << array << "\n";
			file << "\t\t  file : " << it->second.file << ", line " << it->second.line << "\n";
			n += it->second.size;
		}

		file << "============================================\n";
		file << "tolal : " << getInstance()->m_blocks.size() << " blocks and " << n << "o";
		file.close();
	}

}


