#include "Encoder.hpp"

#include "mnemonics.hpp"
#include "parse.hpp"

#include <bitset>
#include <cassert>
#include <iostream>
#include <tuple>

//	Constructors
Encoder::Encoder(InstructionDataBank* bank) : resolver(bank) {}

Encoder::~Encoder(){}

//	public Methods
Instruction* Encoder::encode(string asmString){
	Instruction* retInstruction = new Instruction();
	retInstruction->id = resolver.getInstructionData(asmString);
	if(retInstruction->id == NULL){delete retInstruction; return NULL;}
	
	retInstruction->asmString = asmString;
	
	string tmpBinString = retInstruction->id->getFull();
	
	vector<string> asmTokens = parse::tokenizeInstruction(asmString);
	asmTokens.erase(asmTokens.begin());	//remove instruction mnemonic from tokenized vector so it's just args
	
	vector<string> args = retInstruction->id->getArguments();

	if(retInstruction->id->isEncodedNormally()){
		for(int i=0; i<asmTokens.size(); i++){
			if(args[i][0] == '('){
				args[i] = args[i].substr(1, args[i].length() - 2);
			}
			tmpBinString = encodeArgument(tmpBinString, args[i], asmTokens[i]);
		}
	}else{
		//
		//ABNORMAL ENCODING!!
		//
		int instructionID = retInstruction->id->getId();
		switch(instructionID){

			case 152:
				{
				//CLO rd, rs
				tmpBinString = encodeArgument(tmpBinString, args[0], asmTokens[0]);
				tmpBinString = encodeArgument(tmpBinString, args[0], "$rt");
				tmpBinString = encodeArgument(tmpBinString, args[1], asmTokens[1]);
				}
				break;
			case 153:
				{
				//CLZ rd, rs
				tmpBinString = encodeArgument(tmpBinString, args[0], asmTokens[0]);
				tmpBinString = encodeArgument(tmpBinString, args[0], "$rt");
				tmpBinString = encodeArgument(tmpBinString, args[1], asmTokens[1]);
				}
				break;
			case 179:
				{
				//EXT rt, rs, pos, size
				tmpBinString = encodeArgument(tmpBinString, args[0], asmTokens[0]);
				tmpBinString = encodeArgument(tmpBinString, args[1], asmTokens[1]);
				tmpBinString = encodeArgument(tmpBinString, args[2], asmTokens[2]);

				int case179_size = getArgumentValue(asmTokens[3]);
				int case179_msbd = (case179_size == 0)? (32) : (case179_size-1);
				tmpBinString = encodeArgument(tmpBinString, args[3], std::to_string(case179_msbd));
				}
				break;
			case 184:
				{
				//INS rt, rs, pos, size
				tmpBinString = encodeArgument(tmpBinString, args[0], asmTokens[0]);
				tmpBinString = encodeArgument(tmpBinString, args[1], asmTokens[1]);

				int case184_pos = getArgumentValue(asmTokens[2]);
				int case184_size = getArgumentValue(asmTokens[3]);
				int case184_msb = case184_pos + case184_size - 1;
				if(case184_msb + 1 > 32){case184_msb -= 32;}
				tmpBinString = encodeArgument(tmpBinString, args[2], std::to_string(case184_msb));
				
				tmpBinString = encodeArgument(tmpBinString, args[3], asmTokens[3]);
				}
				break;
			case 227:
				{
				//MFC2, rt, Impl, sel
				cout << "Error[Instruction* Encoder::encode(string asmString)]: unrecognized instruction \"MFC2, rt, Impl, sel\" - how to handle \"sel\" field?";
				getchar();
				}
				break;
			case 230: 
				{
				//MFHC2, rt, Impl, sel
				cout << "Error[Instruction* Encoder::encode(string asmString)]: unrecognized instruction \"MFHC2, rt, Impl, sel\" - how to handle \"sel\" field?";
				getchar();
				}
				break;
			case 261:
				{
				//MTC2, rt, Impl, sel
				cout << "Error[Instruction* Encoder::encode(string asmString)]: unrecognized instruction \"MTC2, rt, Impl, sel\" - how to handle \"sel\" field?";
				getchar();
				}
				break;
			case 264:
				{
				//MTHC2, rt, Impl, sel
				cout << "Error[Instruction* Encoder::encode(string asmString)]: unrecognized instruction \"MTHC2, rt, Impl, sel\" - how to handle \"sel\" field?";
				getchar();
				}
				break;
			default:
				cout << "Error[Instruction* Encoder::encode(string asmString)]: unrecognized \"abnormal\" instruction";
				getchar();
				break;
		}
	}

	tmpBinString = parse::replaceChar(tmpBinString, 'x', DONTCAREREPLACEMENT);

	retInstruction->binString = tmpBinString;
	retInstruction->bin = parse::binStrToSignedDecInt(tmpBinString);

	return retInstruction;
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


//	private Methods
int Encoder::getArgumentValue(string argument){
	if(argument[0] == '$'){
		if(argument[1] == 'f'){
			if(argument[2] == 'p'){
				return 30;
			}else{
				return mnemonics::getFPRegIndex(argument);
			}
		}else{
			return mnemonics::getGPRegIndex(argument);
		}
	}else{
		return atoi(argument.c_str());
	}
}


string Encoder::encodeValueAtBitrange(string instruction, bitRange parameter, int argument){
	instruction = setBitrange(instruction, parse::decIntToBinStr(argument), parameter.first, parameter.second);
	return instruction;
}

string Encoder::encodeArgument(string instruction, string parameter, string argument){
	bitRange parameterBitRange = mnemonics::getBitRangeFromParameter(parameter);
	int argumentValue = getArgumentValue(argument);
	instruction = encodeValueAtBitrange(instruction, parameterBitRange, argumentValue);

	return instruction;
}


