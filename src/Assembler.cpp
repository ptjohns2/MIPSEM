#include "Assembler.hpp"

#include "parse.hpp"

#include <fstream>

Assembler::Assembler()
	:	memory()
{
	init();
}
Assembler::~Assembler(){
	deinit();
}
void Assembler::init(){
	program.clear();
	labelAddressDB.clear();
}
void Assembler::deinit(){

}



void Assembler::loadProgramFromFile(string fileName){
	fstream file = fstream(fileName);
	if(!file.is_open()){return;}
	string tmpProgramLine;
	while(getline(file, tmpProgramLine)){
		tmpProgramLine = parse::sanitizeInstruction(tmpProgramLine);
		program.push_back(tmpProgramLine);
	}
}















