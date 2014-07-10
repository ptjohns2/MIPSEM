#ifndef __ASSEMBLER_HPP__
#define __ASSEMBLER_HPP__

#include "MemoryMap.hpp"
#include "VirtualMemory.hpp"

#include <utility>

using namespace std;

class Assembler{
	public:

	private:


		VirtualMemory memory;
		vector<string> program;
		vector<pair<string, string>> labelAddressDB;
};

#endif