#include "StringResolver.hpp"
#include "stringManip.hpp"
#include "decode.hpp"

#include <cassert>

//==================
//class StringResolver
//	Constructors
StringResolver::StringResolver()
{
	num = 0;
}
StringResolver::StringResolver(InstructionDataBank* bank){
	num = 0;
	addInstructionDataBank(bank);
}
StringResolver::~StringResolver()
{

}


//	public Methods
void StringResolver::addInstructionData(InstructionData* id){
	int bin = hash(id->getHashableName());
	table[bin].push_back(id);
	num++;
}

void StringResolver::addInstructionDataBank(InstructionDataBank* bank){
	for(int i=0; i<bank->size; i++){
		addInstructionData(bank->bank[i]);
	}
}

InstructionData* StringResolver::getInstructionData(string instructionString){
	string hashedInstructionString = instructionStringToHashableString(instructionString);
	int bin = hash(hashedInstructionString);
	for(int i=0; i<table[bin].size(); i++){
		if(table[bin][i]->getHashableName() == hashedInstructionString){
			return table[bin][i];
		}
	}
}

int StringResolver::hash(string key){
	unsigned int hashVal = hasher(key);
	int retHash = hashVal % INSTRUCTION_DATA_HASH_TABLE_SIZE;
	return retHash;
}

string StringResolver::instructionStringToHashableString(string instructionString){
	vector<string> tokens = stringManip::tokenizeInstruction(instructionString);
	string name = tokens[0];
	string pos[4];
	int numArgs = 0;
	for(int i=1; i<tokens.size(); i++){
		pos[i-1] = tokens[i];
		numArgs++;
	}
	for(int i = numArgs; i<4; i++){
		pos[i] = "_";
	}
	string hashableString = InstructionData::generateHashableName(name, pos[0], pos[1], pos[2], pos[3]);
	return hashableString;
}





