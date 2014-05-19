#include "mnemonics.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

//	public Methods
bitrange mnemonics::getParameterBitrange(string parameter){
	bitrange retBitrange;
	if(parameter[1] != '['){
		//standard mnemonic not specific range	{$/.}%mnemonic%
		if(parameter == "$rs" || parameter == "$fmt"){
			retBitrange.first = 25;
			retBitrange.second = 21;
		}else if(parameter == "$rt" || parameter == "$ft"){
			retBitrange.first = 20;
			retBitrange.second = 16;
		}else if(parameter == "$rd" || parameter == "$fs"){
			retBitrange.first = 15;
			retBitrange.second = 11;
		}else if(parameter == ".shamt" || parameter == "$fd"){
			retBitrange.first = 10;
			retBitrange.second = 6;	
		}else if(parameter == ".imm"){
			retBitrange.first = 15;
			retBitrange.second = 0;
		}else if(parameter == ".addr"){
			retBitrange.first = 25;
			retBitrange.second = 0;
		}else{
			cout << "\n\n\n" << parameter;
			assert(!"invalid field mnemonic - check instructions.txt");
		}
	}else{
		//specific range	ex. $[20,1]
		string inBrackets = parameter.substr(2, parameter.length()-3);
		stringstream ss;
		ss << inBrackets;
	
		string num1, num2;
		getline(ss, num1, ',');
		getline(ss, num2);
		
		retBitrange.first = atoi(num1.c_str());
		retBitrange.second = atoi(num2.c_str());
	}
	return retBitrange;
}

bool mnemonics::parameterIsRegister(string parameter){
	???
}

bool mnemonics::parameterIsGPRegister(string parameter){
	???
}

string mnemonics::getGPRegisterName(int index){
	assert(index >= 0 && index < 32);
	return GPRegisterNames[index];
}

int mnemonics::getGPRegisterIndex(string parameter){
	for(int i=0; i<32; i++){
		if(GPRegisterNames[i] == parameter){
			return i;
		}
	}
	assert(!"registers::getGPRegIndex name DNE");
}

bool mnemonics::parameterIsFPRegister(string parameter){
	???
}

string mnemonics::getFPRegisterName(int index){
	assert(index >= 0 && index < 32);
	return FPRegisterNames[index];
}
int mnemonics::getFPRegisterIndex(string parameter){
	for(int i=0; i<32; i++){
		if(FPRegisterNames[i] == parameter){
			return i;
		}
	}
	assert(!"registers::getFPRegIndex name DNE");
}

bool mnemonics::parameterIsImmediate(string parameter){
	???
}

bool mnemonics::parameterIsSignedImmediate(string parameter){
	???
}

bool mnemonics::parameterIsUnsignedImmediate(string parameter){
	???
}


int mnemonics::getArgumentValue(string argument){
	if(argument[0] == '$'){
		if(argument[1] == 'f'){
			if(argument[2] == 'p'){
				return 30;
			}else{
				return mnemonics::getFPRegisterIndex(argument);
			}
		}else{
			return mnemonics::getGPRegisterIndex(argument);
		}
	}else{
		return atoi(argument.c_str());
	}
}





//	Members
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