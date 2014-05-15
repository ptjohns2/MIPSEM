#include "Decoder.hpp"
#include "stringManip.hpp"
#include "mnemonics.hpp"
#include <cassert>


Decoder::Decoder()
	: resolver()
{

}

Decoder::Decoder(InstructionDataBank* bank)
	: resolver(bank)
{

}

Decoder::~Decoder()
{

}


Instruction* Decoder::decode(instr i){
	//



	//FIX WEIRD INSTRUTIONS WHERE YOU ADD VALUES TO FIELD



	//
	Instruction* retInstruction = new Instruction();
	retInstruction->id = resolver.getInstructionData(i);
	if(retInstruction->id == NULL){delete retInstruction; return NULL;}

	retInstruction->bin = i;

	string binStr = stringManip::decIntToBinStr(i);
	retInstruction->binString = binStr;

	vector<string> instrArgs = retInstruction->id->getArguments();
	int numArgs = 0;
	for(int i=0; i<instrArgs.size(); i++){
		if(instrArgs[i] != "_"){
			numArgs++;
		}
	}
	stringstream asmString;
	asmString << retInstruction->id->getName() << ((numArgs > 0)? "\t" : "");

	for(int i=0; i<instrArgs.size(); i++){
		if(instrArgs[i] == "_"){break;}
		string tmpArg = decodeArgument(binStr, instrArgs[i]);
		asmString << tmpArg;
		if(i<numArgs-1){asmString << ", ";}
	}

	retInstruction->asmString = asmString.str();

	return retInstruction;
}


string Decoder::decodeArgument(string binStr, string parameter){
	if(parameter[0] == '('){
		parameter = parameter.substr(1, parameter.length() - 1 - 1);
	}

	bitRange argBitrange = mnemonics::getBitRangeFromField(parameter);
	string argstr;
	int argval;
	argstr = extractBitrange(binStr, argBitrange);
	if(parameter[0] == '.'){
		argval = stringManip::binStrToSignedDecInt(argstr);
	}else{
		argval = stringManip::binStrToDecInt(argstr);
	}

	stringstream ss, tmpArgument;
	ss << parameter;

	if(parameter[0] == '$'){
		if(parameter[1] == 'f'){
			tmpArgument << mnemonics::getFPRegName(argval);
		}else{
			tmpArgument << mnemonics::getGPRegName(argval);
		}
	}else{
		tmpArgument << argval;
	}
	
	return tmpArgument.str();
}




string Decoder::extractBitrange(string value, bitRange range){
	return extractBitrange(value, range.first, range.second);
}

string Decoder::extractBitrange(string value, unsigned int start, unsigned int end){
	int valueStart = value.length() - start - 1;
	int segmentSize = start - end + 1;
	string retVal = value.substr(valueStart, segmentSize);
	return retVal;
}
















