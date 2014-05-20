#include "Encoder.hpp"

#include "parse.hpp"

#include <bitset>
#include <cassert>
#include <iostream>
#include <tuple>

//	Constructors
Encoder::Encoder(InstructionDataBank* bank) : resolver(bank) {}

Encoder::~Encoder(){}

//	public Methods
Instruction Encoder::buildInstruction(string asmString){
	Instruction ret = Instruction();
	InstructionData* id = resolver.getInstructionData(asmString);
	ret.id = id;

	string tmpIDbinStr = id->getFull();
	vector<string> tmpInstructionTokens = parse::tokenizeInstruction(asmString);
	tmpInstructionTokens.erase(tmpInstructionTokens.begin());
	vector<string> tmpIDparameters = id->getParameters();
	ret.binString = encodeInstruction(tmpIDbinStr, tmpIDparameters, tmpInstructionTokens);

	ret.bin = parse::binStrToUnsignedDecInt(ret.binString);
	return ret;
}

string Encoder::setBitrange(string instruction, string value, bitrange range){
	return setBitrange(instruction, value, range.first, range.second);
}
string Encoder::setBitrange(string instruction, string value, unsigned int start, unsigned int end){
	assert(instruction.length() == INSTRUCTIONSIZE);
	
	int segmentSize = start - end + 1;
	assert(segmentSize <= value.length());

	int instructionStart = instruction.length() - start - 1;
	int valueStart = value.length() - segmentSize;

	for(int i=0; i<segmentSize; i++){
		instruction[instructionStart + i] = value[valueStart + i];
	}

	return instruction;
}


//	private Methods
string Encoder::encodeArgument(string binStr, string parameter, string argument){
	bitrange br = parse::getParameterBitrange(parameter);
	int parameterValue = parse::getArgumentValue(argument);
	string parameterBinStr = parse::decIntToBinStr(parameterValue);
	binStr = setBitrange(binStr, parameterBinStr, br);
	return binStr;
}

string Encoder::encodeInstruction(string binStr, vector<string> parameters, vector<string> arguments){
	for(int i=0; i<arguments.size(); i++){
		binStr = encodeArgument(binStr, parameters[i], arguments[i]);
	}
	return binStr;
}

string Encoder::encodeAbnormalInstruction(string binStr, vector<string> parameters, vector<string> arguments){
	//???
	return "";
}
