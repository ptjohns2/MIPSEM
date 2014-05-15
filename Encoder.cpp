#include "Encoder.hpp"
#include <cassert>
#include "mnemonics.hpp"
#include "stringManip.hpp"
#include <bitset>
#include <tuple>

Encoder::Encoder() : resolver() {}

Encoder::Encoder(InstructionDataBank* bank) : resolver(bank) {}

Encoder::~Encoder() {}


Instruction* Encoder::encode(string asmString){
	//



	//FIX WEIRD INSTRUTIONS WHERE YOU ADD VALUES TO FIELD



	//
	asmString = stringManip::sanitizeInstruction(asmString);

	Instruction* retInstruction = new Instruction();
	retInstruction->id = resolver.getInstructionData(asmString);
	if(retInstruction->id == NULL){delete retInstruction; return NULL;}

	retInstruction->asmString = asmString;
	
	string tmpBinString = retInstruction->id->getFull();
	
	vector<string> asmTokens = stringManip::tokenizeInstruction(asmString);
	asmTokens.erase(asmTokens.begin());	//remove instruction mnemonic from tokenized vector so it's just args
	
	vector<string> args = retInstruction->id->getArguments();
	for(int i=0; i<asmTokens.size(); i++){
		if(args[i][0] == '('){
			args[i] = args[i].substr(1, args[i].length() - 2);
		}
		tmpBinString = encodeArgument(tmpBinString, args[i], asmTokens[i]);
	}

	//OPTIONAL
	///*
	tmpBinString = stringManip::replaceChar(tmpBinString, 'x', DONTCAREREPLACEMENT);
	//*/

	retInstruction->binString = tmpBinString;
	retInstruction->bin = stringManip::binStrToDecInt(tmpBinString);

	return retInstruction;
}


int Encoder::getArgumentValue(string argument){
	if(argument[0] == '$'){
		if(argument[1] == 'f'){
			if(argument[2] == 'p'){
				return 30;
			}else{
				return mnemonics::getFPRegField(argument);
			}
		}else{
			return mnemonics::getGPRegField(argument);
		}
	}else{
		return atoi(argument.c_str());
	}
}


string Encoder::encodeValueAtBitrange(string instruction, bitRange parameter, int argument){
	instruction = setBitrange(instruction, stringManip::decIntToBinStr(argument), parameter.first, parameter.second);
	return instruction;
}

string Encoder::encodeArgument(string instruction, string parameter, string argument){
	bitRange parameterBitRange = mnemonics::getBitRangeFromField(parameter);
	int argumentValue = getArgumentValue(argument);
	instruction = encodeValueAtBitrange(instruction, parameterBitRange, argumentValue);

	return instruction;
}






string Encoder::setBitrange(string instruction, string value, bitRange range){
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

