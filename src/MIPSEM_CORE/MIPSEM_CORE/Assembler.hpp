#ifndef __ASSEMBLER_HPP__
#define __ASSEMBLER_HPP__

#include "Encoder.hpp"
#include "MemoryMap.hpp"
#include "Parser.hpp"
#include "VirtualMemory.hpp"
class AssemblerException;

#include <utility>
#include <unordered_map>

using namespace std;





typedef enum {
	DIRECTIVE_DATA = 0, DIRECTIVE_TEXT = 1, DIRECTIVE_KDATA = 2, DIRECTIVE_KTEXT = 3, 

	DIRECTIVE_BYTE, DIRECTIVE_HALF, DIRECTIVE_WORD, 
	DIRECTIVE_FLOAT, DIRECTIVE_DOUBLE, 
	DIRECTIVE_ASCII, DIRECTIVE_ASCIIZ,

	DIRECTIVE_ALIGN, DIRECTIVE_SPACE,

	DIRECTIVE_INCLUDE, DIRECTIVE_EXTERN, DIRECTIVE_GLOBL, DIRECTIVE_SET, 
	DIRECTIVE_MACRO, DIRECTIVE_END_MACRO, DIRECTIVE_EQV,

	DIRECTIVE_LABEL, DIRECTIVE_INSTRUCTION,
    
}DIRECTIVE;
#define     DIRECTIVE_ENUM_SIZE (22)

typedef enum {
	ACTION_INIT = 0, ACTION_DECLARE_SEGMENT, ACTION_MEMWRITE_INTEGRAL, ACTION_MEMWRITE_STRING, ACTION_ALIGN, ACTION_SPACE, ACTION_INSTRUCTION_ENCODE
}ACTION;



class ProgramLine{
	public:
		string fileName;
		uint32_t lineNumber;
		string text;
};

class ProgramAtom{
	public:
		virtualAddr addr;
		string token;
		DIRECTIVE type;
		ProgramLine* programLine;
};


class MacroAtom{
	public:
		MacroAtom();
		MacroAtom(vector<ProgramLine>);
		~MacroAtom();
		void init();
		void deinit();
		
		vector<ProgramLine> buildMacro(vector<string> const &arguments);
		vector<ProgramLine> buildMacro(string programLine);

		vector<ProgramLine> getUniquelyLabelledMacroBody();

		bool lineIsMacroCall(string programLine);
		vector<string> getMacroCallArguments(string programLine);

		vector<pair<string, string>> reassignedLabels;

	private:
		string name;
		vector<string> parameters;
		vector<ProgramLine> body;
		int numTimesUsed;

};

class Assembler{
	public:
		Assembler();
		virtual ~Assembler();
		void init();
		void deinit();
		void reset();

		bool assemble(string fileName);
		void loadProgramFromFile(string fileName, ProgramLine* programLine = NULL);

	//private:
		//Pre-processing
		void splitLabels();
		void replaceEqv();
		void extractMacroDefinitions();
		void replaceMacros();
		void pseudoInstructionPad();

		//Memory alignment
		bool tokenIsInLabelDB(string);
		void addLabelAddress(string label, virtualAddr);
		virtualAddr getLabelAddress(string);

		void applyDirective(string, ProgramLine*);

		void alignRawProgram();
		void flushLabelBuffer();

		void alignSegmentTop();
		void incrementSegmentTop(virtualAddr);
		virtualAddr getCurrentMemoryLocation();

		void alignLiteralTokenList(vector<string> const &tokens, string currentLine, ProgramLine* programLine);
		void writeAlignedRawProgramToDisk(string fileName);

		//Post-processing
		void pseudoInstructionReplace();
		void replaceLabels();

		//VirtualMemory mapping
		void mapAlignedProgramToVirtualMemory();



		Parser parser;
		Encoder encoder;
		
		void setRootDirectory(string);
		void setProgramName(string);
		string rootDirectory;
		#define DEFAULT_PROGRAMNAME	("out")
		string programName;
		#define DEFAULT_OBJECTNAMEPOSTFIX	(".MIPSEMcoreObj")
		string objectNamePostfix;
		#define DEFAULT_ALIGNEDPROGRAMNAMEPOSTFIX	(DEFAULT_OBJECTNAMEPOSTFIX + std::string(".txt"))
		string alignedProgramNamePostfix;
		string builtObjectFileName;
		
		virtualAddr memorySegmentTopArray[NUMBER_OF_MEMORY_SEGMENTS];
		DIRECTIVE currentMemorySegment;
		DIRECTIVE currentValueTypeSpecifier;
		ACTION currentAction;
		uint32_t currentByteAlignment;
        size_t valueTypeSpecifierSizes[DIRECTIVE_ENUM_SIZE];

		VirtualMemory virtualMemory;
		
		vector<ProgramLine> program;
		vector<ProgramAtom> alignedProgram;

		vector<pair<string, string>> eqvDB;
		vector<MacroAtom> macroDB;

		vector<ProgramLine*> labelsToAssign;
		vector<string> labelNames;
		unordered_map<string, virtualAddr> labelMap;


		//EXCEPTIONS
		void addException(AssemblerException const &e);
		vector<AssemblerException> recoverableExceptions;
		ProgramLine* currentProgramLine;


};







#endif





