#include "StringResolver.hpp"

#include "parse.hpp"

#include <algorithm>
#include <cassert>
#include <sstream>

//	Constructors
StringResolver::StringResolver(InstructionDataBank* bank){
	addInstructionDataBank(bank);
}
StringResolver::~StringResolver()
{

}


//	public Methods

void StringResolver::addInstructionDataBank(InstructionDataBank* bank){
	for(int i=0; i<bank->size(); i++){
		addInstructionData(bank->bank[i]);
	}
}

InstructionData* StringResolver::getInstructionData(string instructionString){
	string hashedInstructionString = instructionStringToHashableString(instructionString);
	int bin = hash(hashedInstructionString);
	for(int i=0; i<table[bin].size(); i++){
		if(stringIsMatch(table[bin][i], instructionString)){
			return table[bin][i];
		}
	}
	return NULL;
}


//	private Methods
void StringResolver::addInstructionData(InstructionData* id){
	int bin = hash(generateHashableName(id->getName(), id->getArguments()));
	table[bin].push_back(id);
}

bool StringResolver::stringIsMatch(InstructionData* id, string rightInstrStr){
	string hashRHS = StringResolver::instructionStringToHashableString(rightInstrStr);
	string hashID = StringResolver::generateHashableName(id->getName(), id->getArguments());
	return (hashRHS == hashID);
}


int StringResolver::hash(string key){
	unsigned int hashVal = hasher(key);
	int retHash = hashVal % INSTRUCTION_DATA_HASH_TABLE_SIZE;
	return retHash;
}

string StringResolver::instructionStringToHashableString(string instructionString){
	vector<string> tokens = parse::tokenizeInstruction(instructionString);
	string instructionName = tokens[0];
	tokens.erase(tokens.begin());
	for(int i=tokens.size(); i<4; i++){
		tokens.push_back("_");
	}
	string hashableString = generateHashableName(instructionName, tokens);
	return hashableString;
}

string StringResolver::generateHashableName(string name, vector<string> arguments){
	ostringstream oss;
	oss << "@" << name << ":";

	for(int i=0; i<arguments.size(); i++){
		string tmpArg = arguments[i];
		if(tmpArg != "_"){
			int argStart = (tmpArg[0] == '(')? 1 : 0;

			if(argStart == 1){oss << "(";}
			oss << ((tmpArg[argStart] == '$')? '$' : '.');
			if(argStart == 1){oss << ")";}
		}
	}

	string tmpHashable = oss.str();
	std::transform(tmpHashable.begin(), tmpHashable.end(), tmpHashable.begin(), ::tolower);
	return tmpHashable;
}



















