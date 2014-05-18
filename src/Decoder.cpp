#include "Decoder.hpp"

#include "mnemonics.hpp"
#include "parse.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

//	Constructors
Decoder::Decoder(InstructionDataBank* bank)	: resolver(bank){}

Decoder::~Decoder(){}

//	public Methods
Instruction* Decoder::decode(instr i){
	//
	//FIX WEIRD INSTRUTIONS WHERE YOU ADD VALUES TO FIELD
	//
	Instruction* retInstruction = new Instruction();
	retInstruction->id = resolver.getInstructionData(i);
	if(retInstruction->id == NULL){delete retInstruction; return NULL;}

	retInstruction->bin = i;

	string binStr = parse::decIntToBinStr(i);
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

	if(retInstruction->id->isDecodedNormally()){
		for(int i=0; i<instrArgs.size(); i++){
			if(instrArgs[i] == "_"){break;}
			string tmpArg = decodeArgument(binStr, instrArgs[i]);
			asmString << tmpArg;
			if(i<numArgs-1){asmString << ", ";}
		}
	}else{
		//
		//ABNORMAL DECODING!!
		//
		int instructionID = retInstruction->id->getId();
		switch(instructionID){

			case 179:
				{
				//EXT rt, rs, pos, size
				string case179_rt = decodeArgument(binStr, instrArgs[0]);
				string case179_rs = decodeArgument(binStr, instrArgs[1]);

				string case179_msbd = decodeArgument(binStr, instrArgs[2]);
				int case179_msbd_int = atoi(case179_msbd.c_str());
				int case179_size_int = (case179_msbd_int == 32)? (0) : (case179_msbd_int + 1);
				string case179_size = std::to_string(case179_size_int);

				string case179_pos = decodeArgument(binStr, instrArgs[3]);

				asmString << case179_rt << ", " << case179_rs << ", " << case179_pos << ", " << case179_size;
				}
				break;
			case 184:
				{
				//INS rt, rs, pos, size
				string case184_rt = decodeArgument(binStr, instrArgs[0]);
				string case184_rs = decodeArgument(binStr, instrArgs[1]);
				
				string case184_msb = decodeArgument(binStr, instrArgs[2]);
				int case184_msb_int = atoi(case184_msb.c_str());
				string case184_pos, case184_lsb = decodeArgument(binStr, instrArgs[3]);
				case184_pos = case184_lsb;
				int case184_pos_int = atoi(case184_lsb.c_str());
				int case184_size_int = case184_msb_int - case184_pos_int + 1;
				string case184_size = std::to_string(case184_size_int);

				asmString << case184_rt << ", " << case184_rs << ", " << case184_pos << ", " << case184_size;
				
				}
				break;
			case 227:
				{
				//MFC2, rt, Impl, sel
				cout << "Error[Instruction* Decoder::decode(string asmString)]: unrecognized instruction \"MFC2, rt, Impl, sel\" - how to handle \"sel\" field?";
				getchar();
				}
				break;
			case 230: 
				{
				//MFHC2, rt, Impl, sel
				cout << "Error[Instruction* Decoder::decode(string asmString)]: unrecognized instruction \"MFHC2, rt, Impl, sel\" - how to handle \"sel\" field?";
				getchar();
				}
				break;
			case 261:
				{
				//MTC2, rt, Impl, sel
				cout << "Error[Instruction* Decoder::decode(string asmString)]: unrecognized instruction \"MTC2, rt, Impl, sel\" - how to handle \"sel\" field?";
				getchar();
				}
				break;
			case 264:
				{
				//MTHC2, rt, Impl, sel
				cout << "Error[Instruction* Decoder::decode(string asmString)]: unrecognized instruction \"MTHC2, rt, Impl, sel\" - how to handle \"sel\" field?";
				getchar();
				}
				break;
			default:
				cout << "Error[Instruction* Decoder::decode(string asmString)]: unrecognized \"abnormal\" instruction";
				getchar();
				break;
		}

	}

	retInstruction->asmString = asmString.str();

	return retInstruction;
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


//	private Methods
string Decoder::decodeArgument(string binStr, string parameter){
	if(parameter[0] == '('){
		parameter = parameter.substr(1, parameter.length() - 1 - 1);
	}

	bitRange argBitrange = mnemonics::getBitRangeFromParameter(parameter);
	string argstr;
	int argval;
	argstr = extractBitrange(binStr, argBitrange);
	if(parameter[0] == '.'){
		argval = parse::binStrToSignedDecInt(argstr);
	}else{
		argval = parse::binStrToUnsignedDecInt(argstr);
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



















