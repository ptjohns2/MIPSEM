#include "InstructionData.hpp"

#include "parse.hpp"
#include "StringResolver.hpp"

#include <cassert>
#include <sstream>

using namespace std;

//class InstructionData
//	Constructors
InstructionData::InstructionData(string info){
	stringstream ss(info);
	string tmpStr;

	getline(ss, tmpStr, '\t');
	this->instructionID = atoi(tmpStr.c_str());

	getline(ss, this->name, '\t');
	getline(ss, this->format, '\t');

	getline(ss, this->opcode, '\t');
	getline(ss, this->fields, '\t');
	
	string pos1, pos2, pos3, pos4;
	getline(ss, pos1, '\t');
	getline(ss, pos2, '\t');
	getline(ss, pos3, '\t');
	getline(ss, pos4, '\t');
	this->parameters.push_back(pos1);
	this->parameters.push_back(pos2);
	this->parameters.push_back(pos3);
	this->parameters.push_back(pos4);

	string tmpNormalEncoding;
	getline(ss, tmpNormalEncoding, '\t');
	this->normalEncoding = (tmpNormalEncoding[0] == '1')? true : false;

	string tmpNormalDecoding;
	getline(ss, tmpNormalDecoding, '\t');
	this->normalDecoding = (tmpNormalDecoding[0] == '1')? true : false;

	string tmpInstructionChangesPC;
	getline(ss, tmpInstructionChangesPC, '\t');
	this->instructionChangesPC = (tmpInstructionChangesPC[0] == '1')? true : false;

	this->full = this->opcode + this->fields;
	
	assert(opcode.length() == 6 && fields.length() == 26 && full.length() == 32);
}

InstructionData::~InstructionData()
{
	//nothing on heap
}

//	public Methods
int InstructionData::getInstructionID()const{return instructionID;}
string InstructionData::getName()const{return name;}
string InstructionData::getFormat()const{return format;}
string InstructionData::getOpcode()const{return opcode;}
string InstructionData::getFields()const{return fields;}
vector<string> InstructionData::getParameters()const{return parameters;}
bool InstructionData::isEncodedNormally()const{return normalEncoding;}
bool InstructionData::isDecodedNormally()const{return normalDecoding;}
bool InstructionData::changesPC()const{return instructionChangesPC;}
string InstructionData::getFull()const{return full;}

