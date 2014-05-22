#include "StringResolver.hpp"

#include "parse.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
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
	string hashedInstructionString = getHashableStringFromInstructionString(instructionString);
	int bin = hash(hashedInstructionString);
	for(unsigned int i=0; i<table[bin].size(); i++){
		if(instructionStrIsMatch(table[bin][i], instructionString)){
			return table[bin][i];
		}
	}
	return NULL;
}


//	private Methods
void StringResolver::addInstructionData(InstructionData* id){
	int bin = hash(getHashableStringFromParameterTokens(id->getName(), id->getParameters()));
	table[bin].push_back(id);
}

bool StringResolver::instructionStrIsMatch(InstructionData* id, string rightInstrStr){
	string hashRHS = StringResolver::getHashableStringFromInstructionString(rightInstrStr);
	string hashID = StringResolver::getHashableStringFromParameterTokens(id->getName(), id->getParameters());
	return (hashRHS == hashID);
}


int StringResolver::hash(string key){
	unsigned int hashVal = hasher(key);
	int retHash = hashVal % INSTRUCTION_DATA_HASH_TABLE_SIZE;
	return retHash;
}

string StringResolver::getHashableStringFromInstructionString(string instructionString){
	vector<string> tokens = parse::tokenizeInstruction(instructionString);
	string instructionName = tokens[0];
	tokens.erase(tokens.begin());
	string retStr = getHashableStringFromInstructionTokens(instructionName, tokens);
	return retStr;
}

string StringResolver::getHashableStringFromInstructionTokens(string name, vector<string> arguments){
	stringstream ss;
	ss << name << ":";

	for(unsigned int i=0; i<arguments.size(); i++){
		string tmpArg = arguments[i];
		string tmpTokStr;
		bool hasParentheses = parse::hasParentheses(tmpArg);
		if(hasParentheses){
			tmpArg = parse::removeParentheses(tmpArg);
		}
		if(parse::argumentIsGPRegister(tmpArg)){
			tmpTokStr = "g$";
		}else if(parse::argumentIsFPRegister(tmpArg)){
			tmpTokStr = "f$";
		}else if(parse::tokenIsLiteral(tmpArg)){
			tmpTokStr = ".";
		}else{
			cout << "invalid token " << tmpArg;
			getchar();
		}
		if(hasParentheses){
			tmpTokStr = "(" + tmpTokStr + ")";
		}
		ss << tmpTokStr;
	}

	string tmpHashable = ss.str();
	std::transform(tmpHashable.begin(), tmpHashable.end(), tmpHashable.begin(), ::tolower);
	return tmpHashable;
}

string StringResolver::getHashableStringFromParameterTokens(string name, vector<string> arguments){
	stringstream ss;
	ss << name << ":";

	for(unsigned int i=0; i<arguments.size(); i++){
		string tmpArg = arguments[i];
		if(tmpArg != "_"){
			string tmpTokStr;
			bool hasParentheses = parse::hasParentheses(tmpArg);
			if(hasParentheses){
				tmpArg = parse::removeParentheses(tmpArg);
			}
			if(parse::parameterIsGPRegister(tmpArg)){
				tmpTokStr = "g$";
			}else if(parse::parameterIsFPRegister(tmpArg)){
				tmpTokStr = "f$";
			}else if(parse::parameterIsLiteral(tmpArg)){
				tmpTokStr = ".";
			}else{
				cout << "invalid token " << tmpArg;
				getchar();
			}
			if(hasParentheses){
				tmpTokStr = "(" + tmpTokStr + ")";
			}
			ss << tmpTokStr;
		}
	}

	string tmpHashable = ss.str();
	std::transform(tmpHashable.begin(), tmpHashable.end(), tmpHashable.begin(), ::tolower);
	return tmpHashable;
}


















