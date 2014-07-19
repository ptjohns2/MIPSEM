#include "Assembler.hpp"

#include "BitManip.hpp"
#include "Parser.hpp"

#include <iostream>
#include <fstream>
#include <tuple>



Assembler::Assembler()
	:	virtualMemory(), parser()
{
	init();
}
Assembler::~Assembler(){
	deinit();
}
void Assembler::init(){
	memorySegmentTopArray[DIRECTIVE_DATA] = MEMSEG_BASE_DATA;
	memorySegmentTopArray[DIRECTIVE_TEXT] = MEMSEG_BASE_TEXT;
	memorySegmentTopArray[DIRECTIVE_KDATA] = MEMSEG_BASE_KDATA;
	memorySegmentTopArray[DIRECTIVE_KTEXT] = MEMSEG_BASE_KTEXT;

	currentMemorySegment = DIRECTIVE_DATA;
	currentValueTypeSpecifier = DIRECTIVE_WORD;
	currentAction = ACTION_INIT;
	currentByteAlignment = SIZE_WORD;

}
void Assembler::deinit(){

}
void Assembler::reset(){
	virtualMemory.reset();
	program.clear();
	alignedProgram.clear();
	labelsToAssign.clear();
	labelNames.clear();
	labelMap.clear();

	globalLabelNames.clear();
	globalLabelMap.clear();

	init();
}
void Assembler::setEncoder(Encoder* encoder){
	this->encoder = encoder;
}


void Assembler::loadProgramFromFile(string fileName){
	fstream file = fstream(fileName);
	if(!file.is_open()){return;}
	string tmpProgramLine;
	while(getline(file, tmpProgramLine)){
		tmpProgramLine = Parser::sanitizeProgramLine(tmpProgramLine);
		if(tmpProgramLine != ""){
			program.push_back(tmpProgramLine);
		}
	}
}





//Pre-processing

void Assembler::pseudoInstructionPad(){	
	for(int programLineNumber=0; programLineNumber<program.size(); programLineNumber++){
		string line = program[programLineNumber];

		string token = parser.extractFirstToken(line);
		if(parser.tokenIsLabel(token)){
			parser.extractAndRemoveFirstToken(line, token);
		}
		token = parser.toLower(parser.extractFirstToken(line));
		int pseudoInstructionNumber = 0;
		if(parser.tokenIsPseudoInstructionName(token)){
			pseudoInstructionNumber = parser.getPseudoInstructionNameNumber(token);
		}else{
			continue;
		}
		int numLinesToInsert = parser.getPseudoInstructionNumberOfLinesToInsert(token);
		for(int numInsertedLines = 0; numInsertedLines < numLinesToInsert; numInsertedLines++){
			program.insert(program.begin() + programLineNumber, line);
		}
		programLineNumber += numLinesToInsert;
	}
}






bool Assembler::tokenIsInLabelDB(string token){
	return getLabelAddress(token) != -1;
}
void Assembler::addLabelAddress(string label, virtualAddr addr){
	labelMap[label] = addr;
	labelNames.push_back(label);
}
virtualAddr Assembler::getLabelAddress(string label){
	unordered_map<string, virtualAddr>::iterator iter = labelMap.find(label);
	if(iter != labelMap.end()){
		return (*iter).second;
	}else{
		return -1;
	}
}

void Assembler::applyDirective(string directive){
	uint32_t directiveNumber = parser.getDirectiveNumber(directive);
	switch(directiveNumber){
		//Primary memory segments
		case DIRECTIVE_DATA:
			currentMemorySegment = DIRECTIVE_DATA;
			currentAction = ACTION_DECLARE_SEGMENT;
			break;
		case DIRECTIVE_TEXT:
			currentMemorySegment = DIRECTIVE_TEXT;
			currentAction = ACTION_DECLARE_SEGMENT;
			break;
		case DIRECTIVE_KDATA:
			currentMemorySegment = DIRECTIVE_KDATA;
			currentAction = ACTION_DECLARE_SEGMENT;
			break;
		case DIRECTIVE_KTEXT:
			currentMemorySegment = DIRECTIVE_KTEXT;
			currentAction = ACTION_DECLARE_SEGMENT;
			break;

		//Memory value type specifiers (integral)
		case DIRECTIVE_BYTE:
			currentValueTypeSpecifier = DIRECTIVE_BYTE;
			currentByteAlignment = SIZE_BYTE;
			currentAction = ACTION_MEMWRITE_INTEGRAL;
			break;
		case DIRECTIVE_HALF:
			currentValueTypeSpecifier = DIRECTIVE_HALF;
			currentByteAlignment = SIZE_HALF;
			currentAction = ACTION_MEMWRITE_INTEGRAL;
			break;
		case DIRECTIVE_WORD:
			currentValueTypeSpecifier = DIRECTIVE_WORD;
			currentByteAlignment = SIZE_WORD;
			currentAction = ACTION_MEMWRITE_INTEGRAL;
			break;
		case DIRECTIVE_FLOAT:
			currentValueTypeSpecifier = DIRECTIVE_FLOAT;
			currentByteAlignment = SIZE_FLOAT;
			currentAction = ACTION_MEMWRITE_INTEGRAL;
			break;
		case DIRECTIVE_DOUBLE:
			currentValueTypeSpecifier = DIRECTIVE_DOUBLE;
			currentByteAlignment = SIZE_DOUBLE;
			currentAction = ACTION_MEMWRITE_INTEGRAL;
			break;

		//Memory value type specifiers (string)
		case DIRECTIVE_ASCII:
			currentValueTypeSpecifier = DIRECTIVE_ASCII;
			currentByteAlignment = SIZE_BYTE;
			currentAction = ACTION_MEMWRITE_STRING;
			break;
		case DIRECTIVE_ASCIIZ:
			currentValueTypeSpecifier = DIRECTIVE_ASCIIZ;
			currentByteAlignment = SIZE_BYTE;
			currentAction = ACTION_MEMWRITE_STRING;
			break;

		//Memory alignment specifiers
		case DIRECTIVE_ALIGN:
			currentAction = ACTION_ALIGN;
			break;
		case DIRECTIVE_SPACE:
			currentByteAlignment = SIZE_BYTE;
			currentAction = ACTION_SPACE;
			break;
		case DIRECTIVE_INCLUDE:

			break;
		case DIRECTIVE_EXTERN:

			break;
		case DIRECTIVE_GLOBL:

			break;
		case DIRECTIVE_SET:

			break;
		case DIRECTIVE_MACRO:

			break;
		case DIRECTIVE_END_MACRO:

			break;
		case DIRECTIVE_EQV:

			break;
		default:

			break;
	}
}


void Assembler::alignRawProgram(){
	for(int lineNum=0; lineNum<program.size(); lineNum++){
		string line = program[lineNum];

		string token = parser.extractFirstToken(line);
		while(parser.tokenIsDirective(token) || parser.tokenIsLabel(token)){
			parser.extractAndRemoveFirstToken(line, token);
			if(parser.tokenIsLabel(token)){
				string labelName = parser.getLabelName(token);
				labelsToAssign.push_back(labelName);
			}else if(parser.tokenIsDirective(token)){
				applyDirective(token);
			}
			token = parser.extractFirstToken(line);
			if(token == ""){break;}
		}
		
		if(line == "" && currentAction != ACTION_DECLARE_SEGMENT){
			continue; //if programLine is all consumed, skip to next
		}
		//consume literal token
		ProgramAtom atom;
		string mappedProgramString;
		switch(currentAction){
			case ACTION_INIT:
				{
				//cout << "Error Assembler::converRawProgramToMemoryMappedProgram ACTION_INIT executed\n";
				}
				break;
			case ACTION_DECLARE_SEGMENT:
				{
					virtualAddr addr = getCurrentMemoryLocation();
					mappedProgramString = parser.getDirectiveName(currentMemorySegment);
					atom.addr = addr;
					atom.token = mappedProgramString;
					atom.type = currentMemorySegment;
					alignedProgram.push_back(atom);
					switch(currentMemorySegment){
						case DIRECTIVE_DATA:
							currentAction = ACTION_INIT;
							break;
						case DIRECTIVE_TEXT:
							currentAction = ACTION_INSTRUCTION_ENCODE;
							break;
						case DIRECTIVE_KDATA:
							currentAction = ACTION_INIT;
							break;
						case DIRECTIVE_KTEXT:
							currentAction = ACTION_INSTRUCTION_ENCODE;
							break;
					}
				}
				break;
			case ACTION_MEMWRITE_INTEGRAL:
				{
					alignSegmentTop();
					flushLabelBuffer();

					vector<string> literalTokens = parser.collectableLiteralListExplode(line);
					alignLiteralTokenList(literalTokens, line);
					currentAction = ACTION_INIT;
				}
				break;
			case ACTION_MEMWRITE_STRING:
				{
					flushLabelBuffer();
					int i=0;
					while(line[i] != '"'){i++;}
					string stringLiteral = line.substr(i);
					string rawString = parser.literals.getStringLiteralValue(stringLiteral);

					mappedProgramString = parser.literals.getRawStringLiteralValue(rawString);
					atom.addr = getCurrentMemoryLocation();
					atom.token = mappedProgramString;
					atom.type = currentValueTypeSpecifier;
					alignedProgram.push_back(atom);
					
					virtualAddr segmentIncrementSize = rawString.length() * SIZE_BYTE;
					if(currentValueTypeSpecifier == DIRECTIVE_ASCIIZ){
						segmentIncrementSize+=2;
					}

					incrementSegmentTop(segmentIncrementSize);
					currentAction = ACTION_INIT;
				}
				break;
			case ACTION_ALIGN:
				{
					currentByteAlignment = parser.literals.getLiteralValue(token);
					alignSegmentTop();
					currentAction = ACTION_INIT;
					//align
				}
				break;
			case ACTION_SPACE:
				{
					currentByteAlignment = SIZE_BYTE;
					alignSegmentTop();
					flushLabelBuffer();

					parser.extractAndRemoveFirstToken(line, token);
					uint32_t spaceSize = parser.literals.getLiteralValue(token);

					atom.token = parser.literals.getDecimalLiteralString(spaceSize);
					atom.addr = getCurrentMemoryLocation();
					atom.type = DIRECTIVE_SPACE;
					alignedProgram.push_back(atom);

					incrementSegmentTop(spaceSize);
					currentAction = ACTION_INIT;
				}
				break;
			case ACTION_INSTRUCTION_ENCODE:
				{
					currentByteAlignment = SIZE_WORD;
					alignSegmentTop();
					flushLabelBuffer();

					atom.addr = getCurrentMemoryLocation();
					atom.token = line;	//instruction full line
					atom.type = DIRECTIVE_INSTRUCTION;
					alignedProgram.push_back(atom);

					incrementSegmentTop(SIZE_WORD);
				}
				break;
			default:
				
				break;
		}
	}
}





void Assembler::flushLabelBuffer(){
	for(int i=0; i<labelsToAssign.size(); i++){
		virtualAddr addr = memorySegmentTopArray[currentMemorySegment];
		addLabelAddress(labelsToAssign[i], addr);

		ProgramAtom atom;
		atom.addr = addr;
		atom.token = labelsToAssign[i];
		atom.type = DIRECTIVE_LABEL;

		alignedProgram.push_back(atom);
	}
	labelsToAssign.clear();
}

void Assembler::alignSegmentTop(){
	while(memorySegmentTopArray[currentMemorySegment] % currentByteAlignment != 0){
		memorySegmentTopArray[currentMemorySegment]++;
	}
}
void Assembler::incrementSegmentTop(virtualAddr val){
	memorySegmentTopArray[currentMemorySegment] += val;
}
virtualAddr Assembler::getCurrentMemoryLocation(){
	return memorySegmentTopArray[currentMemorySegment];
}



void Assembler::alignLiteralTokenList(vector<string> const &literalTokens, string currentLine){
	virtualAddr memorySegmentTopIncrementationSize = 0;
	for(int tokenNum=0; tokenNum<literalTokens.size(); tokenNum++){
		//init string to ".datatype	|[insert literals here]"
		string mappedProgramString;

		string currentLiteralToken = literalTokens[tokenNum];
		bool terminateLine = false;
		switch(currentValueTypeSpecifier){
			case DIRECTIVE_BYTE:
				{
					memorySegmentTopIncrementationSize = SIZE_BYTE;
					char val = parser.literals.getLiteralValue(currentLiteralToken);

					mappedProgramString = parser.literals.getCharLiteralString(val);
				}
				break;
			case DIRECTIVE_HALF:
				{
					memorySegmentTopIncrementationSize = SIZE_HALF;
					uint16_t val = parser.literals.getLiteralValue(currentLiteralToken);
					mappedProgramString = parser.literals.getDecimalLiteralString(val);
				}
				break;
			case DIRECTIVE_WORD:
				{
					//Standard literal value + instructions addon
					memorySegmentTopIncrementationSize = SIZE_WORD;
					if(parser.tokenIsInstructionName(currentLiteralToken)){
						//Add instruction
						mappedProgramString = currentLine;
						terminateLine = true;
						break;
					}
					uint32_t val = parser.literals.getLiteralValue(currentLiteralToken);
					mappedProgramString = parser.literals.getDecimalLiteralString(val);
				}
				break;
			case DIRECTIVE_FLOAT:
				{
					memorySegmentTopIncrementationSize = SIZE_FLOAT;
					float val = parser.literals.getLiteralValue(currentLiteralToken);
					mappedProgramString = parser.literals.getFloatLiteralString(val);
				}
				break;
			case DIRECTIVE_DOUBLE:
				{
					memorySegmentTopIncrementationSize = SIZE_DOUBLE;
					double val = parser.literals.getLiteralValue(currentLiteralToken);
					mappedProgramString = parser.literals.getFloatLiteralString(val);
				}
				break;
			default:

				break;
		}
		virtualAddr addr = getCurrentMemoryLocation();
		ProgramAtom atom;
		atom.addr = addr;
		atom.token = mappedProgramString;
		atom.type = currentValueTypeSpecifier;
		alignedProgram.push_back(atom);
		incrementSegmentTop(memorySegmentTopIncrementationSize);
		if(terminateLine){break;} //exit for loop
	}


}



void Assembler::writeAlignedRawProgramToDisk(string fileName){
	ofstream file = ofstream(fileName);
	if(!file.is_open()){return;}
	for(int i=0; i<alignedProgram.size(); i++){
		ProgramAtom atom = alignedProgram[i];
		DIRECTIVE type = atom.type;
		bool tokenIsSegmentName = type <= DIRECTIVE_KTEXT;
		bool tokenIsLabel = type == DIRECTIVE_LABEL;
		bool tokenIsInstruction = type == DIRECTIVE_INSTRUCTION;
		if(tokenIsLabel){
			file << atom.token << ':';
			file << '\n';
			continue;
		}else if(tokenIsSegmentName){
			file << '\n';
			file << parser.getDirectiveName(type);
			file << '\n';
			file << '\n';
			continue;
		}else{
			file << parser.literals.getHexLiteralString(atom.addr);
			file << ':';
			file << '\t';
			if(!tokenIsInstruction){file << parser.getDirectiveName(type) << '\t';}
			file << atom.token;
			file << '\n';
		}
	}

	file.close();
}



//Post-processing
void Assembler::replaceEqv(){
	vector<pair<string, string>> eqvDB;
	for(int programLine=0; programLine<program.size(); programLine++){
		string line = program[programLine];
		string token;
		parser.extractAndRemoveFirstToken(line, token);
		if(token == ".eqv"){
			string eqvName;
			parser.extractAndRemoveFirstToken(line, eqvName);
			string eqvValue = parser.trim(line);
			pair<string, string> eqvAtom = make_pair(eqvName, eqvValue);
			eqvDB.push_back(eqvAtom);
		}
	}
	for(int programLine=0; programLine<program.size(); programLine++){
		string line = program[programLine];
		string token = parser.extractFirstToken(line);
		if(token == ".eqv"){continue;}

		pair<string, string>* largestMatchingEqv = NULL;
		for(int i=0; i<eqvDB.size(); i++){
			if(parser.indexOf(program[programLine], eqvDB[i].first) != -1){
				if(largestMatchingEqv == NULL){
					largestMatchingEqv = &eqvDB[i];
				}else{
					if(largestMatchingEqv->first.length() < eqvDB[i].first.length()){
						largestMatchingEqv = &eqvDB[i];
					}
				}
			}
		}
		if(largestMatchingEqv != NULL){
			program[programLine] = parser.replace(program[programLine], largestMatchingEqv->first, largestMatchingEqv->second);
		}
	}
	int asdfjkasdkfjsd  = 1;
}


void Assembler::pseudoInstructionReplace(){
	for(int i=0; i<alignedProgram.size(); i++){
		ProgramAtom atom = alignedProgram[i];
		string line = atom.token;
		if(atom.type == DIRECTIVE_INSTRUCTION){
			string mnemonic = parser.extractFirstToken(atom.token);
			mnemonic = parser.toLower(mnemonic);
			if(parser.tokenIsPseudoInstructionName(mnemonic)){
				int pseudoInstructionNumber = parser.getPseudoInstructionNameNumber(mnemonic);
				int numInsertedLines = parser.getPseudoInstructionNumberOfLinesToInsert(mnemonic);
				vector<string> tokenizedInstruction = parser.tokenizeInstruction(line);
				switch(pseudoInstructionNumber){
					case 0:
						{
							//bge
							string registerName1 = tokenizedInstruction[1];
							string registerName2 = tokenizedInstruction[2];
							string labelName = tokenizedInstruction[3];
							string line1 = "slt\t$at, " + registerName1 + ", " + registerName2;
							string line2 = "beq\t$at, $zero, " + labelName;
							alignedProgram[i].token = line1;
							alignedProgram[i+1].token = line2;
						}
						break;
					case 1:
						{
							//bgt

						}
						break;
					case 2:
						{
							//ble

						}
						break;
					case 3:
						{
							//blt

						}
						break;
					case 4:
						{
							//clear

						}
						break;
					case 5:
						{
							//div

						}
						break;
					case 6:
						{
							//la
							string labelName = tokenizedInstruction[2];
							virtualAddr labelAddr = getLabelAddress(labelName);
							virtualAddr msb = labelAddr >> (NUM_BITS_IN_VIRTUAL_ADDR / 2);
							virtualAddr lsb = labelAddr & 0x0000FFFF;
							string msbHex = parser.literals.getHexLiteralString(msb);
							string lsbHex = parser.literals.getHexLiteralString(lsb);
							string registerName = tokenizedInstruction[1];
							string line1 = "lui\t" + registerName + ", " + msbHex;
							string line2 = "ori\t" + registerName + ", " + registerName + ", " + lsbHex;
							alignedProgram[i].token = line1;
							alignedProgram[i+1].token = line2;
						}
						break;
					case 7:
						{
							//li
							string immediateString = tokenizedInstruction[2];
							uint32_t immediateVal = parser.literals.getLiteralValue(immediateString);
							virtualAddr msb = immediateVal >> (NUM_BITS_IN_WORD / 2);
							virtualAddr lsb = immediateVal & 0x0000FFFF;
							string msbHex = parser.literals.getHexLiteralString(msb);
							string lsbHex = parser.literals.getHexLiteralString(lsb);
							string registerName = tokenizedInstruction[1];
							string line1 = "lui\t" + registerName + ", " + msbHex;
							string line2 = "ori\t" + registerName + ", " + registerName + ", " + lsbHex;
							alignedProgram[i].token = line1;
							alignedProgram[i+1].token = line2;

						}
						break;
					case 8:
						{
							//move

						}
						break;
					case 9:
						{
							//mul

						}
						break;
					case 10:
						{
							//neg

						}
						break;
					case 11:
						{
							//not

						}
						break;
					case 12:
						{
							//push

						}
						break;
					case 13:
						{
							//pop

						}
						break;
					case 14:
						{
							//peak

						}
						break;
					case 15:
						{
							//rem

						}
						break;
					case 16:
						{
							//sge

						}
						break;
					case 17:
						{
							//sgt

						}
						break;
					default:

						break;
				}
				i += numInsertedLines;
			}else{

			}
		}else{

		}
	}
}


void Assembler::replaceLabels(){
	for(int i=0; i<alignedProgram.size(); i++){
		ProgramAtom atom = alignedProgram[i];
		if(atom.type == DIRECTIVE_INSTRUCTION){
		//Modified replacement
			string mnemonic = parser.extractFirstToken(atom.token);
			mnemonic = parser.toLower(mnemonic);
			bool isBranch = parser.tokenIsBranchInstructionName(mnemonic);
			bool isJump = parser.tokenIsJumpInstructionName(mnemonic);
			vector<string> instructionTokens = parser.tokenizeInstruction(atom.token);
			if(isBranch || isJump){
				string lastToken = instructionTokens[instructionTokens.size() - 1];
				virtualAddr labelAddr = getLabelAddress(lastToken);
				virtualAddr instructionAddr = atom.addr;
				virtualAddr immediateVal;
				if(isBranch){
					int32_t offset = labelAddr - instructionAddr - 4;	//pc still increments by 4 on branches
					offset >>= 2;
					immediateVal = (virtualAddr)offset;
				}else if(isJump){
					immediateVal = (labelAddr & 0x0FFFFFFF) >> 2;
				}
				string immediateString = parser.literals.getHexLiteralString(immediateVal);
				instructionTokens[instructionTokens.size() - 1] = immediateString;
				string newInstructionString = parser.combineInstructionTokens(instructionTokens);
				alignedProgram[i].token = newInstructionString;
			}else{
				//Standard text replacement
				for(int labelNum=0; labelNum<labelNames.size(); labelNum++){
					instructionTokens.clear();
					instructionTokens = parser.tokenizeInstruction(alignedProgram[i].token);
					bool labelWasReplaced = false;
					for(int tokenNum = 1; tokenNum < instructionTokens.size(); tokenNum++){
						if(tokenIsInLabelDB(instructionTokens[tokenNum])){
							string instructionToken = instructionTokens[tokenNum];
							virtualAddr labelAddress = getLabelAddress(instructionToken);
							string immediateHexString = parser.literals.getHexLiteralString(labelAddress);
							instructionTokens[tokenNum] = immediateHexString;
							labelWasReplaced = true;
						}
					}
					if(labelWasReplaced){
						string newInstructionString = parser.combineInstructionTokens(instructionTokens);
						alignedProgram[i].token = newInstructionString;
					}
				}
			}
		}else{

		}
	}
}




//VirtualMemory mapping
void Assembler::mapAlignedProgramToVirtualMemory(){
	for(int i=0; i<alignedProgram.size(); i++){
		ProgramAtom atom = alignedProgram[i];
		virtualAddr tokenAddr = atom.addr;
		switch(alignedProgram[i].type){
			case DIRECTIVE_DATA:
				{
					//do nothing
				}
				break;
			case DIRECTIVE_TEXT:
				{
					//do nothing
				}
				break;
			case DIRECTIVE_KDATA:
				{
					//do nothing
				}
				break;
			case DIRECTIVE_KTEXT:
				{
					//do nothing
				}
				break;
			case DIRECTIVE_BYTE:
				{
					char val = parser.literals.getLiteralValue(atom.token);
					size_t size = sizeof(val);
					virtualMemory.writeToVirtualMemorySpace(tokenAddr, size, &val);
				}
				break;
			case DIRECTIVE_HALF:
				{
					int16_t val = parser.literals.getLiteralValue(atom.token);
					size_t size = sizeof(val);
					virtualMemory.writeToVirtualMemorySpace(tokenAddr, size, &val);
				}
				break;
			case DIRECTIVE_WORD:
				{
					int32_t val = parser.literals.getLiteralValue(atom.token);
					size_t size = sizeof(val);
					virtualMemory.writeToVirtualMemorySpace(tokenAddr, size, &val);
				}
				break;
			case DIRECTIVE_FLOAT:
				{
					float val = parser.literals.getLiteralValue(atom.token);
					size_t size = sizeof(val);
					virtualMemory.writeToVirtualMemorySpace(tokenAddr, size, &val);
				}
				break;
			case DIRECTIVE_DOUBLE:
				{
					double val = parser.literals.getLiteralValue(atom.token);
					size_t size = sizeof(val);
					virtualMemory.writeToVirtualMemorySpace(tokenAddr, size, &val);
				}
				break;
			case DIRECTIVE_ASCII:
				{
					string val = parser.literals.getRawStringLiteralValue(atom.token);
					size_t size = val.length();
					virtualMemory.writeToVirtualMemorySpace(tokenAddr, size, (void*)val.c_str());
				}
				break;
			case DIRECTIVE_ASCIIZ:
				{
					string val = parser.literals.getRawStringLiteralValue(atom.token);
					size_t size = val.length();
					char nullTerm = '\0';
					virtualMemory.writeToVirtualMemorySpace(tokenAddr, size, (void*)val.c_str());
					virtualMemory.writeToVirtualMemorySpace(tokenAddr + size, sizeof(nullTerm), &nullTerm);
				}
				break;
			case DIRECTIVE_SPACE:
				{
					size_t size = parser.literals.getLiteralValue(atom.token);
					char* emptySpace = new char[size];
					memset(emptySpace, 0, size);
					virtualMemory.writeToVirtualMemorySpace(tokenAddr, size, emptySpace);
					delete emptySpace;
				}
				break;
			case DIRECTIVE_LABEL:
				{
					//do nothing
				}
				break;
			case DIRECTIVE_INSTRUCTION:
				{
					Instruction instruction = encoder->buildInstruction(atom.token);
					instr bin = instruction.getBin();
					size_t size = sizeof(bin);

					virtualMemory.writeToVirtualMemorySpace(tokenAddr, size, &bin);
				}
				break;
			default:
				{
					cout << "Error [void mapAlignedProgramToVirtualMemory()] invalid DIRECTIVE_%TYPE%";
					getchar();
				}
				break;
		}
	}
}