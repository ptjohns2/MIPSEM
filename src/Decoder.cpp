#include "Decoder.hpp"

#include "parse.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

//	Constructors
Decoder::Decoder(InstructionDataBank* bank)	: resolver(bank){}

Decoder::~Decoder(){}

//	public Methods
Instruction Decoder::buildInstruction(instr i){
	return buildInstruction(parse::decIntToBinStr(i));
}

Instruction Decoder::buildInstruction(string binStr){
	Instruction ret = Instruction();
	InstructionData* id = resolver.getInstructionData(binStr);
	ret.id = id;
	ret.binString = binStr;
	ret.bin = parse::binStrToUnsignedDecInt(binStr);
	ret.asmString = decodeInstruction(binStr, id->getName(), id->getParameters());
	return ret;
}


string Decoder::extractBitrange(string value, bitrange range){
	return extractBitrange(value, range.first, range.second);
}
string Decoder::extractBitrange(string value, unsigned int start, unsigned int end){
	int valueStart = value.length() - start - 1;
	int segmentSize = start - end + 1;
	string retVal = value.substr(valueStart, segmentSize);
	return retVal;
}


//	private Methods
string Decoder::decodeArgument(string binStr, string parameter){
	bitrange br = parse::getParameterBitrange(parameter);
	string argumentBinStr = extractBitrange(binStr, br);
	if(parse::parameterIsGPRegister(parameter)){
		return parse::getGPRegisterName(parse::binStrToUnsignedDecInt(argumentBinStr));
	}else if(parse::parameterIsFPRegister(parameter)){
		return parse::getGPRegisterName(parse::binStrToUnsignedDecInt(argumentBinStr));
	}else if(parse::parameterIsUnsignedLiteral(parameter)){
		return std::to_string(parse::binStrToUnsignedDecInt(argumentBinStr));
	}else if(parse::parameterIsSignedLiteral(parameter)){
		return std::to_string(parse::binStrToSignedDecInt(argumentBinStr));
	}
}

string Decoder::decodeInstruction(string binStr, string name, vector<string> parameters){
	stringstream ss;
	ss << name;
	int numParameters = 0;
	for(int i=0; i<parameters.size(); i++){
		if(parameters[i] != "_"){numParameters++;}
	}
	if(numParameters > 0){ss << '\t';}

	for(int i=0; i<numParameters; i++){
		ss << decodeArgument(binStr, parameters[i]);
		if(i < numParameters + 1){ss << ", ";}
	}

	return ss.str();
}

string Decoder::decodeAbnormalInstruction(string binStr, string instruction){
	//???
	return "";
}



















