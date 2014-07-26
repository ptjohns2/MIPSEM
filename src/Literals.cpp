#include "Literals.hpp"

#include "Exceptions.hpp"
#include "Parser.hpp"

#include <bitset>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>

Literals::Literals(){
	for(int i=0; i<NUM_CHARACTERS; i++){
		EscapableCharacters[i] = 0;
	}
	EscapableCharacters['a'] = '\a';
	EscapableCharacters['b'] = '\b';
	EscapableCharacters['f'] = '\f';
	EscapableCharacters['n'] = '\n';
	EscapableCharacters['r'] = '\r';
	EscapableCharacters['t'] = '\t';
	EscapableCharacters['v'] = '\v';
	EscapableCharacters['\\'] = '\\';
	EscapableCharacters['\''] = '\'';
	EscapableCharacters['"'] = '"';
	EscapableCharacters['?'] = '?';

	//StandardCharacterStringRepresentations
	StandardCharacterStringRepresentations[0] = "\\0";
	StandardCharacterStringRepresentations[1] = "\\x1";
	StandardCharacterStringRepresentations[2] = "\\x2";
	StandardCharacterStringRepresentations[3] = "\\x3";
	StandardCharacterStringRepresentations[4] = "\\x4";
	StandardCharacterStringRepresentations[5] = "\\x5";
	StandardCharacterStringRepresentations[6] = "\\x6";
	StandardCharacterStringRepresentations[7] = "\\a";
	StandardCharacterStringRepresentations[8] = "\\b";
	StandardCharacterStringRepresentations[9] = "\\t";
	StandardCharacterStringRepresentations[10] = "\\n";
	StandardCharacterStringRepresentations[11] = "\\v";
	StandardCharacterStringRepresentations[12] = "\\f";
	StandardCharacterStringRepresentations[13] = "\\r";
	StandardCharacterStringRepresentations[14] = "\\xE";
	StandardCharacterStringRepresentations[15] = "\\xF";
	StandardCharacterStringRepresentations[16] = "\\x10";
	StandardCharacterStringRepresentations[17] = "\\x11";
	StandardCharacterStringRepresentations[18] = "\\x12";
	StandardCharacterStringRepresentations[19] = "\\x13";
	StandardCharacterStringRepresentations[20] = "\\x14";
	StandardCharacterStringRepresentations[21] = "\\x15";
	StandardCharacterStringRepresentations[22] = "\\x16";
	StandardCharacterStringRepresentations[23] = "\\x17";
	StandardCharacterStringRepresentations[24] = "\\x18";
	StandardCharacterStringRepresentations[25] = "\\x19";
	StandardCharacterStringRepresentations[26] = "\\x1A";
	StandardCharacterStringRepresentations[27] = "\\x1B";
	StandardCharacterStringRepresentations[28] = "\\x1C";
	StandardCharacterStringRepresentations[29] = "\\x1D";
	StandardCharacterStringRepresentations[30] = "\\x1E";
	StandardCharacterStringRepresentations[31] = "\\x1F";
	for(unsigned int i = ' '; i<NUM_CHARACTERS; i++){
		string tmp;
		tmp += (char)i;
		StandardCharacterStringRepresentations[i] = tmp;
	}
	StandardCharacterStringRepresentations['\\'] = "\\\\";
	StandardCharacterStringRepresentations['\''] = "\\'";
	StandardCharacterStringRepresentations['"'] = "\\\"";
	StandardCharacterStringRepresentations[127] = "\\x7F";
}
Literals::~Literals(){

}




bool Literals::tokenIsLiteral(string token){
	if(tokenIsDecimalLiteral(token)){return true;}
	if(tokenIsFloatLiteral(token)){return true;}
	if(tokenIsHexLiteral(token)){return true;}
	if(tokenIsBinaryLiteral(token)){return true;}
	if(tokenIsOctalLiteral(token)){return true;}
	if(tokenIsCharLiteral(token)){return true;}
	return false;
}
int Literals::getLiteralValue(string token){
	if(tokenIsDecimalLiteral(token)){
		return getDecimalLiteralValue(token);
	}else if(tokenIsHexLiteral(token)){
		return getHexLiteralValue(token);
	}else if(tokenIsBinaryLiteral(token)){
		return getBinaryLiteralValue(token);
	}else if(tokenIsOctalLiteral(token)){
		return getOctalLiteralValue(token);
	}else if(tokenIsCharLiteral(token)){
		return (int)getCharLiteralValue(token);
	}else if(tokenIsFloatLiteral(token)){
		return (int)(getFloatLiteralValue(token));
	}
	throw InvalidTokenException("Literal", token);
	return 0;
}

bool Literals::tokenIsFixedPointLiteral(string token){
	if(tokenIsDecimalLiteral(token)){return true;}
	if(tokenIsHexLiteral(token)){return true;}
	if(tokenIsBinaryLiteral(token)){return true;}
	if(tokenIsOctalLiteral(token)){return true;}
	if(tokenIsCharLiteral(token)){return true;}
	return false;
}
int Literals::getFixedPointLiteralValue(string token){
	if(tokenIsDecimalLiteral(token)){
		return getDecimalLiteralValue(token);
	}else if(tokenIsHexLiteral(token)){
		return getHexLiteralValue(token);
	}else if(tokenIsBinaryLiteral(token)){
		return getBinaryLiteralValue(token);
	}else if(tokenIsOctalLiteral(token)){
		return getOctalLiteralValue(token);
	}else if(tokenIsCharLiteral(token)){
		return (int)getCharLiteralValue(token);
	}
	throw InvalidTokenException("Fixed point literal", token);
	return 0;
}










bool Literals::tokenIsDecimalLiteral(string token){
	int start = 0;
	if(token[0] == '0' && token.length() > 1){return false;}//if octal return false
	if(token[0] == '-'){start++;}
	for(unsigned int i=start; i<token.length(); i++){
		if(!isDecimalDigit(token[i])){return false;}
	}
	return true;
}
bool Literals::isDecimalDigit(char c){
	return (c >= '0' && c <= '9');
}
int Literals::getDecimalDigitValue(char c){
	return c - '0';
}
int Literals::getDecimalLiteralValue(string token){
	//return atoi(token.c_str());
	if(!tokenIsDecimalLiteral(token)){
		throw InvalidTokenException("Decimal literal", token);
		return 0;
	}
	bool isNeg = token[0] == '-';
	int start = isNeg? 1 : 0;
	int retVal = 0;
	for(unsigned int i=start; i<token.length(); i++){
		retVal *= 10;
		retVal += getDecimalDigitValue(token[i]);
	}
	if(isNeg){retVal *= -1;}
	return retVal;
}
string Literals::getDecimalLiteralString(int val){
	return std::to_string(val);
}













bool Literals::tokenIsFloatLiteral(string token){
	int start = 0;
	if(token[0] == '-'){start++;}
	bool decimalFound = false;
	for(unsigned int i=start; i<token.length(); i++){
		if(token[i] == '.'){
			if(decimalFound == true){
				return false;
			}else{
				decimalFound = true;	
			}
		}else{
			if(!isDecimalDigit(token[i])){
				return false;
			}
		}
	}
	return true;
}
float Literals::getFloatLiteralValue(string token){
	if(!tokenIsFloatLiteral(token)){
		throw InvalidTokenException("Float literal", token);
		return 0;
	}
	return (float)atof(token.c_str());
}
double Literals::getDoubleLiteralValue(string token){
	if(!tokenIsFloatLiteral(token)){
		throw InvalidTokenException("Double literal", token);
		return 0;
	}
	return atof(token.c_str());
}
string Literals::getFloatLiteralString(float val){
	return std::to_string(val);
}
string Literals::getDoubleLiteralString(double val){
	return std::to_string(val);
}









bool Literals::tokenIsHexLiteral(string token){
	if(token.length() <= 2){return false;}
	if(token[0] != '0'){return false;}
	if(token[1] != 'x' && token[1] != 'X'){return false;}
	return tokenIsRawHexLiteral(token.substr(2));
}
bool Literals::isHexDigit(char c){
	return (c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F');
}
bool Literals::tokenIsRawHexLiteral(string token){
	for(unsigned int i=0; i<token.length(); i++){
		if(!isHexDigit(token[i])){
			return false;
		}
	}
	return true;
}
int Literals::getHexDigitValue(char c){
	if(c >= '0' && c <= '9'){
		return c - '0';
	}
	else if(c >= 'a' && c <= 'f'){
		return c - 'a' + 10;
	}
	else /*	if(c >= 'A' && c <= 'F')	*/	{
		return c - 'A' + 10;
	}
}
int Literals::getHexLiteralValue(string token){
	if(!tokenIsHexLiteral(token)){
		throw InvalidTokenException("Hex literal", token);
		return 0;
	}
	return getRawHexLiteralValue(token.substr(2));
}
int Literals::getRawHexLiteralValue(string token){
	int retVal = 0;
	for(unsigned int i=0; i<token.length(); i++){
		retVal <<= 4;
		retVal |= getHexDigitValue(token[i]);
	}
	return retVal;
}
string Literals::getHexLiteralString(int val){
	stringstream ss;
	ss  << std::setw(8) << std::setfill('0') << std::hex << val;
	return "0x" + Parser::toUpper(ss.str());
}














bool Literals::tokenIsBinaryLiteral(string token){
	if(token.length() <= 2){return false;}
	if(token[0] != '0'){return false;}
	if(token[1] != 'b' && token[1] != 'B'){return false;}
	return tokenIsRawBinaryLiteral(token.substr(2));
}
bool Literals::isBinaryDigit(char c){
	return c == '0' || c == '1';
}
bool Literals::tokenIsRawBinaryLiteral(string token){
	for(unsigned int i=0; i<token.length(); i++){
		if(!isBinaryDigit(token[i])){return false;}
	}
	return true;
}
int Literals::getBinaryDigitValue(char c){
	return (c == '0')? 0 : 1;
}
int Literals::getRawBinaryLiteralValue(string token){
	int retVal = 0;
	for(int i=0; i<token.length(); i++){
		retVal <<= 1;
		retVal |= getBinaryDigitValue(token[i]);
	}
	return retVal;
}
int Literals::getBinaryLiteralValue(string token){
	if(!tokenIsBinaryLiteral(token)){
		throw InvalidTokenException("Binary literal", token);
		return 0;
	}
	//this instead of binStrToSigned/UnsignedDecInt(string binStr)
	//	so it's counted as leading 0s
	int retVal = binStrToUnsignedDecInt(token.substr(2));
	return retVal;
}
string Literals::getBinaryLiteralString(int val){
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

//utilities
uint32_t Literals::binStrToUnsignedDecInt(string binStr){
	bitset<INSTRUCTIONSIZE> tmpBitset = bitset<INSTRUCTIONSIZE>(binStr);
	uint32_t retVal = (uint32_t)(tmpBitset.to_ulong());
	return retVal;
}
char Literals::flipBit(char i){
	if(i == '0'){
		return '1';
	}else{
		return '0';
	}
}
string Literals::incBitStrByOne(string binStr){
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
string Literals::onesComplement(string binStr){
	for(unsigned int i=0; i<binStr.length(); i++){
		binStr[i] = flipBit(binStr[i]);
	}
	return binStr;
}
string Literals::twosComplement(string binStr){
	binStr = onesComplement(binStr);
	binStr = incBitStrByOne(binStr);

	return binStr;
}






bool Literals::tokenIsOctalLiteral(string token){
	if(token.length() <= 1){return false;}
	if(token[0] != '0'){return false;}
	return tokenIsRawOctalLiteral(token.substr(1));
}
bool Literals::isOctalDigit(char c){
	return c >= '0' && c <= '7';
}
bool Literals::tokenIsRawOctalLiteral(string token){
	for(unsigned int i=0; i<token.length(); i++){
		if(!isOctalDigit(token[i])){return false;}
	}
	return true;
}
int Literals::getOctalDigitValue(char c){
	return c - '0';
}
int Literals::getRawOctalLiteralValue(string token){
	if(!tokenIsOctalLiteral(token)){
		throw InvalidTokenException("Octal literal", token);
		return 0;
	}
	int retVal = 0;
	for(int i=0; i<token.length(); i++){
		retVal <<= 3;
		retVal |= getOctalDigitValue(token[i]);
	}
	return retVal;
}
int Literals::getOctalLiteralValue(string token){
	return getRawOctalLiteralValue(token.substr(1));
}
string Literals::getOctalLiteralString(int val){
	stringstream ss;
	ss << "0" << /*	std::setw(16) << std::setfill('0') <<	*/ std::oct << val;
	return ss.str();
}












bool Literals::tokenIsCharLiteral(string token){
	if(token.length() < 3){return false;}
	if(token.length() > ESCAPED_RAW_CHAR_LITERAL_MAX_LENGTH + 2){return false;}
	if(!Parser::isNestedByApostrophes(token)){return false;}
	return tokenIsRawCharLiteral(Parser::removeNestedApostrophes(token));
}
bool Literals::tokenIsRawCharLiteral(string token){
	if(token.length() == 1){
		if(token[0] == '\''){
			return false;
		}else{
			return true;
		}
	}
	else if(tokenIsRawEscapedCharLiteral(token)){
		return true;
	}
	return false;
}
bool Literals::tokenIsRawEscapedCharLiteral(string token){
	if(token.length() < ESCAPED_RAW_CHAR_LITERAL_MIN_LENGTH){return false;}
	if(token.length() > ESCAPED_RAW_CHAR_LITERAL_MAX_LENGTH){return false;}
	if(token[0] != '\\'){return false;}

	if(token[1] == 'x' || token[1] == 'X'){
		//Hex \xnn
		if(token.length() < 3){return false;}
		if(token.length() > 4){return false;}
		for(int i=2; i<token.length(); i++){
			if(!isHexDigit(token[i])){return false;}
		}
		return true;
	}else if(isOctalDigit(token[1])){
		//Octal \nnn
		if(token.length() < 2){return false;}
		if(token.length() > 4){return false;}
		//start at 2 since 1 already tested above
		for(int i=2; i<token.length(); i++){
			if(!isOctalDigit(token[i])){return false;}
		}
		return true;
	}else{
		//Standard \*
		if(token.length() != 2){return false;}
		if(EscapableCharacters[token[1]] == 0){
			return false;
		}
		return true;
	}
	return false;
	//http://en.cppreference.com/w/cpp/language/escape
														/*
\'	 single quote	 byte 0x27 in ASCII encoding
\"	 double quote	 byte 0x22 in ASCII encoding
\?	 question mark	 byte 0x3f in ASCII encoding
\\	 backslash	 byte 0x5c in ASCII encoding
\a	 audible bell	 byte 0x07 in ASCII encoding
\b	 backspace	 byte 0x08 in ASCII encoding
\f	 form feed - new page	 byte 0x0c in ASCII encoding
\n	 line feed - new line	 byte 0x0a in ASCII encoding
\r	 carriage return	 byte 0x0d in ASCII encoding
\t	 horizontal tab	 byte 0x09 in ASCII encoding
\v	 vertical tab	 byte 0x0b in ASCII encoding
\nnn	 arbitrary octal value	 byte nnn
\xnn	 arbitrary hexadecimal value	 byte nn		*/
}


char Literals::getRawCharLiteralValue(string token){
	if(token.length() == 1){
		return token[0];
	}else{
		return getRawEscapedCharLiteralValue(token);
	}
}
char Literals::getRawEscapedCharLiteralValue(string token){
	if(token[1] == 'x' || token[1] == 'X'){
		//Hex \xnn
		return getRawHexLiteralValue(token.substr(2));
	}else if(isOctalDigit(token[1])){
		//Octal \nnn
		return getRawOctalLiteralValue(token.substr(1));
	}else{
		//Standard \*
		return EscapableCharacters[token[1]];
	}
}
char Literals::getCharLiteralValue(string token){
	if(!tokenIsCharLiteral(token)){
		throw InvalidTokenException("Char literal", token);
		return 0;
	}
	return getRawCharLiteralValue(Parser::removeNestedApostrophes(token));
}
string Literals::getRawCharLiteralString(char c){
	return StandardCharacterStringRepresentations[c];
}
string Literals::getCharLiteralString(char c){
	return "'" + StandardCharacterStringRepresentations[c] + "'";
}

















bool Literals::tokenIsStringLiteral(string token){
	if(token.length() < 2){return false;}
	if(!Parser::isNestedByQuotes(token)){return false;}
	return tokenIsRawStringLiteral(Parser::removeNestedQuotes(token));
}
bool Literals::tokenIsRawStringLiteral(string token){
	if(token == ""){return true;}
	if(token[0] == '"'){return false;}
	for(int i=0; i<token.length(); i++){
		if(token[i] == '"' && token[i-1] != '\\'){return false;}
	}
	return true;
}
string Literals::getRawStringLiteralValue(string token){
	if(token == ""){return "";}
	string newString;
	for(int i=0; i<token.length(); i++){
		if(token[i] == '\\'){
			int max = ESCAPED_RAW_CHAR_LITERAL_MAX_LENGTH;
			int min = ESCAPED_RAW_CHAR_LITERAL_MIN_LENGTH;
			int len = max;
			bool leadByEscapedCharLiteral = false;
			for(; len >= min; len--){
				string testEscapedCharLiteral = token.substr(i, len);
				if(tokenIsRawEscapedCharLiteral(testEscapedCharLiteral)){
					leadByEscapedCharLiteral = true;
					newString += getRawEscapedCharLiteralValue(testEscapedCharLiteral);
					i += len - 1; //-1 to take into account i++ loop
					break;
				}
			}
			if(!leadByEscapedCharLiteral){newString += '\\';}
		}else{
			newString += token[i];
		}
	}
	return newString;
}
string Literals::getStringLiteralValue(string token){
	if(!tokenIsStringLiteral(token)){
		throw InvalidTokenException("String literal", token);
		return "INVALID_STRING_LITERAL";
	}
	return getRawStringLiteralValue(Parser::removeNestedQuotes(token));
}
string Literals::getRawStringLiteralString(string token){
	string newStr;
	for(int i=0; i<token.length(); i++){
		newStr += getRawCharLiteralString(token[i]);
	}
	return newStr;
}
string Literals::getStringLiteralString(string token){
	return '"' + getRawStringLiteralString(token) + '"';
}





