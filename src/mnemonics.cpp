#include "mnemonics.hpp"
#include <cassert>
#include <sstream>
#include <iostream>


string mnemonics::getGPRegName(ufield num){
	assert(num >= 0 && num < 32);
	return GPRegisterNames[num];
}
int mnemonics::getGPRegField(string name){
	for(int i=0; i<32; i++){
		if(GPRegisterNames[i] == name){
			return i;
		}
	}
	assert(!"registers::getGPRegField name DNE");
}

string mnemonics::getFPRegName(ufield num){
	assert(num >= 0 && num < 32);
	return FPRegisterNames[num];
}
int mnemonics::getFPRegField(string name){
	for(int i=0; i<32; i++){
		if(FPRegisterNames[i] == name){
			return i;
		}
	}
	assert(!"registers::getFPRegField name DNE");
}

bitRange mnemonics::getBitRangeFromField(string fieldName){
	bitRange retBitRange;
	if(fieldName[1] != '['){
		//standard mnemonic not specific range	{$/.}%mnemonic%
		if(fieldName == "$rs" || fieldName == "$fmt"){
			retBitRange.first = 25;
			retBitRange.second = 21;
			return retBitRange;
		}else if(fieldName == "$rt" || fieldName == "$ft"){
			retBitRange.first = 20;
			retBitRange.second = 16;
			return retBitRange;
		}else if(fieldName == "$rd" || fieldName == "$fs"){
			retBitRange.first = 15;
			retBitRange.second = 11;
			return retBitRange;
		}else if(fieldName == ".shamt" || fieldName == "$fd"){
			retBitRange.first = 10;
			retBitRange.second = 6;
			return retBitRange;			
		}else if(fieldName == ".imm"){
			retBitRange.first = 15;
			retBitRange.second = 0;
			return retBitRange;
		}else if(fieldName == ".addr"){
			retBitRange.first = 25;
			retBitRange.second = 0;
			return retBitRange;
		}else{
			cout << "\n\n\n" << fieldName;
			assert(!"invalid field mnemonic - check instructions.txt");
		}
	}else{
		//specific range	{$/.}[%val1%,%val2%]
		string inBrackets = fieldName.substr(2, fieldName.length()-3);
		string num1, num2;
		stringstream ss;
		ss << inBrackets;
	
		getline(ss, num1, ',');
		getline(ss, num2);
		
		retBitRange.first = atoi(num1.c_str());
		retBitRange.second = atoi(num2.c_str());
		return retBitRange;
	}
}



std::string const mnemonics::GPRegisterNames[] = {
	"$zero",
	"$at",
	"$v0", "$v1",
	"$a0", "$a1", "$a2", "$a3",
	"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
	"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
	"$t8", "$t9",
	"$k0", "$k1",
	"$gp",
	"$sp",
	"$fp",
	"$ra"
};

std::string const mnemonics::FPRegisterNames[] = {
	"$f0", "$f1", "$f2", "$f3", "$f4", "$f5", "$f6", "$f7",
	"$f8", "$f9", "$f10", "$f11", "$f12", "$f13", "$f14", "$f15",
	"$f16", "$f17", "$f18", "$f19", "$f20", "$f21", "$f22", "$f23",
	"$f24", "$f25", "$f26", "$f27", "$f28", "$f29", "$f30", "$f31"
};