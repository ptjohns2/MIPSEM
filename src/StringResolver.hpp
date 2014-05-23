#ifndef __STRINGRESOLVER_HPP__
#define __STRINGRESOLVER_HPP__

#include "InstructionData.hpp"
#include "types.hpp"
#include "InstructionDataBank.hpp"

#include <string>
#include <vector>


class StringResolver{
	public:
		//Constructors
		StringResolver(InstructionDataBank* bank);
		~StringResolver();

		//Methods
		void addInstructionDataBank(InstructionDataBank* bank);
		InstructionData* getInstructionData(string instructionString);

	private:
		//Methods
		void addInstructionData(InstructionData* id);
		static bool instructionStrIsMatch(InstructionData* id, string rightInstrStr);

		int hash(string);	
		static string getHashableStringFromInstructionString(string instructionString);
		static string getHashableStringFromInstructionTokens(string name, vector<string> arguments);
		static string getHashableStringFromParameterTokens(string name, vector<string> parameters);


		//Members
		std::hash<string> hasher;
		vector<InstructionData*> table[INSTRUCTION_DATA_HASH_TABLE_SIZE];
};



#endif
