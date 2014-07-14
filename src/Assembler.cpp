#include "Assembler.hpp"

#include "Parser.hpp"

#include <iostream>
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

}
void Assembler::deinit(){

}




void Assembler::addLabelAddress(string label, virtualAddr addr){
	labelDB[label] = addr;
}
virtualAddr Assembler::getLabelAddress(string label){
	unordered_map<string, virtualAddr>::iterator iter = labelDB.find(label);
	if(iter != labelDB.end()){
		return (*iter).second;
	}else{
		cout << "error LabelDB::get(string label) @" << label << '\n';
		getchar();
		return -1;
	}
}



void Assembler::loadProgramFromFile(string fileName){
	fstream file = fstream(fileName);
	if(!file.is_open()){return;}
	string tmpProgramLine;
	while(getline(file, tmpProgramLine)){
		tmpProgramLine = Parser::removeComment(tmpProgramLine);
		if(tmpProgramLine != ""){
			program.push_back(tmpProgramLine);
		}
	}
}















