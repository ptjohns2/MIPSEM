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
	InstructionData* id = resolver.getInstructionData(binStr);
	if(id == NULL){
		Instruction jnk;
		return jnk;
	}

	instr bin = parse::binStrToUnsignedDecInt(binStr);

	vector<string> parameters = id->getParameters();
	
	int numArgs = 0;
	for(int i=0; i<parameters.size(); i++){
		if(parameters[i] != "_"){
			numArgs++;
		}
	}
	vector<int64_t> argumentValues;
	if(id->isDecodedNormally()){
		for(int i=0; i<numArgs; i++){
			bitrange br = parse::getParameterBitrange(parameters[i]);
			int argVal = decodeArgumentToValue(binStr, parameters[i]);
			argumentValues.push_back(argVal);
		}
	}
	
	string asmString;
	if(id->isDecodedNormally()){
		 asmString = decodeInstruction(binStr, id->getName(), parameters);
	}else{
		asmString = decodeAbnormalInstruction(binStr, id->getName(), parameters, id->getId(), argumentValues);
	}
	
	Instruction instruction = Instruction(id, asmString, binStr, bin, argumentValues);
	return instruction;
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
string Decoder::decodeArgumentToMnemonic(string binStr, string parameter){
	bool hasParentheses = parse::hasParentheses(parameter);
	if(hasParentheses){
		parameter = parse::removeParentheses(parameter);
	}
	bitrange br = parse::getParameterBitrange(parameter);
	string argumentBinStr = extractBitrange(binStr, br);
	string retStr;
	if(parse::parameterIsGPRegister(parameter)){
		retStr = parse::getGPRegisterName(parse::binStrToUnsignedDecInt(argumentBinStr));
	}else if(parse::parameterIsFPRegister(parameter)){
		retStr = parse::getFPRegisterName(parse::binStrToUnsignedDecInt(argumentBinStr));
	}else if(parse::parameterIsUnsignedLiteral(parameter)){
		retStr = std::to_string(parse::binStrToUnsignedDecInt(argumentBinStr));
	}else if(parse::parameterIsSignedLiteral(parameter)){
		retStr = std::to_string(parse::binStrToSignedDecInt(argumentBinStr));
	}
	if(hasParentheses){
		retStr = "(" + retStr + ")";
	}
	return retStr;
}

int64_t Decoder::decodeArgumentToValue(string binStr, string parameter){
	parameter = parse::removeParentheses(parameter);
	bitrange br = parse::getParameterBitrange(parameter);
	string argumentBinStr = extractBitrange(binStr, br);
	if(parse::parameterIsGPRegister(parameter)){
		return parse::binStrToUnsignedDecInt(argumentBinStr);
	}else if(parse::parameterIsFPRegister(parameter)){
		return parse::binStrToUnsignedDecInt(argumentBinStr);
	}else if(parse::parameterIsUnsignedLiteral(parameter)){
		return parse::binStrToUnsignedDecInt(argumentBinStr);
	}else if(parse::parameterIsSignedLiteral(parameter)){
		return parse::binStrToSignedDecInt(argumentBinStr);
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
		ss << decodeArgumentToMnemonic(binStr, parameters[i]);
		if(i < (numParameters - 1)){
			if(!parse::hasParentheses(parameters[i+1])){
				ss << ", ";
			}
		}
	}

	return ss.str();
}

string Decoder::decodeAbnormalInstruction(string binStr, string name, vector<string> parameters, int id, vector<int64_t> &argumentValues){
	stringstream asmString;
	switch(id){
		case 179:
			{
			//EXT rt, rs, pos, size
			string rt = decodeArgumentToMnemonic(binStr, parameters[0]);
			string rs = decodeArgumentToMnemonic(binStr, parameters[1]);
			
			string pos = decodeArgumentToMnemonic(binStr, parameters[2]);
			int pos_int = decodeArgumentToValue(binStr, parameters[2]);

			int msbd_int = decodeArgumentToValue(binStr, parameters[3]);
			int size_int = msbd_int + 1;
			while(size_int < 0){size_int += 32;}
			while(size_int > 31){size_int -= 32;}
			string size = std::to_string(size_int);

			
			argumentValues.push_back(decodeArgumentToValue(binStr, parameters[0]));
			argumentValues.push_back(decodeArgumentToValue(binStr, parameters[1]));
			argumentValues.push_back(pos_int);
			argumentValues.push_back(size_int);

			asmString << name << '\t' << rt << ", " << rs << ", " << pos << ", " << size;
			}
			break;
		case 184:
			{
			//INS rt, rs, pos, size
			string rt = decodeArgumentToMnemonic(binStr, parameters[0]);
			string rs = decodeArgumentToMnemonic(binStr, parameters[1]);
			string pos = decodeArgumentToMnemonic(binStr, parameters[2]);
			int pos_int = decodeArgumentToValue(binStr, parameters[2]);
			int msb_int = decodeArgumentToValue(binStr, parameters[3]);

			int size_int = msb_int - pos_int + 1;
			while(size_int < 0){size_int += 32;}
			while(size_int > 31){size_int -= 32;}
			string size = std::to_string(size_int);

			argumentValues.push_back(decodeArgumentToValue(binStr, parameters[0]));
			argumentValues.push_back(decodeArgumentToValue(binStr, parameters[1]));
			argumentValues.push_back(pos_int);
			argumentValues.push_back(size_int);

			asmString << name << '\t' << rt << ", " << rs << ", " << pos << ", " << size;

			}
			break;
	}
	return asmString.str();
}




















