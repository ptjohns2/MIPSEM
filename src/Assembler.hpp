#ifndef __ASSEMBLER_HPP__
#define __ASSEMBLER_HPP__

#include "MemoryMap.hpp"
#include "VirtualMemory.hpp"

#include <utility>
#include <unordered_map>

using namespace std;


class Assembler{
	public:
		Assembler();
		~Assembler();
		void init();
		void deinit();
		
		void addLabelAddress(string, virtualAddr);
		virtualAddr getLabelAddress(string);

		void loadProgramFromFile(string fileName);

	private:
		VirtualMemory memory;
		vector<string> program;

		vector<pair<virtualAddr, string>> memoryMappedProgram;
		unordered_map<string, virtualAddr> labelDB;
};







#endif





