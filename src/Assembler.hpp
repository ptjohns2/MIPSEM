#ifndef __ASSEMBLER_HPP__
#define __ASSEMBLER_HPP__

#include "MemoryMap.hpp"
#include "Parser.hpp"
#include "VirtualMemory.hpp"

#include <utility>
#include <unordered_map>

using namespace std;



#define SIZE_BYTE (1)
#define SIZE_WORD (8)
#define SIZE_HALF (SIZE_WORD / 2)
#define SIZE_FLOAT (SIZE_WORD)
#define SIZE_DOUBLE (2 * SIZE_FLOAT)


typedef enum {
	DIRECTIVE_DATA = 0, DIRECTIVE_TEXT = 1, DIRECTIVE_KDATA = 2, DIRECTIVE_KTEXT = 3, 

	DIRECTIVE_BYTE, DIRECTIVE_HALF, DIRECTIVE_WORD, 
	DIRECTIVE_FLOAT, DIRECTIVE_DOUBLE, 
	DIRECTIVE_ASCII, DIRECTIVE_ASCIIZ,

	DIRECTIVE_ALIGN, DIRECTIVE_SPACE,

	DIRECTIVE_INCLUDE, DIRECTIVE_EXTERN, DIRECTIVE_GLOBL, DIRECTIVE_SET, 
	DIRECTIVE_MACRO, DIRECTIVE_END_MACRO, DIRECTIVE_EQV,

	DIRECTIVE_LABEL, DIRECTIVE_INSTRUCTION
}DIRECTIVE;

typedef enum {
	ACTION_INIT = 0, ACTION_DECLARE_SEGMENT, ACTION_MEMWRITE_INTEGRAL, ACTION_MEMWRITE_STRING, ACTION_ALIGN, ACTION_SPACE, ACTION_INSTRUCTION_ENCODE
}ACTION;


struct ProgramAtom{
	virtualAddr addr;
	string token;
	DIRECTIVE type;
};

class Assembler{
	public:
		Assembler();
		~Assembler();
		void init();
		void deinit();
		void globalReset();
		void localReset();


		void loadProgramFromFile(string fileName);

	//private:
		void addLabelAddress(string, virtualAddr);
		virtualAddr getLabelAddress(string);

		void applyDirective(string);

		void convertRawProgramToMemoryMappedProgram();
		void assignUnassignedLabelsAndAddToMemoryMappedProgram();
		void alignSegmentTop();
		void incrementSegmentTop(virtualAddr);
		virtualAddr getCurrentMemoryLocation();
		void applyLiteralTokenList(vector<string> const &tokens, string currentLine);
		void writeMemoryMappedProgramToDisk(string fileName);

		Parser parser;
		
		
		virtualAddr memorySegmentTopArray[NUMBER_OF_MEMORY_SEGMENTS];
		DIRECTIVE currentMemorySegment;
		DIRECTIVE currentValueTypeSpecifier;
		ACTION currentAction;

		uint32_t currentByteAlignment;


		VirtualMemory memory;

		vector<string> program;

		vector<ProgramAtom> memoryMappedProgram;
		vector<string> labelsToAssign;
		vector<string> labelNames;
		unordered_map<string, virtualAddr> labelMap;

		vector<string> globalLabelNames;
		unordered_map<string, virtualAddr> globalLabelMap;


};







#endif





