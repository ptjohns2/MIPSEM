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
	this->id = atoi(tmpStr.c_str());

	getline(ss, this->name, '\t');
	getline(ss, this->format, '\t');

	getline(ss, this->opcode, '\t');
	getline(ss, this->fields, '\t');
	
	string pos1, pos2, pos3, pos4;
	getline(ss, pos1, '\t');
	getline(ss, pos2, '\t');
	getline(ss, pos3, '\t');
	getline(ss, pos4, '\t');
	this->arguments.push_back(pos1);
	this->arguments.push_back(pos2);
	this->arguments.push_back(pos3);
	this->arguments.push_back(pos4);

	string tmpNormalEncoding;
	getline(ss, tmpNormalEncoding, '\t');
	this->normalEncoding = (tmpNormalEncoding[0] == '1')? true : false;

	string tmpNormalDecoding;
	getline(ss, tmpNormalDecoding, '\t');
	this->normalDecoding = (tmpNormalDecoding[0] == '1')? true : false;

	this->full = this->opcode + this->fields;
	
	assert(opcode.length() == 6 && fields.length() == 26 && full.length() == 32);
}

InstructionData::~InstructionData()
{
	//nothing on heap
}

//	public Methods
int InstructionData::getId(){return id;}
string InstructionData::getName(){return name;}
string InstructionData::getFormat(){return format;}
string InstructionData::getOpcode(){return opcode;}
string InstructionData::getFields(){return fields;}
vector<string> InstructionData::getArguments(){return arguments;}
bool InstructionData::isEncodedNormally(){return normalEncoding;}
bool InstructionData::isDecodedNormally(){return normalDecoding;}
string InstructionData::getFull(){return full;}


