#include "Encoder.hpp"

#include "Decoder.hpp"
#include "Exceptions.hpp"
#include "Parser.hpp"

#include <bitset>
#include <cassert>
#include <iostream>
#include <tuple>

//	Constructors
Encoder::Encoder(InstructionDataBank* bank, Decoder* decoder) 
	:	resolver(bank), parser(){
	this->decoder = decoder;	
}

Encoder::~Encoder(){}

//	public Methods
Instruction Encoder::buildInstruction(string asmString){
	InstructionData* id = resolver.getInstructionData(asmString);
	if(id == NULL){
		//EXCEPTION
		string error = "Unable to encode instruction \""
			+ asmString
			+ "\"";
		throw AssemblerException(NULL, error);
	}

	vector<string> arguments = Parser::tokenizeInstruction(asmString);
	arguments.erase(arguments.begin());

	instr bin;
	if(id->isEncodedNormally()){
		bin = encodeInstruction(id, arguments);
	}else{
		bin = encodeAbnormalInstruction(id, arguments);
	}

	return decoder->buildInstruction(bin);
}

instr Encoder::setBitrange(instr bin, uint32_t value, unsigned int start, unsigned int end){
	//extract clean value (right #bits) from value
	uint32_t cleanValue = Decoder::extractBitrangeUnsigned(value, start - end, 0);
	//shift cleanValue to position
	cleanValue = cleanValue << end;

	//generate positive mask "start" bits long
	instr mask = (1 << (start - end + 1)) - 1;
	//shift mask to position
	mask = mask << end;
	//flip mask
	mask = ~mask;

	//clear bits under mask on instruction
	instr newInstr = bin & mask;
	//set cleanValue as cleared bits of newInstr
	newInstr = newInstr | cleanValue;

	return newInstr;
}
instr Encoder::setBitrange(instr bin, uint32_t value, bitrange br){
	return setBitrange(bin, value, br.first, br.second);
}

//	private Methods
instr Encoder::encodeArgument(instr bin, string argument, bitrange br){
	int32_t parameterValue = parser.getTokenValue(argument);
	instr encodedInstr = setBitrange(bin, parameterValue, br);
	return encodedInstr;
}

instr Encoder::encodeInstruction(InstructionData* id, vector<string> arguments){
	instr newInstruction = id->getFace();
	for(int i=0; i<arguments.size(); i++){
		newInstruction = encodeArgument(newInstruction, arguments[i], id->getParameterBitrange(i));
	}
	return newInstruction;
}

instr Encoder::encodeAbnormalInstruction(InstructionData* id, vector<string> arguments){
	instr newInstruction = id->getFace();
	switch(id->getID()){
		case 152:
			{
			//CLO rd, rs
			newInstruction = encodeArgument(newInstruction, arguments[0], id->getParameterBitrange(0));
			bitrange rt_br;
			rt_br.first = 20;
			rt_br.second = 16;
			newInstruction = encodeArgument(newInstruction, arguments[0], rt_br);
			newInstruction = encodeArgument(newInstruction, arguments[1], id->getParameterBitrange(0));
			}
			break;
		case 153:
			{
			//CLZ rd, rs
				newInstruction = encodeArgument(newInstruction, arguments[0], id->getParameterBitrange(0));
			bitrange rt_br;
			rt_br.first = 20;
			rt_br.second = 16;
			newInstruction = encodeArgument(newInstruction, arguments[0], rt_br);
			newInstruction = encodeArgument(newInstruction, arguments[1], id->getParameterBitrange(1));
			}
			break;
		case 179:
			{
			//EXT rt, rs, pos, size
				newInstruction = encodeArgument(newInstruction, arguments[0], id->getParameterBitrange(0));
			newInstruction = encodeArgument(newInstruction, arguments[1], id->getParameterBitrange(1));
			newInstruction = encodeArgument(newInstruction, arguments[2], id->getParameterBitrange(2));

			int size = parser.literals.getLiteralValue(arguments[3]);
			//negatives will be handled since only 5 lsb of binstr
			int msbd = size - 1;
			newInstruction = encodeArgument(newInstruction, std::to_string(msbd), id->getParameterBitrange(3));
			}
			break;
		case 184:
			{
			//INS rt, rs, pos, size
			newInstruction = encodeArgument(newInstruction, arguments[0], id->getParameterBitrange(0));
			newInstruction = encodeArgument(newInstruction, arguments[1], id->getParameterBitrange(1));

			int pos = parser.literals.getLiteralValue(arguments[2]);
			int size = parser.literals.getLiteralValue(arguments[3]);
			//negatives will be handled since only 5 lsb of binstr
			int msb = pos + size - 1;
		
			newInstruction = encodeArgument(newInstruction, arguments[2], id->getParameterBitrange(2));
			newInstruction = encodeArgument(newInstruction, std::to_string(msb), id->getParameterBitrange(3));
			}
			break;
		default:
			{

			}
	}
	
	return newInstruction;
}









