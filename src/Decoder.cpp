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
		Instruction jnk = buildInstruction(0x0);
		return jnk;
	}

	instr bin = parse::binStrToUnsignedDecInt(binStr);

	vector<string> parameters = id->getParameters();
	
	int numArgs = 0;
	for(int i=0; i<parameters.size(); i++){
		if(parameters[i] != "_"){numArgs++;}
	}

	string asmString;
	vector<int> argumentValues;
	if(id->isDecodedNormally()){
		//decode instr
		asmString = decodeInstruction(binStr, id->getName(), parameters);
		//get argument values
		for(int i=0; i<numArgs; i++){
			bitrange br = parse::getParameterBitrange(parameters[i]);
			uint32_t argVal = parse::binStrToUnsignedDecInt(extractBitrange(binStr, br));
			argumentValues.push_back(argVal);
		}
	}else{
		//decode abnormal instr
		argumentValues.clear();
		asmString = decodeAbnormalInstruction(binStr, id->getName(), parameters, id->getInstructionID(), argumentValues);
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
	string cleanParameter = parameter;
	bool hasParentheses = parse::hasParentheses(parameter);
	if(hasParentheses){
		cleanParameter = parse::removeParentheses(parameter);
	}
	bitrange br = parse::getParameterBitrange(cleanParameter);
	string argumentBinStr = extractBitrange(binStr, br);
	string retStr;
	if(parse::parameterIsGPRegister(cleanParameter)){
		retStr = parse::getGPRegisterName(parse::binStrToUnsignedDecInt(argumentBinStr));
	}else if(parse::parameterIsFPRegister(cleanParameter)){
		retStr = parse::getFPRegisterName(parse::binStrToUnsignedDecInt(argumentBinStr));
	}else if(parse::parameterIsUnsignedLiteral(cleanParameter)){
		retStr = std::to_string(parse::binStrToUnsignedDecInt(argumentBinStr));
	}else if(parse::parameterIsSignedLiteral(cleanParameter)){
		retStr = std::to_string(parse::binStrToSignedDecInt(argumentBinStr));
	}
	if(hasParentheses){
		retStr = "(" + retStr + ")";
	}
	return retStr;
}

int Decoder::decodeArgumentToValue(string binStr, string parameter){
	string cleanParameter = parameter;
	cleanParameter = parse::removeParentheses(parameter);
	bitrange br = parse::getParameterBitrange(cleanParameter);
	string argumentBinStr = extractBitrange(binStr, br);
	if(parse::parameterIsGPRegister(cleanParameter)){
		return parse::binStrToUnsignedDecInt(argumentBinStr);
	}else if(parse::parameterIsFPRegister(cleanParameter)){
		return parse::binStrToUnsignedDecInt(argumentBinStr);
	}else if(parse::parameterIsUnsignedLiteral(cleanParameter)){
		return parse::binStrToUnsignedDecInt(argumentBinStr);
	}else if(parse::parameterIsSignedLiteral(cleanParameter)){
		return parse::binStrToSignedDecInt(argumentBinStr);
	}else{
		cout << "Decoder::decodeArgumentToValue error not real param type";
		getchar();
		return 0;
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

string Decoder::decodeAbnormalInstruction(string binStr, string name, vector<string> parameters, int id, vector<int> &argumentValues){
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




















