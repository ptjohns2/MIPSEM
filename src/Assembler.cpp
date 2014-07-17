#include "Assembler.hpp"

#include "Parser.hpp"

#include <iostream>
#include <fstream>



Assembler::Assembler()
	:	memory(), parser()
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
void Assembler::globalReset(){
	localReset();

	memset(&memorySegmentTopArray[0], 0, sizeof(virtualAddr) * NUMBER_OF_MEMORY_SEGMENTS);

	globalLabelNames.clear();
	globalLabelMap.clear();
}
void Assembler::localReset(){
	memory.reset();
	program.clear();
	memoryMappedProgram.clear();
	labelNames.clear();
	labelMap.clear();
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






void Assembler::addLabelAddress(string label, virtualAddr addr){
	labelMap[label] = addr;
	labelNames.push_back(label);
}
virtualAddr Assembler::getLabelAddress(string label){
	unordered_map<string, virtualAddr>::iterator iter = labelMap.find(label);
	if(iter != labelMap.end()){
		return (*iter).second;
	}else{
		cout << "error LabelDB::get(string label) @" << label << '\n';
		getchar();
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


void Assembler::convertRawProgramToMemoryMappedProgram(){
	for(int lineNum=0; lineNum<program.size(); lineNum++){
		string line = program[lineNum];

		string token = parser.extractFirstToken(line);
		while(parser.tokenIsDirective(token) || parser.tokenIsLabel(token)){
			parser.extractAndRemoveFirstToken(line, token);
			if(parser.tokenIsLabel(token)){
				labelsToAssign.push_back(token);
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
				cout << "Error Assembler::converRawProgramToMemoryMappedProgram ACTION_INIT executed";
				}
				break;
			case ACTION_DECLARE_SEGMENT:
				{
					virtualAddr addr = getCurrentMemoryLocation();
					mappedProgramString = parser.getDirectiveName(currentMemorySegment);
					atom.addr = addr;
					atom.token = mappedProgramString;
					atom.type = currentMemorySegment;
					memoryMappedProgram.push_back(atom);
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
					assignUnassignedLabelsAndAddToMemoryMappedProgram();

					vector<string> literalTokens = parser.collectableLiteralListExplode(line);
					applyLiteralTokenList(literalTokens, line);
					currentAction = ACTION_INIT;
				}
				break;
			case ACTION_MEMWRITE_STRING:
				{
					assignUnassignedLabelsAndAddToMemoryMappedProgram();
					int i=0;
					while(line[i] != '"'){i++;}
					string stringLiteral = line.substr(i);
					string rawString = parser.literals.getStringLiteralValue(stringLiteral);

					mappedProgramString = parser.literals.getStringLiteralString(rawString);
					atom.addr = getCurrentMemoryLocation();
					atom.token = mappedProgramString;
					atom.type = currentValueTypeSpecifier;
					memoryMappedProgram.push_back(atom);
					
					virtualAddr segmentIncrementSize = rawString.length() * SIZE_BYTE;
					segmentIncrementSize += (currentValueTypeSpecifier == DIRECTIVE_ASCIIZ)? 1 : 0;

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
					assignUnassignedLabelsAndAddToMemoryMappedProgram();

					parser.extractAndRemoveFirstToken(line, token);
					uint32_t spaceSize = parser.literals.getLiteralValue(token);

					atom.token = parser.literals.getDecimalLiteralString(spaceSize);
					atom.addr = getCurrentMemoryLocation();
					atom.type = DIRECTIVE_SPACE;
					memoryMappedProgram.push_back(atom);

					incrementSegmentTop(spaceSize);
					currentAction = ACTION_INIT;
				}
				break;
			case ACTION_INSTRUCTION_ENCODE:
				{
					currentByteAlignment = SIZE_WORD;
					alignSegmentTop();
					assignUnassignedLabelsAndAddToMemoryMappedProgram();

					atom.addr = getCurrentMemoryLocation();
					atom.token = line;	//instruction full line
					atom.type = DIRECTIVE_INSTRUCTION;
					memoryMappedProgram.push_back(atom);

					incrementSegmentTop(SIZE_WORD);
				}
				break;
			default:
				
				break;
		}
	}
}





void Assembler::assignUnassignedLabelsAndAddToMemoryMappedProgram(){
	for(int i=0; i<labelsToAssign.size(); i++){
		virtualAddr addr = memorySegmentTopArray[currentMemorySegment];
		addLabelAddress(labelsToAssign[i], addr);
		ProgramAtom atom;
		atom.addr = addr;
		atom.token = labelsToAssign[i];
		atom.type = DIRECTIVE_LABEL;
		memoryMappedProgram.push_back(atom);
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



void Assembler::applyLiteralTokenList(vector<string> const &literalTokens, string currentLine){
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
					if(parser.tokenIsInstructionMnemonic(currentLiteralToken)){
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
		memoryMappedProgram.push_back(atom);
		incrementSegmentTop(memorySegmentTopIncrementationSize);
		if(terminateLine){break;} //exit for loop
	}


}



void Assembler::writeMemoryMappedProgramToDisk(string fileName){
	ofstream file = ofstream(fileName);
	if(!file.is_open()){return;}
	for(int i=0; i<memoryMappedProgram.size(); i++){
		ProgramAtom atom = memoryMappedProgram[i];
		DIRECTIVE type = atom.type;
		bool tokenIsSegmentName = type <= DIRECTIVE_KTEXT;
		bool tokenIsLabel = type == DIRECTIVE_LABEL;
		bool tokenIsInstruction = type == DIRECTIVE_INSTRUCTION;
		if(tokenIsLabel){
			file << atom.token;
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