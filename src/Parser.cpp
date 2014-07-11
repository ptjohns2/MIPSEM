#include "Parser.hpp"

#include <bitset>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>

#define WHITE_SPACE_STRING (" \t")

Parser::Parser(){
	for(int i=0; i<NUM_GP_REGISTER_NAMES; i++){
		GPRegisterNameMap[GPRegisterNames[i]] = i;
	}
	for(int i=0; i<NUM_FP_REGISTER_NAMES; i++){
		FPRegisterNameMap[FPRegisterNames[i]] = i;
	}
	for(int i=0; i<NUM_DIRECTIVE_NAMES; i++){
		DirectiveNameMap[DirectiveNames[i]] = i;
	}
}
Parser::~Parser(){

}


//	public Methods

string Parser::trimFront(string str){
	if(str == ""){return "";}
	int len = str.length();
	int i = 0;
	while((str[i] == ' ' || str[i] == '\t') && i < len){
		i++;
	}
	if((i == len-1) && (str[i] == '\t' || str[i] == '\t')){return "";}
	return str.substr(i);
}

string Parser::trimEnd(string str){
	if(str == ""){return "";}
	int len = str.length();
	int i = len - 1;
	while((str[i] == ' ' || str[i] == '\t') && i > -1){
		i--;
	}
	if((i == 0) && (str[i] == ' ' || str[i] == '\t')){return "";}
	i++;

	return str.substr(0, i);
}

string Parser::trim(string str){
	return trimEnd(trimFront(str));
}

string Parser::replaceChar(string str, char before, char after){
	for(unsigned int i=0; i<str.length(); i++){
		if(str[i] == before){
			str[i] = after;
		}
	}
	return str;
}

bool Parser::hasParentheses(string str){
	return str[0] == '(' && str[str.length()-1] == ')';
}
string Parser::removeParentheses(string str){
	if(hasParentheses(str)){
		str = str.substr(1, str.length() - 1 - 1);	//1 for each parentheses
	}
	return str;
}

bool Parser::hasTrailingComma(string str){
	return str[str.length() - 1] == ',';
}
string Parser::removeTrailingComma(string str){
	if(hasTrailingComma(str)){
		str = str.substr(0, str.length() - 1);
	}
	return str;
}


bool Parser::isWhiteSpace(char c){
	string whiteSpace = WHITE_SPACE_STRING;
	for(int i=0; i<whiteSpace.length(); i++){
		if(whiteSpace[i] == c){return true;}
	}
	return false;
}

string Parser::sanitizeInstruction(string str){
	int i = 0;
	while(i<str.length() && str[i] != '#'){
		if(str[i] == '\t'){str[i] = ' ';}
		i++;
	}
	string substr = str.substr(0, i);
	return trim(substr);
}

vector<string> Parser::tokenizeInstruction(string str){
	// NAME A1,A2,A3,A4#xxxx
	str = sanitizeInstruction(str);

	stringstream ss(str);

	vector<string> tokensBeforeParenSplit;
	vector<string> tokensAfterParenSplit;

	//tokenize instructions without splitting parenthises
	string tmpStr;
	getline(ss, tmpStr, ' ');	//get instruction name
	tokensBeforeParenSplit.push_back(trim(tmpStr));
	while(getline(ss, tmpStr, ',')){
		tokensBeforeParenSplit.push_back(trim(tmpStr));
	}
	ss.clear();
	//split tokens by parenthises
	for(unsigned int i=0; i<tokensBeforeParenSplit.size(); i++){
		stringstream ss(tokensBeforeParenSplit[i]);
		string beforeParen, afterParen;
		getline(ss, beforeParen, '(');
		getline(ss, afterParen);
		tokensAfterParenSplit.push_back(beforeParen);
		if(afterParen.length() != 0){
			tokensAfterParenSplit.push_back("(" + afterParen);
		}
	}
	
	return tokensAfterParenSplit;
}

vector<string> Parser::stringExplode(string str){
	vector<string> ret;
	for(int i=0; i<str.length(); i++){
		bool isToken = false;
		string tmpStr;
		while(isWhiteSpace(str[i]) && i<str.length()){
			i++;
		}
		while(!isWhiteSpace(str[i]) && i<str.length()){
			isToken = true;
			tmpStr += str[i];
			i++;
		}
		if(isToken){
			ret.push_back(tmpStr);
		}
	}
	return ret;
}

vector<string> Parser::stringExplodeAndSanitize(string str){
	vector<string> ret = stringExplode(str);
	for(int i=0; i<ret.size(); i++){
		ret[i] = removeTrailingComma(ret[i]);
	}
	return ret;
}


uint32_t Parser::binStrToUnsignedDecInt(string binStr){
	bitset<INSTRUCTIONSIZE> tmpBitset = bitset<INSTRUCTIONSIZE>(binStr);
	uint32_t retVal = (uint32_t)(tmpBitset.to_ulong());
	return retVal;
}

char Parser::flipBit(char i){
	if(i == '0'){
		return '1';
	}else{
		return '0';
	}
}

string Parser::incBitStrByOne(string binStr){
	int i = binStr.length()-1;
	char lastChar = binStr[i];
	if(lastChar == '1'){
		while(binStr[i] == '1'){
			binStr[i] = '0';
			i--;
		}
		binStr[i] = '1';
	}else{
		binStr[i] = '1';
	}

	return binStr;
}

string Parser::onesComplement(string binStr){
	for(unsigned int i=0; i<binStr.length(); i++){
		binStr[i] = flipBit(binStr[i]);
	}
	return binStr;
}

string Parser::twosComplement(string binStr){
	binStr = onesComplement(binStr);
	binStr = incBitStrByOne(binStr);

	return binStr;
}






int Parser::getArgumentValue(string argument){
	argument = removeParentheses(argument);
	if(tokenIsRegister(argument)){
		return getRegisterIndex(argument);
	}else if(tokenIsLiteral(argument)){
		return getLiteralValue(argument);
	}
	cout << "Error invalid token " << argument << '\n';
	getchar();
	return 0;
}



bool Parser::tokenIsRegister(string token){
	return tokenIsGPRegister(token) || tokenIsFPRegister(token);
}
bool Parser::tokenIsGPRegister(string token){
	return getGPRegisterIndex(token) != -1;
}
bool Parser::tokenIsFPRegister(string token){
	return getFPRegisterIndex(token) != -1;
}



string Parser::getGPRegisterName(int index){
	assert(index >= 0 && index < 32);
	return GPRegisterNames[index];
}
string Parser::getFPRegisterName(int index){
	assert(index >= 0 && index < 32);
	return FPRegisterNames[index];
}


int Parser::getRegisterIndex(string token){
	if(tokenIsGPRegister(token)){
		return getGPRegisterIndex(token);
	}else if(tokenIsFPRegister(token)){
		return getFPRegisterIndex(token);
	}
	cout << "error Parser::getRegisterIndex - invalid argument";
	getchar();
	return 0;
}

//TODO: memoize the get*RegisterIndex functions
int Parser::getGPRegisterIndex(string token){
	unordered_map<string, int>::iterator iter = GPRegisterNameMap.find(token);
	if(iter != GPRegisterNameMap.end()){
		return (*iter).second;
	}else{
		return -1;
	}
}

int Parser::getFPRegisterIndex(string token){
	unordered_map<string, int>::iterator iter = FPRegisterNameMap.find(token);
	if(iter != FPRegisterNameMap.end()){
		return (*iter).second;
	}else{
		return -1;
	}
}



bool Parser::tokenIsLiteral(string argument){
	return tokenIsDecimalLiteral(argument)
		|| tokenIsHexLiteral(argument)
		|| tokenIsBinaryLiteral(argument);
}
bool Parser::tokenIsDecimalLiteral(string argument){
	int start = 0;
	if(argument[0] == '-'){start++;}
	for(unsigned int i=start; i<argument.length(); i++){
		if(!isDecimalDigit(argument[i])){return false;}
	}
	return true;
}
bool Parser::tokenIsHexLiteral(string argument){
	if(argument[0] != '0'){return false;}
	if(argument[1] != 'x'){return false;}
	if(argument.length() > 10){return false;}
	for(unsigned int i=2; i<argument.length(); i++){
		if(!isHexDigit(argument[i])){return false;}
	}
	return true;
}
bool Parser::tokenIsBinaryLiteral(string argument){
	if(argument[0] != '0'){return false;}
	if(argument[1] != 'b'){return false;}
	if(argument.length() > 34){return false;}
	for(unsigned int i=2; i<argument.length(); i++){
		if(!isBinaryDigit(argument[i])){return false;}
	}
	return true;
}


int Parser::getLiteralValue(string argument){
	if(tokenIsDecimalLiteral(argument)){
		return getDecimalLiteralValue(argument);
	}else if(tokenIsHexLiteral(argument)){
		return getHexLiteralValue(argument);
	}else if(tokenIsBinaryLiteral(argument)){
		return getBinaryLiteralValue(argument);
	}
	cout << "error[int getLiteralValue(string argument)]: " << argument << " is not a valid literal value\n";
	getchar();
	return 0;
}
int Parser::getDecimalLiteralValue(string argument){
	bool isNeg = argument[0] == '-';
	int start = isNeg? 1 : 0;
	int retVal = 0;
	for(unsigned int i=start; i<argument.length(); i++){
		retVal *= 10;
		retVal += decimalCharToDigit(argument[i]);
	}
	if(isNeg){retVal *= -1;}
	return retVal;
}
int Parser::getHexLiteralValue(string argument){
	int retVal = 0;
	for(unsigned int i=2; i<argument.length(); i++){
		retVal <<= 4;
		retVal |= hexCharToDigit(argument[i]);
	}
	return retVal;
}
int Parser::getBinaryLiteralValue(string argument){
	//this instead of binStrToSigned/UnsignedDecInt(string binStr)
	//	so it's counted as leading 0s
	int retVal = binStrToUnsignedDecInt(argument.substr(2));
	return retVal;
}




string Parser::getValueDecimalLiteral(int val){
	return std::to_string(val);
}
string Parser::getValueHexLiteral(int val){
	stringstream ss;
	ss << "0x" << std::setw(8) << std::setfill('0') << std::hex << val;
	return ss.str();
}
string Parser::getValueBinaryLiteral(int val){
	bool isNeg = (val < 0);
	if(isNeg){
		val = -1 * val;
	}
	bitset<INSTRUCTIONSIZE> tmpBitset = bitset<INSTRUCTIONSIZE>(val);
	string binStr = tmpBitset.to_string();
	if(isNeg){
		binStr = twosComplement(binStr);
	}
	return "0b" + binStr;
}






bool Parser::tokenIsDirective(string token){
	return getDirectiveNumber(token) != -1;
}
int Parser::getDirectiveNumber(string token){
	unordered_map<string, int>::iterator iter = DirectiveNameMap.find(token);
	if(iter != DirectiveNameMap.end()){
		return (*iter).second;
	}else{
		return -1;
	}
}





//

bool Parser::isDecimalDigit(char c){
	return (c >= '0' && c <= '9');
}
bool Parser::isHexDigit(char c){
	return (c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F');
}
bool Parser::isBinaryDigit(char c){
	return c == '0' || c == '1';
}

int Parser::decimalCharToDigit(char c){
	return c - '0';
}
int Parser::hexCharToDigit(char c){
	if(c >= '0' && c <= '9'){return c - '0';}
	else if(c >= 'a' && c <= 'f'){return c - 'a' + 10;}
	else if(c >= 'A' && c <= 'F'){return c - 'A' + 10;}
	//error, not real hex char
	return 0;
}
int Parser::binaryCharToDigit(char c){
	return (c == '0')? 0 : 1;
}










//	Members
string const Parser::GPRegisterNames[] = {
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
	"$ra",
	"$0", "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9", 
	"$10", "$11", "$12", "$13", "$14", "$15", "$16", "$17", "$18", "$19", 
	"$20", "$21", "$22", "$23", "$24", "$25", "$26", "$27", "$28", "$29", 
	"$30", "$31"
};

string const Parser::FPRegisterNames[] = {
	"$f0", "$f1", "$f2", "$f3", "$f4", "$f5", "$f6", "$f7",
	"$f8", "$f9", "$f10", "$f11", "$f12", "$f13", "$f14", "$f15",
	"$f16", "$f17", "$f18", "$f19", "$f20", "$f21", "$f22", "$f23",
	"$f24", "$f25", "$f26", "$f27", "$f28", "$f29", "$f30", "$f31"
};

string const Parser::DirectiveNames[] = {
	".data",
	".text",
	".kdata",
	".ktext",
	".byte",
	".half",
	".word",
	".float",
	".double",
	".ascii",
	".asciiz",
	".align",
	".space",
	".include",
	".extern",
	".globl",
	".set",
	".macro",
	".end_macro",
	".eqv"
};