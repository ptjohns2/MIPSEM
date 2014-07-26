#include "StringResolver.hpp"

#include "Exceptions.hpp"
#include "Parser.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>

//	Constructors
StringResolver::StringResolver(InstructionDataBank* bank)
	:	parser()
{
	addInstructionDataBank(bank);
}
StringResolver::~StringResolver()
{

}


//	public Methods

void StringResolver::addInstructionDataBank(InstructionDataBank* bank){
	for(int i=0; i<bank->size(); i++){
		addInstructionData(bank->get(i));
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
	int bin = hash(getHashableStringFromInstructionData(id));
	table[bin].push_back(id);
}

bool StringResolver::instructionStrIsMatch(InstructionData* id, string rightInstrStr){
	string hashRHS = StringResolver::getHashableStringFromInstructionString(rightInstrStr);
	string hashID = StringResolver::getHashableStringFromInstructionData(id);
	return (hashRHS == hashID);
}


int StringResolver::hash(string key){
	unsigned int hashVal = hasher(key);
	int retHash = hashVal % INSTRUCTION_DATA_HASH_TABLE_SIZE;
	return retHash;
}

string StringResolver::getHashableStringFromInstructionString(string instructionString){
	vector<string> tokens = Parser::tokenizeInstruction(instructionString);
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
		bool isNestedByParentheses = Parser::isNestedByParentheses(tmpArg);
		if(isNestedByParentheses){
			tmpArg = Parser::removeNestedParentheses(tmpArg);
		}
		if(parser.tokenIsGPRegister(tmpArg)){
			tmpTokStr = "g$";
		}else if(parser.tokenIsFPRegister(tmpArg)){
			tmpTokStr = "f$";
		}else if(parser.literals.tokenIsFixedPointLiteral(tmpArg)){
			tmpTokStr = ".";
		}else{
			//EXCEPTION
			throw InvalidTokenException("Instruction argument", tmpArg);
		}
		if(isNestedByParentheses){
			tmpTokStr = "(" + tmpTokStr + ")";
		}
		ss << tmpTokStr;
	}

	string tmpHashable = ss.str();
	tmpHashable = parser.toLower(tmpHashable);
	return tmpHashable;
}

string StringResolver::getHashableStringFromInstructionData(InstructionData* id){
	stringstream ss;
	ss << id->getName() << ":";

	for(unsigned int i=0; i<id->getNumParameters(); i++){
		string tmpTokStr;
		if(id->parameterIsGPRegister(i)){
			tmpTokStr = "g$";
		}else if(id->parameterIsFPRegister(i)){
			tmpTokStr = "f$";
		}else if(id->parameterIsLiteral(i)){
			tmpTokStr = ".";
		}

		if(id->paramHasParenthises(i)){
			tmpTokStr = "(" + tmpTokStr + ")";
		}
		ss << tmpTokStr;
	}

	string tmpHashable = ss.str();
	tmpHashable = parser.toLower(tmpHashable);
	return tmpHashable;
}


















