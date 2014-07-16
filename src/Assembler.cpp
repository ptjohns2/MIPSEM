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
	currentAction = INIT;
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

void Assembler::applyDirective(string directive, string nextToken){
	uint32_t directiveNumber = parser.getDirectiveNumber(directive);
	switch(directiveNumber){
		//Primary memory segments
		case DIRECTIVE_DATA:
			currentMemorySegment = DIRECTIVE_DATA;
			break;
		case DIRECTIVE_TEXT:
			currentMemorySegment = DIRECTIVE_TEXT;
			break;
		case DIRECTIVE_KDATA:
			currentMemorySegment = DIRECTIVE_KDATA;
			break;
		case DIRECTIVE_KTEXT:
			currentMemorySegment = DIRECTIVE_KTEXT;
			break;

		//Memory value type specifiers (integral)
		case DIRECTIVE_BYTE:
			currentValueTypeSpecifier = DIRECTIVE_BYTE;
			currentByteAlignment = SIZE_BYTE;
			currentAction = MEMWRITE;
			break;
		case DIRECTIVE_HALF:
			currentValueTypeSpecifier = DIRECTIVE_HALF;
			currentByteAlignment = SIZE_HALF;
			currentAction = MEMWRITE;
			break;
		case DIRECTIVE_WORD:
			currentValueTypeSpecifier = DIRECTIVE_WORD;
			currentByteAlignment = SIZE_WORD;
			currentAction = MEMWRITE;
			break;
		case DIRECTIVE_FLOAT:
			currentValueTypeSpecifier = DIRECTIVE_FLOAT;
			currentByteAlignment = SIZE_FLOAT;
			currentAction = MEMWRITE;
			break;
		case DIRECTIVE_DOUBLE:
			currentValueTypeSpecifier = DIRECTIVE_DOUBLE;
			currentByteAlignment = SIZE_DOUBLE;
			currentAction = MEMWRITE;
			break;

		//Memory value type specifiers (string)
		case DIRECTIVE_ASCII:
			currentValueTypeSpecifier = DIRECTIVE_ASCII;
			currentByteAlignment = SIZE_BYTE;
			currentAction = MEMWRITE;
			break;
		case DIRECTIVE_ASCIIZ:
			currentValueTypeSpecifier = DIRECTIVE_ASCIIZ;
			currentByteAlignment = SIZE_BYTE;
			currentAction = MEMWRITE;
			break;

		//Memory alignment specifiers
		case DIRECTIVE_ALIGN:
			currentByteAlignment = parser.literals.getDecimalLiteralValue(nextToken);
			currentAction = MEMALIGN;
			break;
		case DIRECTIVE_SPACE:
			currentAction = ALLOC;
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

}













