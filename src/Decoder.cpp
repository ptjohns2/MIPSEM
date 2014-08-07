#include "Decoder.hpp"

#include "Parser.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

//	Constructors
Decoder::Decoder(InstructionDataBank* bank)	: resolver(bank){}

Decoder::~Decoder(){}

//	public Methods
Instruction Decoder::buildInstruction(instr ins){	
	InstructionData* id = resolver.getInstructionData(ins);
	if(id == NULL){
		//TODO: fix
		Instruction jnk = buildInstruction(0x0);
		return jnk;
	}

	string asmString;
	int32_t argumentValues[NUMBER_OF_INSTRUCTION_PARAMETERS];
	if(id->isDecodedNormally()){
		//get argument values
		for(int i=0; i<id->getNumParameters(); i++){
			bitrange br = id->getParameterBitrange(i);
			int32_t argVal = decodeArgumentToValue(ins, id, i);
			argumentValues[i] = argVal;
		}
		for(int i=id->getNumParameters(); i<NUMBER_OF_INSTRUCTION_PARAMETERS; i++){
			argumentValues[i] = 0;
		}
		//decode normal instr
		asmString = decodeInstruction(id, ins);

	}else{
		//decode abnormal instr
		asmString = decodeAbnormalInstruction(id, ins, argumentValues);
	}
	
	Instruction instruction = Instruction(id, asmString, ins, argumentValues);
	return instruction;
}


int32_t Decoder::extractBitrangeUnsigned(instr value, unsigned int start, unsigned int end){
	value = value << (SIZE_BITS_WORD - 1 - start);	/*	shift out high bits	*/
	value = value >> (SIZE_BITS_WORD - 1 - start);	/*	shift back into place	*/
	value = value >> end;		/*	shift out low bits	*/
	return (int32_t)value;
	//return (value & ((1 << start) - 1)) & (value & ~((1 << end) - 1)) >> end;
}
int32_t Decoder::extractBitrangeUnsigned(instr value, bitrange range){
	return extractBitrangeUnsigned(value, range.first, range.second);
}

int32_t Decoder::extractBitrangeSigned(instr value, unsigned int start, unsigned int end){
	int32_t signedValue = (int32_t)(value);
	signedValue = signedValue << (SIZE_BITS_WORD - 1 - start);	/*	shift out high bits	*/
	signedValue = signedValue >> (SIZE_BITS_WORD - 1 - start);	/*	shift back into place	*/
	signedValue = signedValue >> end;		/*	shift out low bits	*/
	return signedValue;
	//return (value & ((1 << start) - 1)) & (value & ~((1 << end) - 1)) >> end;
}
int32_t Decoder::extractBitrangeSigned(instr value, bitrange range){
	return extractBitrangeSigned(value, range.first, range.second);
}

//	private Methods
string Decoder::decodeArgumentToMnemonic(instr ins, InstructionData* id, int parameterNumber){
	bitrange br = id->getParameterBitrange(parameterNumber);
	string retStr;
	if(id->parameterIsGPRegister(parameterNumber)){
		int fieldVal = extractBitrangeUnsigned(ins, br);
		retStr = Parser::getGPRegisterName(fieldVal);
	}else if(id->parameterIsFPRegister(parameterNumber)){
		int fieldVal = extractBitrangeUnsigned(ins, br);
		retStr = Parser::getFPRegisterName(fieldVal);
	}else if(id->parameterIsUnsignedLiteral(parameterNumber)){
		int fieldVal = extractBitrangeUnsigned(ins, br);
		retStr = std::to_string(fieldVal);
	}else if(id->parameterIsSignedLiteral(parameterNumber)){
		int fieldVal = extractBitrangeSigned(ins, br);
		retStr = std::to_string(fieldVal);
	}
	if(id->paramHasParenthises(parameterNumber)){
		retStr = "(" + retStr + ")";
	}
	return retStr;
}

int32_t Decoder::decodeArgumentToValue(instr ins, InstructionData* id, int parameterNumber){
	bitrange br = id->getParameterBitrange(parameterNumber);
	if(id->parameterIsGPRegister(parameterNumber)){
		return extractBitrangeUnsigned(ins, br);
	}else if(id->parameterIsFPRegister(parameterNumber)){
		return extractBitrangeUnsigned(ins, br);
	}else if(id->parameterIsUnsignedLiteral(parameterNumber)){
		return extractBitrangeUnsigned(ins, br);
	}else if(id->parameterIsSignedLiteral(parameterNumber)){
		return extractBitrangeSigned(ins, br);
	}else{
		cout << "int Decoder::decodeArgumentToValue error - invalid argument";
		return 0;
	}
}

string Decoder::decodeInstruction(InstructionData* id, instr ins){
	stringstream ss;
	ss << id->getName();
	if(id->getNumParameters() > 0){ss << '\t';}

	for(int i=0; i<id->getNumParameters(); i++){
		ss << decodeArgumentToMnemonic(ins, id, i);
		if(i < (id->getNumParameters() - 1)){
			if(!id->paramHasParenthises(i+1)){
				ss << ", ";
			}
		}
	}

	return ss.str();
}

string Decoder::decodeAbnormalInstruction(InstructionData* id, instr ins, int32_t argumentValues[NUMBER_OF_INSTRUCTION_PARAMETERS]){
	stringstream asmString;
	switch(id->getID()){
		case 179:
			{
			//EXT rt, rs, pos, size
			string rt = decodeArgumentToMnemonic(ins, id, 0);
			string rs = decodeArgumentToMnemonic(ins, id, 1);
			
			string pos = decodeArgumentToMnemonic(ins, id, 2);
			int pos_int = decodeArgumentToValue(ins, id, 2);

			int msbd_int = decodeArgumentToValue(ins, id, 3);
			int size_int = msbd_int + 1;
			while(size_int < 0){size_int += 32;}
			while(size_int > 31){size_int -= 32;}
			string size = std::to_string(size_int);
			
			argumentValues[0] = decodeArgumentToValue(ins, id, 0);
			argumentValues[1] = decodeArgumentToValue(ins, id, 1);
			argumentValues[2] = pos_int;
			argumentValues[3] = size_int;

			asmString << id->getName() << '\t' << rt << ", " << rs << ", " << pos << ", " << size;
			}
			break;
		case 184:
			{
			//INS rt, rs, pos, size
			string rt = decodeArgumentToMnemonic(ins, id, 0);
			string rs = decodeArgumentToMnemonic(ins, id, 1);
			string pos = decodeArgumentToMnemonic(ins, id, 2);
			int pos_int = decodeArgumentToValue(ins, id, 2);
			int msb_int = decodeArgumentToValue(ins, id, 3);

			int size_int = msb_int - pos_int + 1;
			while(size_int < 0){size_int += 32;}
			while(size_int > 31){size_int -= 32;}
			string size = std::to_string(size_int);

			argumentValues[0] = decodeArgumentToValue(ins, id, 0);
			argumentValues[1] = decodeArgumentToValue(ins, id, 1);
			argumentValues[2] = pos_int;
			argumentValues[3] = size_int;

			asmString << id->getName() << '\t' << rt << ", " << rs << ", " << pos << ", " << size;

			}
			break;
	}
	return asmString.str();
}




















