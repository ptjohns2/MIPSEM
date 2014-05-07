#include "Assembler.hpp"
#include <cassert>
#include "mnemonics.hpp"
#include "stringManip.hpp"
#include "encode.hpp"
#include <bitset>
#include <tuple>

Assembler::Assembler() 
	: resolver()
{
	
}

Assembler::Assembler(InstructionDataBank* bank)
	: resolver(bank)
{

}

Assembler::~Assembler()
{

}


Instruction* Assembler::assemble(string asmString){
	//



	//FIX WEIRD INSTRUTIONS WHERE YOU ADD VALUES TO FIELD



	//
	Instruction* retInstruction = new Instruction();
	retInstruction->id = resolver.getInstructionData(asmString);
	assert(retInstruction->id != NULL);
	if(retInstruction->id == NULL){delete retInstruction; return NULL;}

	retInstruction->asmString = asmString;
	
	string tmpBinString = retInstruction->id->getFull();
	
	vector<string> asmTokens = stringManip::tokenizeInstruction(asmString);
	asmTokens.erase(asmTokens.begin());	//remove instruction mnemonic from tokenized vector so it's just args
	
	int numTokens = asmTokens.size();
	if(numTokens > 0){
		tmpBinString = encodeArgument(tmpBinString, retInstruction->id->getPos1(), asmTokens[0]);
	}if(numTokens > 1){
		tmpBinString = encodeArgument(tmpBinString, retInstruction->id->getPos2(), asmTokens[1]);
	}if(numTokens > 2){
		tmpBinString = encodeArgument(tmpBinString, retInstruction->id->getPos3(), asmTokens[2]);
	}if(numTokens > 3){
		tmpBinString = encodeArgument(tmpBinString, retInstruction->id->getPos4(), asmTokens[3]);
	}

	//OPTIONAL
	///*
	if(stringManip::contains(tmpBinString, "x") != -1){
		tmpBinString = stringManip::replace(tmpBinString, 'x', DONTCAREREPLACEMENT);
	}
	//*/

	retInstruction->binString = tmpBinString;
	retInstruction->bin = stringManip::binStrToDecInt(tmpBinString);

	return retInstruction;
}

int Assembler::getArgumentTokenValue(string argument){
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

pair<int, int> Assembler::getArgumentValue(string argument){
	pair<int, int> retVal;
	string argStr1, argStr2;
	stringstream ss;
	ss << argument;

	if(stringManip::contains(argument, "(")){
		getline(ss, argStr1, '(');
		getline(ss, argStr2, ')');
		retVal.first = getArgumentTokenValue(argStr1);
		retVal.second = getArgumentTokenValue(argStr2);
	}else{
		retVal.first = getArgumentTokenValue(argument);
	}
	return retVal;
}


string Assembler::encodeValueAtBitrange(string instruction, pair<bitRange, bitRange> parameter, pair<int, int> argument){
	instruction = encode::setBitrange(instruction, stringManip::decIntToBinStr(argument.first), parameter.first.first, parameter.first.second);
	if(parameter.second.first != -1){
		instruction = encode::setBitrange(instruction, stringManip::decIntToBinStr(argument.second), parameter.second.first, parameter.second.second);
	}
	return instruction;
}

string Assembler::encodeArgument(string instruction, string parameter, string argument){
	pair<bitRange, bitRange> parameterBitRange = mnemonics::getArgumentFieldBitRanges(parameter);
	pair<int, int> argumentValue = getArgumentValue(argument);
	instruction = encodeValueAtBitrange(instruction, parameterBitRange, argumentValue);

	return instruction;
}







