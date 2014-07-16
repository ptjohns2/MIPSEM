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
			currentAction = ACTION_INIT;
			break;
		case DIRECTIVE_TEXT:
			currentMemorySegment = DIRECTIVE_TEXT;
			currentAction = ACTION_INSTRUCTION_ENCODE;
			break;
		case DIRECTIVE_KDATA:
			currentMemorySegment = DIRECTIVE_KDATA;
			currentAction = ACTION_INIT;
			break;
		case DIRECTIVE_KTEXT:
			currentMemorySegment = DIRECTIVE_KTEXT;
			currentAction = ACTION_INSTRUCTION_ENCODE;
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
	for(int i=0; i<program.size(); i++){
		string line = program[i];
		string token;
		while(parser.extractAndRemoveFirstToken(line, token)){
			if(parser.tokenIsLabel(token)){
				labelsToAssign.push_back(token);
				continue;	//skip switch statement
			}else if(parser.tokenIsDirective(token)){
				applyDirective(token);
				continue;	//skip switch statement
			}else{
				//consume literal token
				pair<virtualAddr, string> tmpMemoryMapPair;
				string mappedProgramString;
				switch(currentAction){
					case ACTION_INIT:
						{
						cout << "Error Assembler::converRawProgramToMemoryMappedProgram ACTION_INIT executed";
						getchar();
						}
						break;
					case ACTION_MEMWRITE_INTEGRAL:
						{
						virtualAddr memorySegmentTopIncrementationSize = 0;
						alignSegmentTop();
						assignUnassignedLabels();
						switch(currentValueTypeSpecifier){
							case DIRECTIVE_BYTE:
								{
								char val = parser.literals.getLiteralValue(token);
								mappedProgramString = parser.literals.getCharLiteralString(val);
								memorySegmentTopIncrementationSize = SIZE_BYTE;
								}
								break;
							case DIRECTIVE_HALF:
								{
								uint16_t val = parser.literals.getLiteralValue(token);
								mappedProgramString = parser.literals.getDecimalLiteralString(val);
								memorySegmentTopIncrementationSize = SIZE_HALF;
								}
								break;
							case DIRECTIVE_WORD:
								{
								uint32_t val = parser.literals.getLiteralValue(token);
								mappedProgramString = parser.literals.getDecimalLiteralString(val);
								memorySegmentTopIncrementationSize = SIZE_WORD;
								}
								break;
							case DIRECTIVE_FLOAT:
								{
								float val = parser.literals.getLiteralValue(token);
								mappedProgramString = parser.literals.getFloatLiteralString(val);
								memorySegmentTopIncrementationSize = SIZE_FLOAT;
								}
								break;
							case DIRECTIVE_DOUBLE:
								{
								double val = parser.literals.getLiteralValue(token);
								mappedProgramString = parser.literals.getFloatLiteralString(val);
								memorySegmentTopIncrementationSize = SIZE_DOUBLE;
								}
								break;
							default:

								break;
						}
						tmpMemoryMapPair.first = getCurrentMemoryLocation();
						tmpMemoryMapPair.second = mappedProgramString;
						memoryMappedProgram.push_back(tmpMemoryMapPair);
						incrementSegmentTop(memorySegmentTopIncrementationSize);
						}
						break;
					case ACTION_MEMWRITE_STRING:
						{
						assignUnassignedLabels();
						int i=0;
						while(line[i] != '"'){i++;}
						string stringLiteral = line.substr(i);
						string rawString = parser.literals.getStringLiteralValue(stringLiteral);
						mappedProgramString = parser.literals.getStringLiteralString(rawString);

						incrementSegmentTop(rawString.length() * SIZE_BYTE);
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
						assignUnassignedLabels();
						parser.extractAndRemoveFirstToken(line, token);
						uint32_t spaceSize = parser.literals.getLiteralValue(token);
						incrementSegmentTop(spaceSize);
						currentAction = ACTION_INIT;
						}
						break;
					case ACTION_INSTRUCTION_ENCODE:
						{
	

						}
						break;
					default:
				
						break;
				}
			}
		}
	}
}





void Assembler::assignUnassignedLabels(){
	for(int i=0; i<labelsToAssign.size(); i++){
		virtualAddr addr = memorySegmentTopArray[currentMemorySegment];
		addLabelAddress(labelsToAssign[i], addr);
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




