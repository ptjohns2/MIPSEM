#include "InstructionData.hpp"

#include "parse.hpp"
#include "StringResolver.hpp"

#include <cassert>
#include <sstream>

using namespace std;

#define TOKEN_NO_PARAM	'x'
#define TOKEN_GP_REGISTER 'g'
#define TOKEN_FP_REGISTER 'f'
#define TOKEN_SIGNED_LITERAL '-'
#define TOKEN_UNSIGNED_LITERAL '+'



//class InstructionData
//	Constructors
InstructionData::InstructionData(){

}
InstructionData::InstructionData(int id, string name, int opcode, instr face, instr mask, char at1, bool ap1, int asb1, int aeb1, char at2, bool ap2, int asb2, int aeb2, char at3, bool ap3, int asb3, int aeb3, char at4, bool ap4, int asb4, int aeb4, bool normalEncoding, bool normalDecoding, bool instructionChangesPC){
	this->id = id;
	this->name = name;

	this->opcode = opcode;
	this->face = face;
	this->mask = mask;
	
	this->parameterTypes[0] = at1;
	this->parameterTypes[1] = at2;
	this->parameterTypes[2] = at3;
	this->parameterTypes[3] = at4;
	
	this->parameterStartBits[0] = asb1;
	this->parameterStartBits[1] = asb2;
	this->parameterStartBits[2] = asb3;
	this->parameterStartBits[3] = asb4;
	
	this->parameterEndBits[0] = aeb1;
	this->parameterEndBits[1] = aeb2;
	this->parameterEndBits[2] = aeb3;
	this->parameterEndBits[3] = aeb4;

	this->normalEncoding = normalEncoding;
	this->normalDecoding = normalDecoding;
	this->instructionChangesPC = instructionChangesPC;

	int numParameters = 0;
	for(int i=0; i<NUMBER_OF_PARAMETERS; i++){
		if(parameterTypes[i] == TOKEN_NO_PARAM){
			break;
		}
		numParameters++;
	}
	this->numParameters = numParameters;
}	
InstructionData::~InstructionData()
{
	//nothing on heap
}

//	public Methods
int InstructionData::getID()const{return id;}
string InstructionData::getName()const{return name;}
int InstructionData::getOpcode()const{return opcode;}

char InstructionData::getParameterType(int i)const{return parameterTypes[i];}

bool InstructionData::parameterIsLiteral(int i) const{
	return parameterIsSignedLiteral(i) || parameterIsUnsignedLiteral(i);
}
bool InstructionData::parameterIsSignedLiteral(int i)const{
	return parameterTypes[i] == TOKEN_SIGNED_LITERAL;
}
bool InstructionData::parameterIsUnsignedLiteral(int i)const{
	return parameterTypes[i] == TOKEN_UNSIGNED_LITERAL;
}

bool InstructionData::parameterIsRegister(int i) const{
	return parameterIsGPRegister(i) || parameterIsFPRegister(i);
}
bool InstructionData::parameterIsGPRegister(int i) const{
	return parameterTypes[i] == TOKEN_GP_REGISTER;
}
bool InstructionData::parameterIsFPRegister(int i) const{
	return parameterTypes[i] == TOKEN_FP_REGISTER;
}
int InstructionData::getParameterStartBit(int i)const{return parameterStartBits[i];}
int InstructionData::getParameterEndBit(int i)const{return parameterEndBits[i];}
int InstructionData::getNumParameters()const{return numParameters;}

bool InstructionData::isEncodedNormally()const{return normalEncoding;}
bool InstructionData::isDecodedNormally()const{return normalDecoding;}
bool InstructionData::changesPC()const{return instructionChangesPC;}


