#ifndef __ASSEMBLER_HPP__
#define __ASSEMBLER_HPP__

#include "MemoryMap.hpp"
#include "VirtualMemory.hpp"

#include <utility>
#include <map>

using namespace std;

class Assembler{
	public:
		Assembler();
		~Assembler();
		void init();
		void deinit();
		
		void loadProgramFromFile(string fileName);

	private:
		VirtualMemory memory;
		vector<string> program;
		vector<pair<virtualAddr, string>> memoryMappedProgram;
		vector<pair<string, string>> labelAddressDB;
		//		map<string, string> labelAddressDB;
};

#endif