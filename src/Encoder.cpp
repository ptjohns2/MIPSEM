#include "Encoder.hpp"

#include "Decoder.hpp"
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
	InstructionData* id = resolver.getInstructionData(asmString);
	if(id == NULL){
		Instruction jnk;
		return jnk;
	}

	string binString = id->getFull();

	vector<int> argumentValues;

	vector<string> parameters = id->getParameters();
	vector<string> arguments = parse::tokenizeInstruction(asmString);
	arguments.erase(arguments.begin());

	if(id->isEncodedNormally()){
		binString = encodeInstruction(binString, parameters, arguments);
	}else{
		binString = encodeAbnormalInstruction(binString, parameters, arguments, id->getInstructionID());
	}

	for(int i=0; i<binString.length(); i++){
		if(!parse::isBinaryDigit(binString[i])){
			binString[i] = DONTCAREREPLACEMENT;
		}
	}
	
	//get argument values
	for(int i=0; i<arguments.size(); i++){
		int argVal;
		if(parse::parameterIsLiteral(parameters[i])){
			if(id->isDecodedNormally()){
				argVal = Decoder::decodeArgumentToValue(binString, parameters[i]);
			}else{
				//abnormally decoded instruction
				vector<int> tmpArgumentValues;
				Decoder::decodeAbnormalInstruction(binString, id->getName(), parameters, id->getInstructionID(), tmpArgumentValues);
				argVal = tmpArgumentValues[i];
			}
		}else{
			argVal = parse::getArgumentValue(arguments[i]);
		}
		argumentValues.push_back(argVal);
	}
	

	instr bin = parse::binStrToUnsignedDecInt(binString);
	Instruction instruction = Instruction(id, asmString, binString, bin, argumentValues);
	return instruction;
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
string Encoder::encodeArgument(string binString, string parameter, string argument){
	bitrange br = parse::getParameterBitrange(parameter);
	int parameterValue = parse::getArgumentValue(argument);
	string parameterBinStr = parse::decIntToBinStr(parameterValue);
	binString = setBitrange(binString, parameterBinStr, br);
	return binString;
}

string Encoder::encodeInstruction(string binString, vector<string> parameters, vector<string> arguments){
	string newInstruction = binString;
	for(int i=0; i<arguments.size(); i++){
		newInstruction = encodeArgument(newInstruction, parameters[i], arguments[i]);
	}
	return newInstruction;
}

string Encoder::encodeAbnormalInstruction(string binString, vector<string> parameters, vector<string> arguments, int id){
	string newInstruction = binString;
	switch(id){
		case 152:
			{
			//CLO rd, rs
			newInstruction = encodeArgument(newInstruction, parameters[0], arguments[0]);
			newInstruction = encodeArgument(newInstruction, parameters[0], "$rt");
			newInstruction = encodeArgument(newInstruction, parameters[1], arguments[1]);
			}
			break;
		case 153:
			{
			//CLZ rd, rs
			newInstruction = encodeArgument(newInstruction, parameters[0], arguments[0]);
			newInstruction = encodeArgument(newInstruction, parameters[0], "$rt");
			newInstruction = encodeArgument(newInstruction, parameters[1], arguments[1]);
			}
			break;
		case 179:
			{
			//EXT rt, rs, pos, size
			newInstruction = encodeArgument(newInstruction, parameters[0], arguments[0]);
			newInstruction = encodeArgument(newInstruction, parameters[1], arguments[1]);
			newInstruction = encodeArgument(newInstruction, parameters[2], arguments[2]);

			int size = parse::getLiteralValue(arguments[3]);
			//negatives will be handled since only 5 lsb of binstr
			int msbd = size - 1;
			newInstruction = encodeArgument(newInstruction, parameters[3], std::to_string(msbd));
			}
			break;
		case 184:
			{
			//INS rt, rs, pos, size
			newInstruction = encodeArgument(newInstruction, parameters[0], arguments[0]);
			newInstruction = encodeArgument(newInstruction, parameters[1], arguments[1]);

			int pos = parse::getLiteralValue(arguments[2]);
			int size = parse::getLiteralValue(arguments[3]);
			//negatives will be handled since only 5 lsb of binstr
			int msb = pos + size - 1;
		
			newInstruction = encodeArgument(newInstruction, parameters[2], arguments[2]);
			newInstruction = encodeArgument(newInstruction, parameters[3], std::to_string(msb));
			}
			break;
		default:
			{

			}
	}
	return newInstruction;
}









