#include "InstructionData.hpp"
#include "decode.hpp"
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

	name = "";
	format = "";

	opcode = "";
	fields = "";

	pos1 = "";
	pos2 = "";
	pos3 = "";
	pos4 = "";


	full = "";
	hashableName = "";
}

InstructionData::InstructionData
	(
		int id,
		string name, 
		string format, 
		string opcode,
		string fields,
		string pos1,
		string pos2, 
		string pos3,
		string pos4
	)
{
	this->id = id;

	this->name = name;
	this->format = format;

	this->opcode = opcode;
	this->fields = fields;

	this->pos1 = pos1;
	this->pos2 = pos2;
	this->pos3 = pos3;
	this->pos4 = pos4;

	
	this->full = opcode + fields;
	this->hashableName = generateHashableName(this->name, this->pos1, this->pos2, this->pos3, this->pos4);

	
	assert(opcode.length() == OPCODESIZE && fields.length() == 26 && full.length() == INSTRUCTIONSIZE);
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
	
	getline(ss, this->pos1, '\t');
	getline(ss, this->pos2, '\t');
	getline(ss, this->pos3, '\t');
	getline(ss, this->pos4, '\t');

	this->full = this->opcode + this->fields;
	this->hashableName = generateHashableName(this->name, this->pos1, this->pos2, this->pos3, this->pos4);

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
string InstructionData::getPos1(){return pos1;}
string InstructionData::getPos2(){return pos2;}
string InstructionData::getPos3(){return pos3;}
string InstructionData::getPos4(){return pos4;}
string InstructionData::getFull(){return full;}
string InstructionData::getHashableName(){return hashableName;}


bool InstructionData::bitIsMatch(string bitStr){
	//Test opcode first since it's most likely to be non-matching
	for(int i=0; i<6; i++){
		//If opcode char here is a don't care 'x', skip this test
		if(full[i] != 'x'){
			if(full[i] != bitStr[i]){
				return false;
			}
		}
	}
	//Test funct next
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
	//If none of these conditions failed, return true for a match
	return true;
}

bool InstructionData::stringIsMatch(string instructionString){
	string hashableString = StringResolver::instructionStringToHashableString(instructionString);
	return this->hashableName == hashableString;
}

string InstructionData::generateHashableName(string name, string pos1, string pos2, string pos3, string pos4){
	ostringstream oss;
	oss << "@" << name << ":";

	if(pos1 != "_"){
		if(pos1[0] == '$'){
			oss << '$';
		}else{
			oss << '.';
		}
		int i = stringManip::contains(pos1, "(");
		if(i != -1){
			oss << "(" << pos1[i+1] << ")";
		}
	}
	if(pos2 != "_"){
		if(pos2[0] == '$'){
			oss << '$';
		}else{
			oss << '.';
		}
		int i = stringManip::contains(pos2, "(");
		if(i != -1){
			oss << "(" << pos2[i+1] << ")";
		}
	}
	if(pos3 != "_"){
		if(pos3[0] == '$'){
			oss << '$';
		}else{
			oss << '.';
		}
		int i = stringManip::contains(pos3, "(");
		if(i != -1){
			oss << "(" << pos3[i+1] << ")";
		}
	}
	if(pos4 != "_"){
		if(pos4[0] == '$'){
			oss << '$';
		}else{
			oss << '.';
		}
		int i = stringManip::contains(pos4, "(");
		if(i != -1){
			oss << "(" << pos4[i+1] << ")";
		}
	}

	string tmpHashable = oss.str();
	std::transform(tmpHashable.begin(), tmpHashable.end(), tmpHashable.begin(), ::tolower);
	return tmpHashable;
}



string InstructionData::toString(){
	//name (format) [................................]
	ostringstream oss;
	oss << name << "\t" << format << "\t";
	oss << "(" << hashableName << ")" << '\t';
	for(int i=0; i<full.size()-4; i+=4){
		oss << full[i] << full[i+1] << full[i+2] << full[i+3];
	}

	return oss.str();
}


//	private Methods