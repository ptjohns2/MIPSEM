#include "Disassembler.hpp"
#include "stringManip.hpp"
#include "mnemonics.hpp"
#include "decode.hpp"
#include <cassert>


Disassembler::Disassembler()
	: resolver()
{

}

Disassembler::Disassembler(InstructionDataBank* bank)
	: resolver(bank)
{

}

Disassembler::~Disassembler()
{

}


Instruction* Disassembler::disassemble(instr i){
	//



	//FIX WEIRD INSTRUTIONS WHERE YOU ADD VALUES TO FIELD



	//
	Instruction* retInstruction = new Instruction();
	retInstruction->id = resolver.getInstructionData(i);
	//assert(retInstruction->id != NULL);
	if(retInstruction->id == NULL){delete retInstruction; return NULL;}

	retInstruction->bin = i;

	string binStr = stringManip::decIntToBinStr(i);
	retInstruction->binString = binStr;

	int numParameters = 0;
	if(retInstruction->id->getPos1() != "_"){numParameters++;}
	if(retInstruction->id->getPos2() != "_"){numParameters++;}
	if(retInstruction->id->getPos3() != "_"){numParameters++;}
	if(retInstruction->id->getPos4() != "_"){numParameters++;}
	
	stringstream asmString;
	string tmpArg;
	asmString << retInstruction->id->getName() << ((numParameters > 0)? "\t" : "");

	if(numParameters > 0){
		tmpArg = decodeArgument(binStr, retInstruction->id->getPos1());
		asmString << ((tmpArg != "")? tmpArg : "");
	}if(numParameters > 1){
		tmpArg = decodeArgument(binStr, retInstruction->id->getPos2());
		asmString << ((tmpArg != "")? ", " + tmpArg : "");
	}if(numParameters > 2){
		tmpArg = decodeArgument(binStr, retInstruction->id->getPos3());
		asmString << ((tmpArg != "")? ", " + tmpArg : "");
	}if(numParameters > 3){
		tmpArg = decodeArgument(binStr, retInstruction->id->getPos4());
		asmString << ((tmpArg != "")? ", " + tmpArg : "");
	}

	retInstruction->asmString = asmString.str();

	return retInstruction;
}


string Disassembler::decodeArgument(string binStr, string parameter){
	pair<bitRange, bitRange> argBitrange = mnemonics::getArgumentFieldBitRanges(parameter);
	string arg1str, arg2str;
	int arg1val, arg2val;
	arg1str = decode::extractBitrange(binStr, argBitrange.first);
	if(parameter[0] == '.'){
		arg1val = stringManip::binStrToSignedDecInt(arg1str);
	}else{
		arg1val = stringManip::binStrToDecInt(arg1str);
	}
	if(argBitrange.second.first != -1){
		arg2str = decode::extractBitrange(binStr, argBitrange.second);
		if(parameter[0] == '.'){
			arg2val = stringManip::binStrToSignedDecInt(arg2str);
		}else{
			arg2val = stringManip::binStrToDecInt(arg2str);
		}
	}

	stringstream ss, tmpArgument;
	ss << parameter;

	if(stringManip::contains(parameter, "(") != -1){
		getline(ss, arg1str, '(');
		getline(ss, arg2str, ')');
	}else{
		arg1str = parameter;
	}

	if(arg1str[0] == '$'){
		if(arg1str[1] == 'f'){
			tmpArgument << mnemonics::getFPRegName(arg1val);
		}else{
			tmpArgument << mnemonics::getGPRegName(arg1val);
		}
	}else{
		tmpArgument << arg1val;
	}
	
	if(arg2str != ""){
		tmpArgument << "(";
		if(arg2str[0] == '$'){
			if(arg2str[1] == 'f'){
				tmpArgument << mnemonics::getFPRegName(arg2val);
			}else{
				tmpArgument << mnemonics::getGPRegName(arg2val);
			}
		}else{
			tmpArgument << arg2val;
		}
		tmpArgument << ")";
	}


	string retStr = tmpArgument.str();
	return retStr;
}




















