#include "InstructionData.hpp"
#include "stringManip.hpp"
#include "StringResolver.hpp"
#include <sstream>
#include <cassert>
#include <algorithm>
using namespace std;

//class InstructionData
//	Constructors
InstructionData::InstructionData()
{
	id = 0x0;
}


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

	string tmpAbnormalEncoding;
	getline(ss, tmpAbnormalEncoding, '\t');
	this->abnormalEncoding = (tmpAbnormalEncoding[0] == '1')? true : false;

	this->full = this->opcode + this->fields;
	this->hashableName = generateHashableName(this->name, this->arguments);

	assert(opcode.length() == 6 && fields.length() == 26 && full.length() == 32);
}

InstructionData::~InstructionData()
{
	//nothing on heap
}

//	public Methods
string InstructionData::getName(){return name;}
string InstructionData::getFormat(){return format;}
string InstructionData::getOpcode(){return opcode;}
string InstructionData::getFields(){return fields;}
vector<string> InstructionData::getArguments(){return arguments;}
string InstructionData::getFull(){return full;}
string InstructionData::getHashableName(){return hashableName;}


bool InstructionData::bitIsMatch(string bitStr){
	//Test funct first
	for(int i=26; i<32; i++){
		if(full[i] != 'x'){
			if(full[i] != bitStr[i]){
				return false;
			}
		}
	}
	//Now test the rest left to right
	for(int i=6; i<26; i++){
		if(full[i] != 'x'){
			if(full[i] != bitStr[i]){
				return false;
			}
		}
	}
	//Test opcode  last since binary search trees binned by opcode
	for(int i=0; i<6; i++){
		//If opcode char here is a don't care 'x', skip this test
		if(full[i] != 'x'){
			if(full[i] != bitStr[i]){
				return false;
			}
		}
	}
	//If none of these conditions failed, return true for a match
	return true;
}

bool InstructionData::stringIsMatch(string instructionString){
	string hashableString = StringResolver::instructionStringToHashableString(instructionString);
	return this->hashableName == hashableString;
}

string InstructionData::generateHashableName(string name, vector<string> arguments){
	ostringstream oss;
	oss << "@" << name << ":";

	for(int i=0; i<arguments.size(); i++){
		string tmpArg = arguments[i];
		if(tmpArg != "_"){
			int argStart = (tmpArg[0] == '(')? 1 : 0;

			if(argStart == 1){oss << "(";}
			oss << ((tmpArg[argStart] == '$')? '$' : '.');
			if(argStart == 1){oss << ")";}
		}
	}

	string tmpHashable = oss.str();
	std::transform(tmpHashable.begin(), tmpHashable.end(), tmpHashable.begin(), ::tolower);
	return tmpHashable;
}

