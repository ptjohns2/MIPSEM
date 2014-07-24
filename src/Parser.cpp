#include "Parser.hpp"

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#define WHITE_SPACE_STRING (" \t\n")

Parser::Parser()
	:	literals()
{
	for(int i=0; i<NUM_GP_REGISTER_NAMES; i++){
		GPRegisterNameMap[GPRegisterNames[i]] = i;
	}
	for(int i=0; i<NUM_FP_REGISTER_NAMES; i++){
		FPRegisterNameMap[FPRegisterNames[i]] = i;
	}
	for(int i=0; i<NUM_DIRECTIVE_NAMES; i++){
		DirectiveMap[DirectiveNames[i]] = i;
	}
	for(int i=0; i<NUM_INSTRUCTION_NAMES; i++){
		InstructionNameMap[InstructionNames[i]] = i;
	}
	for(int i=0; i<NUM_BRANCH_INSTRUCTION_NAMES; i++){
		BranchInstructionNameMap[BranchInstructionNames[i]] = i;
	}
	for(int i=0; i<NUM_JUMP_INSTRUCTION_NAMES; i++){
		JumpInstructionNameMap[JumpInstructionNames[i]] = i;
	}
	for(int i=0; i<NUM_PSEUDO_INSTRUCTION_NAMES; i++){
		PseudoInstructionNameMap[PseudoInstructionNamesAndNumberOfLinesToInsert[i].first] = i;
	}
}
Parser::~Parser(){

}


//	public Methods

string Parser::toLower(string str){
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}
string Parser::toUpper(string str){
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}


int Parser::indexOf(string _str, string substr){
	return indexOf(_str, substr, 0);
}
int Parser::indexOf(string _str, string substr, int fromIndex){
	if(_str.length() < substr.length()){return -1;}
	for(int i=fromIndex; i<_str.length()-substr.length() + 1; i++){
		int numCharMatches = 0;
		for(int j=0; j<substr.length(); j++){
			if(!(substr[j] == _str[i+j])){break;}
			numCharMatches++;
		}
		if(numCharMatches == substr.length()){return i;}
	}
	return -1;
}

string Parser::replace(string _str, string target, string replacement){
	int firstIndex = indexOf(_str, target);
	if(firstIndex == -1){
		return _str;
	}

	string front = (firstIndex == 0)? "" : _str.substr(0, firstIndex);
	string end = _str.substr(firstIndex + target.length());

	return front + replacement + replace(end, target, replacement);
}

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




bool Parser::isNestedByParentheses(string str){
	return str[0] == '(' && str[str.length()-1] == ')';
}
string Parser::removeNestedParentheses(string str){
	if(isNestedByParentheses(str)){
		return str.substr(1, str.length() - 1 - 1);
	}
	return str;
}
bool Parser::isNestedByApostrophes(string str){
	return str[0] == '\'' && str[str.length()-1] == '\'';
}
string Parser::removeNestedApostrophes(string str){
	if(isNestedByApostrophes(str)){
		return str.substr(1, str.length() - 1 - 1);
	}
	return str;
}
bool Parser::isNestedByQuotes(string str){
	return str[0] == '\"' && str[str.length()-1] == '\"';
}
string Parser::removeNestedQuotes(string str){
	if(isNestedByQuotes(str)){
		return str.substr(1, str.length() - 1 - 1);
	}
	return str;
}

bool Parser::isTrailedByComma(string str){
	return str[str.length() - 1] == ',';
}
string Parser::removeTrailingComma(string str){
	if(isTrailedByComma(str)){
		return str.substr(0, str.length() - 1);
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

string Parser::removeComment(string str){
	int i = 0;
	while(i<str.length() && str[i] != '#'){
		if(str[i] == '\t'){str[i] = ' ';}
		i++;	
	}
	return trim(str.substr(0, i));
}
string Parser::sanitizeProgramLine(string line){
	line = removeComment(line);
	//others?
	return line;
}

vector<string> Parser::tokenizeInstruction(string str){
	// NAME A1,A2,A3,A4#xxxx
	str = removeComment(str);

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
string Parser::combineInstructionTokens(vector<string> const& tokens){
	string instructionStr = tokens[0];
	if(tokens.size() > 1){
		instructionStr += '\t';
	}
	for(int i=1; i<tokens.size(); i++){
		instructionStr += tokens[i];
		if(i+1 < tokens.size()){
			instructionStr += ", ";
		}
	}
	return instructionStr;
}

vector<string> Parser::stringExplode(string str){
	vector<string> ret;
	for(int i=0; i<str.length(); i++){
		bool isToken = false;
		string tmpStr;
		while(isWhiteSpace(str[i]) && i<str.length()){i++;}
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


vector<string> Parser::commaSeparatedListExplode(string str){
	vector<string> ret;
	for(int i=0; i<str.length(); i++){
		bool isToken = false;
		string tmpStr;
		while(isWhiteSpace(str[i]) && i<str.length()){i++;}
		while(i<str.length()){
			/*
			//COND1 whitespace and not ' ' char literal
			if(isWhiteSpace(str[i])){
				if(str[i-1] == '\'' && str[i+1] == '\''){
					//do nothing
				}else{
					break;
				}
			}
			*/
			//COND2 comma and not ',' char literal
			if(str[i] == ','){
				if(str[i-1] == '\'' && str[i+1] == '\''){
					//do nothing;
				}else{
					break;
				}
			}

			isToken = true;
			tmpStr += str[i];
			i++;
		}
		if(isToken){
			ret.push_back(trim(tmpStr));
		}
	}
	return ret;
}


string Parser::extractFirstToken(string str){
	//mirror extractAndRemoveFirstToken
	string firstToken;
	int i = 0;
	while(isWhiteSpace(str[i]) && i<str.length()){i++;}
	while(!isWhiteSpace(str[i]) && i<str.length()){
		firstToken += str[i];
		i++;
	}
	return firstToken;
}
bool Parser::extractAndRemoveFirstToken(string &src, string &token){
	token = "";
	if(src == ""){
		return false;
	}
	//mirror extractFirstToken
	int i = 0;
	while(isWhiteSpace(src[i]) && i<src.length()){i++;}
	while(!isWhiteSpace(src[i]) && i<src.length()){
		token += src[i];
		i++;
	}
	while(isWhiteSpace(src[i]) && i<src.length()){i++;}
	src = src.substr(i);
}




string Parser::combineTokensToString(vector<string> const &tokens, int from){
	string combinedStr;
	for(int i=from; i<tokens.size() - 1; i++){
		combinedStr += tokens[i] + ' ';
	}
	combinedStr += tokens[tokens.size() - 1];
	return combinedStr;
}










int Parser::getTokenValue(string argument){
	argument = removeNestedParentheses(argument);
	if(tokenIsRegister(argument)){
		return getRegisterIndex(argument);
	}else if(literals.tokenIsLiteral(argument)){
		return literals.getLiteralValue(argument);
	}
	cout << "Error invalid token " << argument << '\n';
	getchar();
	return 0;
}



bool Parser::tokenIsRegister(string token){
	return tokenIsGPRegister(token) || tokenIsFPRegister(token);
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

bool Parser::tokenIsGPRegister(string token){
	return getGPRegisterIndex(token) != -1;
}
int Parser::getGPRegisterIndex(string token){
	unordered_map<string, int>::iterator iter = GPRegisterNameMap.find(token);
	if(iter != GPRegisterNameMap.end()){
		return (*iter).second;
	}else{
		return -1;
	}
}
string Parser::getGPRegisterName(int index){
	assert(index >= 0 && index < 32);
	return GPRegisterNames[index];
}


bool Parser::tokenIsFPRegister(string token){
	return getFPRegisterIndex(token) != -1;
}
int Parser::getFPRegisterIndex(string token){
	unordered_map<string, int>::iterator iter = FPRegisterNameMap.find(token);
	if(iter != FPRegisterNameMap.end()){
		return (*iter).second;
	}else{
		return -1;
	}
}
string Parser::getFPRegisterName(int index){
	assert(index >= 0 && index < 32);
	return FPRegisterNames[index];
}

















bool Parser::tokenIsInstructionName(string token){
	return getInstructionNameNumber(token) != -1;
}
int Parser::getInstructionNameNumber(string token){
	unordered_map<string, int>::iterator iter = InstructionNameMap.find(token);
	if(iter != InstructionNameMap.end()){
		return (*iter).second;
	}else{
		return -1;
	}
}
bool Parser::tokenIsBranchInstructionName(string token){
	return getBranchInstructionNameNumber(token) != -1;
}
int Parser::getBranchInstructionNameNumber(string token){
	unordered_map<string, int>::iterator iter = BranchInstructionNameMap.find(token);
	if(iter != BranchInstructionNameMap.end()){
		return (*iter).second;
	}else{
		return -1;
	}
}
bool Parser::tokenIsJumpInstructionName(string token){
	return getJumpInstructionNameNumber(token) != -1;
}
int Parser::getJumpInstructionNameNumber(string token){
	unordered_map<string, int>::iterator iter = JumpInstructionNameMap.find(token);
	if(iter != JumpInstructionNameMap.end()){
		return (*iter).second;
	}else{
		return -1;
	}
}
bool Parser::tokenIsPseudoInstructionName(string token){
	return getPseudoInstructionNameNumber(token) != -1;
}
int Parser::getPseudoInstructionNameNumber(string token){
	unordered_map<string, int>::iterator iter = PseudoInstructionNameMap.find(token);
	if(iter != PseudoInstructionNameMap.end()){
		return (*iter).second;
	}else{
		return -1;
	}
}
int Parser::getPseudoInstructionNumberOfLinesToInsert(string token){
	if(!tokenIsPseudoInstructionName(token)){return -1;}
	int num = getPseudoInstructionNameNumber(token);
	return PseudoInstructionNamesAndNumberOfLinesToInsert[num].second;
}


bool Parser::tokenIsDirective(string token){
	return getDirectiveNumber(token) != -1;
}
int Parser::getDirectiveNumber(string token){
	unordered_map<string, int>::iterator iter = DirectiveMap.find(token);
	if(iter != DirectiveMap.end()){
		return (*iter).second;
	}else{
		return -1;
	}
}
string Parser::getDirectiveName(int num){
	return DirectiveNames[num];
}



bool Parser::tokenIsLabel(string token){
	for(int i=0; i<token.length(); i++){
		if(isWhiteSpace(token[i])){return false;}
	}
	return token[token.length() - 1] == ':';
}
string Parser::getLabelName(string token){
	return token.substr(0, token.length() - 1);
}





















//
























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
	".eqv",
};

string const Parser::InstructionNames[] = {
	"abs.s","abs.d","abs.ps","add","add.s","add.d","add.ps","addi",	"addiu", "addu","alnv.ps","and","andi",
	"b","bal","bc1f","bc1f","bc1fl","bc1fl","bc1t","bc1t","bc1tl","bc1tl","bc2f","bc2f","bc2fl","bc2fl","bc2t","bc2t","bc2tl","bc2tl","beq","beql","bgez","bgezal","bgezall","bgezl","bgtz","bgtzl","blez","blezl","bltz","bltzal","bltzall","bltzl","bne","bnel","break",
	"c.f.s","c.f.s","c.f.d","c.f.d","c.f.ps","c.f.ps","c.un.s","c.un.s","c.un.d","c.un.d","c.un.ps","c.un.ps","c.eq.s","c.eq.s","c.eq.d","c.eq.d","c.eq.ps","c.eq.ps","c.ueq.s","c.ueq.s","c.ueq.d","c.ueq.d","c.ueq.ps","c.ueq.ps","c.olt.s","c.olt.s","c.olt.d","c.olt.d","c.olt.ps","c.olt.ps","c.ult.s","c.ult.s","c.ult.d","c.ult.d","c.ult.ps","c.ult.ps","c.ole.s","c.ole.s","c.ole.d","c.ole.d","c.ole.ps","c.ole.ps","c.ule.s","c.ule.s","c.ule.d","c.ule.d","c.ule.ps","c.ule.ps","c.sf.s","c.sf.s","c.sf.d","c.sf.d","c.sf.ps","c.sf.ps","c.ngle.s","c.ngle.s","c.ngle.d","c.ngle.d","c.ngle.ps","c.ngle.ps","c.seq.s","c.seq.s","c.seq.d","c.seq.d","c.seq.ps","c.seq.ps","c.ngl.s","c.ngl.s","c.ngl.d","c.ngl.d","c.ngl.ps","c.ngl.ps","c.lt.s","c.lt.s","c.lt.d","c.lt.d","c.lt.ps","c.lt.ps","c.nge.s","c.nge.s","c.nge.d","c.nge.d","c.nge.ps","c.nge.ps","c.le.s","c.le.s","c.le.d","c.le.d","c.le.ps","c.le.ps","c.ngt.s","c.ngt.s","c.ngt.d","c.ngt.d","c.ngt.ps","c.ngt.ps","cache","cachee","ceil.l.s","ceil.l.d","ceil.w.s","ceil.w.d","cfc1","cfc2","clo","clz","cop2","ctc1","ctc2","cvt.d.s","cvt.d.w","cvt.d.l","cvt.l.s","cvt.l.d","cvt.ps.s","cvt.s.d","cvt.s.w","cvt.s.l","cvt.s.pl","cvt.s.pl","cvt.w.s","cvt.w.d",
	"deret","di","div","div.s","div.d","divu",
	"ehb","ei","eret","ext",
	"floor.l.s","floor.l.d","floor.w.s","floor.w.d",
	"ins",
	"j","jal","jalr","jalr","jalr.hb","jalr.hb","jalx","jr","jr.hb",
	"lb","lbe","lbu","lbue","ldc1","ldc2","ldxc1","lh","lhe","lhu","lhue","ll","lle","lui","luxc1","lw","lwc1","lwc2","lwe","lwl","lwle","lwr","lwre","lwxc1",
	"madd","madd.s","madd.d","madd.ps","maddu","mfc0","mfc0","mfc1","mfc2","mfc2","mfhc1","mfhc2","mfhc2","mfhi","mflo","mov.s","mov.d","mov.ps","movf","movf.s","movf.d","movf.ps","movn","movn.s","movn.d","movn.ps","movt","movt.s","movt.d","movt.ps","movz","movz.s","movz.d","movz.ps","msub","msub.s","msub.d","msub.ps","msubu","mtc0","mtc0","mtc1","mtc2","mtc2","mthc1","mthc2","mthc2","mthi","mtlo","mul","mul.s","mul.d","mul.ps","mult","multu",
	"neg.s","neg.d","neg.ps","nmadd.s","nmadd.d","nmadd.ps","nmsub.s","nmsub.d","nmsub.ps","nop","nor",
	"or","ori",
	"pause","pll.ps","plu.ps","pref","prefe","prefx","pul.ps","puu.ps",
	"rdhwr","rdpgpr","recip.s","recip.d","rotr","rotrv","round.l.s","round.l.d","round.w.s","round.w.d","rsqrt.s","rsqrt.d",
	"sb","sbe","sc","sce","sdbbp","sdc1","sdc2","sdxc1","seb","seh","sh","she","sll","sllv","slt","slti","sltiu","sltu","sqrt.s","sqrt.d","sra","srav","srl","srlv","ssnop","sub","sub.s","sub.d","sub.ps","subu","suxc1","sw","swc1","swc2","swe","swl","swle","swr","swre","swxc1","sync","sync","synci","syscall",
	"teq","teqi","tge","tgei","tgeiu","tgeu","tlbinv","tlbinvf","tlbp","tlbr","tlbwi","tlbwr","tlt","tlti","tltiu","tltu","tne","tnei","trunc.l.s","trunc.l.d","trunc.w.s","trunc.w.d",
	"wait","wrpgpr","wsbh",
	"xor","xori"
};

string const Parser::BranchInstructionNames[] = {
	"b",
	"bal",
	"bc1f",
	"bc1fl",
	"bc1t",
	"bc1tl",
	"bc2f",
	"bc2fl",
	"bc2t",
	"bc2tl",
	"beq",
	"beql",
	"bgez",
	"bgezal",
	"bgezall",
	"bgezl",
	"bgtz",
	"bgtzl",
	"blez",
	"blezl",
	"bltz",
	"bltzal",
	"bltzall",
	"bltzl",
	"bne",
	"bnel"
};

string const Parser::JumpInstructionNames[] = {
	"j",
	"jal",
	"jalx"
};

pair<string, int> const Parser::PseudoInstructionNamesAndNumberOfLinesToInsert[] = {
	make_pair("bge", 1),
	make_pair("bgt", 1),
	make_pair("ble", 1),
	make_pair("blt", 1),
	make_pair("clear", 0),
	make_pair("div", 1),
	make_pair("la", 1),
	make_pair("li", 1),
	make_pair("move", 0),
	make_pair("mul", 1),
	make_pair("neg", 0),
	make_pair("not", 0),
	make_pair("push", 1),
	make_pair("pop", 1),
	make_pair("peak", 0),
	make_pair("rem", 1),
	make_pair("sge", 1),
	make_pair("sgt", 1),
};
