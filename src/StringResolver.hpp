#ifndef __STRINGRESOLVER_HPP__
#define __STRINGRESOLVER_HPP__

#include "InstructionData.hpp"
#include "InstructionDataBank.hpp"
#include "Parser.hpp"
#include "types.hpp"

#include <string>
#include <vector>

#define INSTRUCTION_DATA_HASH_TABLE_SIZE	(1009)

class StringResolver{
	public:
		//Constructors
		StringResolver();
		~StringResolver();

		//Methods
		void addInstructionDataBank(InstructionDataBank &bank);
		InstructionData* getInstructionData(string instructionString);

	private:
		//Methods
		void addInstructionData(InstructionData id);
		bool instructionStrIsMatch(InstructionData* id, string rightInstrStr);

		int hash(string);	
		string getHashableStringFromInstructionString(string instructionString);
		string getHashableStringFromInstructionTokens(string name, vector<string> arguments);
		string getHashableStringFromInstructionData(InstructionData* id);


		//Members
		std::hash<string> hasher;
		vector<InstructionData> table[INSTRUCTION_DATA_HASH_TABLE_SIZE];
		Parser parser;
};



#endif
