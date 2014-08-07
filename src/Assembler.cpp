#include "Assembler.hpp"

#include "BitManip.hpp"
#include "Exceptions.hpp"
#include "Parser.hpp"
#include "types.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <tuple>
#include <sstream>

#define ASSEMBLER_RESERVED_PREFIX					("@_")
#define ASSEMBLER_REPLACEMENT_PSEUDOINSTRUCTION_PAD	("@_PSEUDOINSTRUCTION")
#define ASSEMBLER_MACRO_LABEL_PREFIX				("@_MACRO_LABEL_")

MacroAtom::MacroAtom(){

}
MacroAtom::MacroAtom(vector<ProgramLine> definition){
	string token;
	//extract name
	string header = definition[0].text;
	Parser::extractAndRemoveFirstToken(header, token);
	stringstream ss = stringstream(header);

	getline(ss, this->name, '(');
	string parameterList;
	getline(ss, parameterList, ')');

	parameters = Parser::commaSeparatedLiteralListExplode(parameterList);

	for(int i=1; i<definition.size()-1; i++){
		this->body.push_back(definition[i]);
	}

	numTimesUsed = 0;
}
MacroAtom::~MacroAtom(){

}
void MacroAtom::init(){

}
void MacroAtom::deinit(){

}

vector<ProgramLine> MacroAtom::buildMacro(vector<string> const &arguments){
	vector<ProgramLine> replacedBody = getUniquelyLabelledMacroBody();
	for(int lineNum=0; lineNum<replacedBody.size(); lineNum++){
		for(int argNum=0; argNum<parameters.size(); argNum++){
			replacedBody[lineNum].text = Parser::replace(replacedBody[lineNum].text, parameters[argNum], arguments[argNum]);
		}
	}
	return replacedBody;
}
vector<ProgramLine> MacroAtom::buildMacro(string programLine){
	string jnk, argument;
	stringstream ss(programLine);
	getline(ss, jnk, '(');
	string argumentList;
	getline(ss, argumentList, ')');
	return buildMacro(Parser::commaSeparatedLiteralListExplode(argumentList));
}

vector<ProgramLine> MacroAtom::getUniquelyLabelledMacroBody(){
	numTimesUsed++;
	vector<ProgramLine> newBody = body;
	vector<string> labelNamesFound;
	for(int lineNum=0; lineNum<newBody.size(); lineNum++){
		if(Parser::tokenIsLabel(newBody[lineNum].text)){
			labelNamesFound.push_back(Parser::getLabelName(newBody[lineNum].text));
		}
	}
	struct stringCompareFunctionPointer {
		bool operator()(const string& lhs, const string& rhs){
			return lhs.size() < rhs.size();
		}
	};
	stringCompareFunctionPointer stringComparer;
	std::sort(labelNamesFound.begin(), labelNamesFound.end(), stringComparer);

	for(int lineNum=0; lineNum<newBody.size(); lineNum++){
		for(int labelNum=0; labelNum<labelNamesFound.size(); labelNum++){
			if(Parser::indexOf(newBody[lineNum].text, labelNamesFound[labelNum]) != -1){
				string newLabelName = ASSEMBLER_MACRO_LABEL_PREFIX + std::to_string(numTimesUsed) + "_" + labelNamesFound[labelNum];
				newBody[lineNum].text = Parser::replace(newBody[lineNum].text, labelNamesFound[labelNum], newLabelName);
			}
		}
	}

	return newBody;
}

bool MacroAtom::lineIsMacroCall(string programLine){
	stringstream ss(programLine);
	string potentialName;
	getline(ss, potentialName, '(');
	string argumentList;
	getline(ss, argumentList, ')');
	if(Parser::commaSeparatedLiteralListExplode(argumentList).size() != parameters.size()){
		return false;
	}
	return potentialName == name;
}




///////////////////////////

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
	currentByteAlignment = SIZE_BYTES_WORD;
	
	defaultObjectNamePostfix = "tmpObj.obj"; 
	defaultAlignedProgramNamePostfix = ".obj.txt"; 

}
void Assembler::deinit(){

}
void Assembler::reset(){
	virtualMemory.reset();

	init();
}
void Assembler::setEncoder(Encoder* encoder){
	this->encoder = encoder;
}

string Assembler::assemble(string fileName){
	bool invalidateAssembly = false;
	try{
		loadProgramFromFile(fileName);

		splitLabels();
		replaceEqv();
		extractMacroDefinitions();
		replaceMacros();
		pseudoInstructionPad();

		alignRawProgram();
		pseudoInstructionReplace();
		replaceLabels();
		
		writeAlignedRawProgramToDisk(fileName + defaultAlignedProgramNamePostfix);
		mapAlignedProgramToVirtualMemory();

		virtualMemory.serialize(defaultObjectNamePostfix);
	}catch(AssemblerException &e){
		string message = e.toString();
		cout << '\n' << message << '\n';
		invalidateAssembly = true;
	}catch(InvalidTokenException &e){
		cout << "ERROR [Assembler::assemble(string fileName)]: HANDLE INVALID TOKEN EXCEPTION IN ASSEMBLER!!!:\t" + e.toString();
		getchar();
	}
	if(recoverableExceptions.size() != 0 || invalidateAssembly){
		for(int i=0; i<recoverableExceptions.size(); i++){
			cout << recoverableExceptions[i].toString() << '\n';
		}
		throw AssemblerException(NULL, "Unable to assemble", fileName);
	}
	
	return defaultObjectNamePostfix;
}

void Assembler::loadProgramFromFile(string fileName, ProgramLine* programLine){
	fstream file = fstream(fileName);
	if(!file.is_open()){
		//EXCEPTION
		string error = "I'm sorry Dave, I'm afraid I can't open that file";
		string offendingToken = fileName;
		throw AssemblerException(programLine, error, offendingToken);
		return;
	}
	string tmpProgramLine;
	uint32_t lineNumber = 0;
	while(getline(file, tmpProgramLine)){
		tmpProgramLine = parser.sanitizeProgramLine(tmpProgramLine);
		
		if(tmpProgramLine != ""){
			ProgramLine programLine;
			programLine.fileName = fileName;
			programLine.lineNumber = lineNumber;
			programLine.text = tmpProgramLine;
			program.push_back(programLine);
		}

		string token = parser.toLower(parser.extractFirstToken(tmpProgramLine));
		if(token == ".include"){
			parser.extractAndRemoveFirstToken(tmpProgramLine, token);
			string nestedFileName = parser.trim(tmpProgramLine);
			nestedFileName = parser.removeNestedQuotes(nestedFileName);
			nestedFileName = parser.trim(nestedFileName);
			ProgramLine* programLinePtr = (program.size() == 0)? NULL : &program[program.size() - 1];
			loadProgramFromFile(nestedFileName, programLinePtr);
		}
		
		lineNumber++;
	}
}





//Pre-processing

void Assembler::splitLabels(){
	for(int lineNum=0; lineNum<program.size(); lineNum++){
		ProgramLine programLine = program[lineNum];
		string token = parser.extractFirstToken(programLine.text);
		vector<string> labels;
		while(token != ""){
			if(!parser.tokenIsLabel(token)){break;}
			parser.extractAndRemoveFirstToken(programLine.text, token);
			ProgramLine newProgramLine;
			newProgramLine = programLine;
			newProgramLine.text = token;

			program.insert(program.begin() + lineNum, newProgramLine);
			lineNum++;
			token = parser.extractFirstToken(programLine.text);
		}
		if(programLine.text == ""){
			program.erase(program.begin() + lineNum);
			lineNum--;
		}else{
			program[lineNum] = programLine;
		}
	}
}

void Assembler::replaceEqv(){
	for(int lineNum=0; lineNum<program.size(); lineNum++){		
		ProgramLine programLine = program[lineNum];
		string token;
		parser.extractAndRemoveFirstToken(programLine.text, token);
		if(token == ".eqv"){
			string eqvName;
			parser.extractAndRemoveFirstToken(programLine.text, eqvName);
			string eqvValue = parser.trim(programLine.text);
			pair<string, string> eqvAtom = make_pair(eqvName, eqvValue);
			eqvDB.push_back(eqvAtom);
		}

		for(int laterlineNum = lineNum + 1; laterlineNum<program.size(); laterlineNum++){
			ProgramLine laterProgramLine = program[laterlineNum];
			string token = parser.extractFirstToken(laterProgramLine.text);

			string immuneFront;
			string replacedBack;
			if(token == ".eqv"){
				parser.extractAndRemoveFirstToken(laterProgramLine.text, immuneFront);
				immuneFront += '\t';
				string nextToken;
				parser.extractAndRemoveFirstToken(laterProgramLine.text, nextToken);
				immuneFront += nextToken + '\t';
				replacedBack = laterProgramLine.text;
			}else{
				immuneFront = "";
				replacedBack = laterProgramLine.text;
			}
			//TODO - just order eqvDB first and go backwards so it's always biggest, then ALL will match
			struct stringCompareFunctionPointer {
				bool operator()(const pair<string, string>& lhs, const pair<string, string>& rhs){
					return lhs.first.size() < rhs.first.size();
				}
			};
			stringCompareFunctionPointer stringComparer;
			std::sort(eqvDB.begin(), eqvDB.end(), stringComparer);

			for(int i=0; i<eqvDB.size(); i++){
				if(parser.indexOf(laterProgramLine.text, eqvDB[i].first) != -1){
					replacedBack = parser.replace(replacedBack, eqvDB[i].first, eqvDB[i].second);
					program[laterlineNum].text = immuneFront + replacedBack;
				}
			}
		}
	}
}

void Assembler::extractMacroDefinitions(){
	for(int lineNum=0; lineNum<program.size(); lineNum++){
		vector<ProgramLine> macroLines;
		ProgramLine programLine = program[lineNum];
		string token = parser.extractFirstToken(programLine.text);
		if(token == ".macro"){
			macroLines.push_back(programLine);
			program.erase(program.begin() + lineNum);
			while(parser.extractFirstToken(program[lineNum].text) != ".end_macro" && lineNum < program.size()){
				macroLines.push_back(program[lineNum]);
				program.erase(program.begin() + lineNum);
			}
			if(program[lineNum].text != ".end_macro"){
				//EXCEPTION
				string error = "Macro not matched with .end_macro directive before EOF";
				string offendingToken = programLine.text;
				throw AssemblerException(&program[lineNum], error, offendingToken);
				return;
			}
			macroLines.push_back(program[lineNum]);
			program.erase(program.begin() + lineNum);
			MacroAtom atom = MacroAtom(macroLines);
			macroDB.push_back(atom);
			lineNum--;
		}else{

		}
	}
}

void Assembler::replaceMacros(){
	for(int lineNum=0; lineNum<program.size(); lineNum++){
		ProgramLine programLine = program[lineNum];
		for(int macroAtomNumber=0; macroAtomNumber<macroDB.size(); macroAtomNumber++){
			if(macroDB[macroAtomNumber].lineIsMacroCall(programLine.text)){
				vector<ProgramLine> builtMacro = macroDB[macroAtomNumber].buildMacro(programLine.text);
				program.insert(program.begin() + lineNum, builtMacro.begin(), builtMacro.end());
				program.erase(program.begin() + lineNum + builtMacro.size());
				lineNum--;
				break;
			}
		}
	}
}

void Assembler::pseudoInstructionPad(){	
	for(int lineNum=0; lineNum<program.size(); lineNum++){
		ProgramLine programLine = program[lineNum];

		string token = parser.toLower(parser.extractFirstToken(programLine.text));
		int pseudoInstructionNumber = 0;
		if(parser.tokenIsPseudoInstructionName(token)){
			pseudoInstructionNumber = parser.getPseudoInstructionNameNumber(token);
		}else{
			continue;
		}
		int numLinesToInsert = parser.getPseudoInstructionNumberOfLinesToInsert(token);
		for(int numInsertedLines = 0; numInsertedLines < numLinesToInsert; numInsertedLines++){
			lineNum++;
			//Modify tmp ProgramLine programLine and insert into program as padding
			programLine.text = ASSEMBLER_REPLACEMENT_PSEUDOINSTRUCTION_PAD;
			program.insert(program.begin() + lineNum, programLine);
		}
	}
}






bool Assembler::tokenIsInLabelDB(string token){
	return labelMap.find(token) != labelMap.end();
}
void Assembler::addLabelAddress(string label, virtualAddr addr){
	if(tokenIsInLabelDB(label)){
		//EXCEPTION
		throw InvalidTokenException("Duplicate label", label);
	}
	labelMap[label] = addr;
	labelNames.push_back(label);
}
virtualAddr Assembler::getLabelAddress(string label){
	unordered_map<string, virtualAddr>::iterator iter = labelMap.find(label);
	if(iter != labelMap.end()){
		return (*iter).second;
	}else{
		//EXCEPTION
		throw InvalidTokenException("Label", label);
	}
	return 0;
}

void Assembler::applyDirective(string directive, ProgramLine* programLine){
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
			currentByteAlignment = SIZE_BYTES_BYTE;
			currentAction = ACTION_MEMWRITE_INTEGRAL;
			break;
		case DIRECTIVE_HALF:
			currentValueTypeSpecifier = DIRECTIVE_HALF;
			currentByteAlignment = SIZE_BYTES_HWORD;
			currentAction = ACTION_MEMWRITE_INTEGRAL;
			break;
		case DIRECTIVE_WORD:
			currentValueTypeSpecifier = DIRECTIVE_WORD;
			currentByteAlignment = SIZE_BYTES_WORD;
			currentAction = ACTION_MEMWRITE_INTEGRAL;
			break;
		case DIRECTIVE_FLOAT:
			currentValueTypeSpecifier = DIRECTIVE_FLOAT;
			currentByteAlignment = SIZE_BYTES_FLOAT;
			currentAction = ACTION_MEMWRITE_INTEGRAL;
			break;
		case DIRECTIVE_DOUBLE:
			currentValueTypeSpecifier = DIRECTIVE_DOUBLE;
			currentByteAlignment = SIZE_BYTES_DOUBLE;
			currentAction = ACTION_MEMWRITE_INTEGRAL;
			break;

		//Memory value type specifiers (string)
		case DIRECTIVE_ASCII:
			currentValueTypeSpecifier = DIRECTIVE_ASCII;
			currentByteAlignment = SIZE_BYTES_BYTE;
			currentAction = ACTION_MEMWRITE_STRING;
			break;
		case DIRECTIVE_ASCIIZ:
			currentValueTypeSpecifier = DIRECTIVE_ASCIIZ;
			currentByteAlignment = SIZE_BYTES_BYTE;
			currentAction = ACTION_MEMWRITE_STRING;
			break;

		//Memory alignment specifiers
		case DIRECTIVE_ALIGN:
			currentAction = ACTION_ALIGN;
			break;
		case DIRECTIVE_SPACE:
			currentByteAlignment = SIZE_BYTES_BYTE;
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
			//EXCEPTION
			string error = ERROR_UNRECOGNIZED_DIRECTIVE;
			string offendingToken = directive;
			addException(AssemblerException(programLine, error, offendingToken));
			break;
	}
}


void Assembler::alignRawProgram(){
	for(int lineNum=0; lineNum<program.size(); lineNum++){
		ProgramLine programLine = program[lineNum];

		string token = parser.extractFirstToken(programLine.text);
		if(parser.tokenIsLabel(token)){
			string labelName = parser.getLabelName(token);
			programLine.text = labelName;
			labelsToAssign.push_back(&program[lineNum]);
			continue;
		}
		while(parser.tokenIsDirective(token)){
			parser.extractAndRemoveFirstToken(programLine.text, token);
			applyDirective(token, &programLine);
			token = parser.extractFirstToken(programLine.text);
			if(token == ""){break;}
		}
		
		if(programLine.text == "" && currentAction != ACTION_DECLARE_SEGMENT){
			continue; //if programLine is all consumed, skip to next line unless you need to declare segment in following actions
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
					atom.programLine = &program[lineNum];
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

					vector<string> literalTokens = parser.commaSeparatedLiteralListExplode(programLine.text);
					alignLiteralTokenList(literalTokens, programLine.text, &program[lineNum]);
					currentAction = ACTION_INIT;
				}
				break;
			case ACTION_MEMWRITE_STRING:
				{
					flushLabelBuffer();
					int i=0;
					while(programLine.text[i] != '"'){i++;}

					string stringLiteral = programLine.text.substr(i);
					string rawString;
					try{
						rawString = parser.literals.getStringLiteralValue(stringLiteral);
					}catch(InvalidTokenException &e){
						//EXCEPTION
						string error = ERROR_INVALID_STRING_LITERAL;
						string offendingToken = rawString;
						addException(AssemblerException(&program[lineNum], error, offendingToken));
						continue;
					}

					mappedProgramString = parser.literals.getRawStringLiteralValue(rawString);
					atom.addr = getCurrentMemoryLocation();
					atom.token = mappedProgramString;
					atom.type = currentValueTypeSpecifier;
					atom.programLine = &program[lineNum];
					alignedProgram.push_back(atom);
					
					virtualAddr segmentIncrementSize = rawString.length() * SIZE_BYTES_BYTE;
					if(currentValueTypeSpecifier == DIRECTIVE_ASCIIZ){
						segmentIncrementSize+=2;
					}

					incrementSegmentTop(segmentIncrementSize);
					currentAction = ACTION_INIT;
				}
				break;
			case ACTION_ALIGN:
				{
					try{
						currentByteAlignment = parser.literals.getFixedPointLiteralValue(token);
					}catch(InvalidTokenException &e){
						string error = ERROR_INVALID_ALIGNMENT_VALUE;
						string offendingToken = token;
						addException(AssemblerException(&program[lineNum], error, token));
						continue;
					}
					alignSegmentTop();
					currentAction = ACTION_INIT;
				}
				break;
			case ACTION_SPACE:
				{
					currentByteAlignment = SIZE_BYTES_BYTE;
					alignSegmentTop();
					flushLabelBuffer();

					parser.extractAndRemoveFirstToken(programLine.text, token);
					uint32_t spaceSize = 0;
					try{
						spaceSize = parser.literals.getFixedPointLiteralValue(token);
					}catch(InvalidTokenException &e){
						//EXCEPTION
						string error = ERROR_INVALID_SPACE_VALUE;
						string offendingToken = token;
						addException(AssemblerException(&program[lineNum], error, offendingToken));
						continue;
					}

					atom.token = parser.literals.getDecimalLiteralString(spaceSize);
					atom.addr = getCurrentMemoryLocation();
					atom.type = DIRECTIVE_SPACE;
					atom.programLine = &program[lineNum];
					alignedProgram.push_back(atom);

					incrementSegmentTop(spaceSize);
					currentAction = ACTION_INIT;
				}
				break;
			case ACTION_INSTRUCTION_ENCODE:
				{
					currentByteAlignment = SIZE_BYTES_WORD;
					alignSegmentTop();
					flushLabelBuffer();

					atom.addr = getCurrentMemoryLocation();
					atom.token = programLine.text;	//instruction full line
					atom.type = DIRECTIVE_INSTRUCTION;
					atom.programLine = &program[lineNum];
					alignedProgram.push_back(atom);

					incrementSegmentTop(SIZE_BYTES_WORD);
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
		try{
			addLabelAddress(parser.getLabelName(labelsToAssign[i]->text), addr);
		}catch(InvalidTokenException &e){
			//EXCEPTION
			string error = ERROR_INVALID_LABEL;
			string offendingToken = labelsToAssign[i]->text;
			addException(AssemblerException(labelsToAssign[i], error, offendingToken));
			continue;
		}

		ProgramAtom atom;
		atom.addr = addr;
		atom.token = parser.getLabelName(labelsToAssign[i]->text);
		atom.type = DIRECTIVE_LABEL;
		atom.programLine = labelsToAssign[i];
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



void Assembler::alignLiteralTokenList(vector<string> const &literalTokens, string currentLine, ProgramLine* programLine){
	virtualAddr memorySegmentTopIncrementationSize = 0;

	for(int tokenNum=0; tokenNum<literalTokens.size(); tokenNum++){
		//init string to ".datatype	|[insert literals here]"
		string mappedProgramString;
		string currentLiteralToken = literalTokens[tokenNum];

		bool terminateLine = false;
		try{
			switch(currentValueTypeSpecifier){
				//TODO: semi-redundant case switch, fix with array to index into to find SIZE of token
				case DIRECTIVE_BYTE:
					{
						memorySegmentTopIncrementationSize = SIZE_BYTES_BYTE;
						char val = parser.literals.getLiteralValue(currentLiteralToken);
						mappedProgramString = parser.literals.getCharLiteralString(val);
					}
					break;
				case DIRECTIVE_HALF:
					{
						memorySegmentTopIncrementationSize = SIZE_BYTES_HWORD;
						uint16_t val = parser.literals.getLiteralValue(currentLiteralToken);
						mappedProgramString = parser.literals.getDecimalLiteralString(val);
					}
					break;
				case DIRECTIVE_WORD:
					{
						//Standard literal value + instructions addon
						memorySegmentTopIncrementationSize = SIZE_BYTES_WORD;
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
						memorySegmentTopIncrementationSize = SIZE_BYTES_FLOAT;
						float val = parser.literals.getFloatLiteralValue(currentLiteralToken);
						mappedProgramString = parser.literals.getFloatLiteralString(val);
					}
					break;
				case DIRECTIVE_DOUBLE:
					{
						memorySegmentTopIncrementationSize = SIZE_BYTES_DOUBLE;
						double val = parser.literals.getDoubleLiteralValue(currentLiteralToken);
						mappedProgramString = parser.literals.getFloatLiteralString(val);
					}
					break;
				default:

					break;
			}
		}catch(InvalidTokenException &e){
			//EXCEPTION
			string error = ERROR_INVALID_LITERAL;
			string offendingToken = currentLiteralToken;
			addException(AssemblerException(programLine, error, offendingToken));
			continue;
		}
		virtualAddr addr = getCurrentMemoryLocation();
		ProgramAtom atom;
		atom.addr = addr;
		atom.token = mappedProgramString;
		atom.type = currentValueTypeSpecifier;
		atom.programLine = programLine;

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
		bool tokenIsStringLiteral = type == DIRECTIVE_ASCII || DIRECTIVE_ASCII; 
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
			string val = tokenIsStringLiteral? parser.literals.getStringLiteralString(atom.token) : atom.token;
			file << val;
			file << '\n';
		}
	}

	file.close();
}


//Post-processing
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
					//TODO: add exceptions for incorrect number of instruction arguments
					case 0:
						{
							//bge	$reg1, $reg2, label
							if(tokenizedInstruction.size() != 4){addException(AssemblerException(atom.programLine, ERROR_INVALID_PSEUDOINSTRUCTION, atom.programLine->text));continue;}
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
							//bgt	$reg1, $reg2, label
							if(tokenizedInstruction.size() != 4){addException(AssemblerException(atom.programLine, ERROR_INVALID_PSEUDOINSTRUCTION, atom.programLine->text));continue;}
							string registerName1 = tokenizedInstruction[1];
							string registerName2 = tokenizedInstruction[2];
							string labelName = tokenizedInstruction[3];
							string line1 = "slt\t$at, " + registerName2 + ", " + registerName1;
							string line2 = "bne\t$at, $zero, " + labelName;
							alignedProgram[i].token = line1;
							alignedProgram[i+1].token = line2;
						}
						break;
					case 2:
						{
							//ble	$reg1, $reg2, label
							if(tokenizedInstruction.size() != 4){addException(AssemblerException(atom.programLine, ERROR_INVALID_PSEUDOINSTRUCTION, atom.programLine->text));continue;}
							string registerName1 = tokenizedInstruction[1];
							string registerName2 = tokenizedInstruction[2];
							string labelName = tokenizedInstruction[3];
							string line1 = "slt\t$at, " + registerName2 + ", " + registerName1;
							string line2 = "beq\t$at, $zero, " + labelName;
							alignedProgram[i].token = line1;
							alignedProgram[i+1].token = line2;

						}
						break;
					case 3:
						{
							//blt	$reg1, $reg2, label
							if(tokenizedInstruction.size() != 4){addException(AssemblerException(atom.programLine, ERROR_INVALID_PSEUDOINSTRUCTION, atom.programLine->text));continue;}
							string registerName1 = tokenizedInstruction[1];
							string registerName2 = tokenizedInstruction[2];
							string labelName = tokenizedInstruction[3];
							string line1 = "slt\t$at, " + registerName1 + ", " + registerName2;
							string line2 = "bne\t$at, $zero, " + labelName;
							alignedProgram[i].token = line1;
							alignedProgram[i+1].token = line2;
						}
						break;
					case 4:
						{
							//clear	$reg
							if(tokenizedInstruction.size() != 2){addException(AssemblerException(atom.programLine, ERROR_INVALID_PSEUDOINSTRUCTION, atom.programLine->text));continue;}
							string registerName1 = tokenizedInstruction[1];
							string line1 = "add\t" + registerName1 + ", $zero, $zero";
							alignedProgram[i].token = line1;
						}
						break;
					case 5:
						{
							//la	$reg, label
							if(tokenizedInstruction.size() != 3){addException(AssemblerException(atom.programLine, ERROR_INVALID_PSEUDOINSTRUCTION, atom.programLine->text));continue;}
							string labelName = tokenizedInstruction[2];
							if(!tokenIsInLabelDB(labelName)){
								//EXCEPTION
								string error = ERROR_UNRECOGNIZED_LABEL;
								string offendingToken = labelName;
								addException(AssemblerException(atom.programLine, error, offendingToken));
								continue;
							}
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
					case 6:
						{
							//li	$reg, imm
							if(tokenizedInstruction.size() != 3){addException(AssemblerException(atom.programLine, ERROR_INVALID_PSEUDOINSTRUCTION, atom.programLine->text));continue;}
							string immediateString = tokenizedInstruction[2];

							//EXCEPTION
							//TODO
							uint32_t immediateVal;
							try{
								immediateVal = parser.literals.getLiteralValue(immediateString);
							}catch(InvalidTokenException &e){
								string error = ERROR_INVALID_IMMEDIATE_LI;
								string offendingToken = immediateString;
								addException(AssemblerException(atom.programLine, error, offendingToken));
								continue;
							}
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
					case 7:
						{
							//move	$reg1, $reg2
							if(tokenizedInstruction.size() != 3){addException(AssemblerException(atom.programLine, ERROR_INVALID_PSEUDOINSTRUCTION, atom.programLine->text));continue;}
							string registerName1 = tokenizedInstruction[1];
							string registerName2 = tokenizedInstruction[2];
							string line1 = "add\t" + registerName1 + ", " + registerName2 + ", $zero";
							alignedProgram[i].token = line1;
						}
						break;
					case 8:
						{
							//neg	$reg1, $reg2
							if(tokenizedInstruction.size() != 3){addException(AssemblerException(atom.programLine, ERROR_INVALID_PSEUDOINSTRUCTION, atom.programLine->text));continue;}
							string registerName1 = tokenizedInstruction[1];
							string registerName2 = tokenizedInstruction[2];
							string line1 = "sub\t" + registerName1 + ", $zero, " + registerName2;
							alignedProgram[i].token = line1;
						}
						break;
					case 9:
						{
							//not	$reg1, $reg2
							if(tokenizedInstruction.size() != 3){addException(AssemblerException(atom.programLine, ERROR_INVALID_PSEUDOINSTRUCTION, atom.programLine->text));continue;}
							string registerName1 = tokenizedInstruction[1];
							string registerName2 = tokenizedInstruction[2];
							string line1 = "addi\t" + registerName1 + ", $zero, -1";
							string line2 = "xor\t" + registerName1 + ", " + registerName1 + "," + registerName2;
							alignedProgram[i].token = line1;
							alignedProgram[i+1].token = line2;
						}
						break;
						/*
						PUSH:
						sub $sp,$sp,4
						sw $t2,($sp)

						POP:
						lw $t2,($sp)
						addiu $sp,$sp,4
						*/
					case 10:
						{
							//push	$reg
							if(tokenizedInstruction.size() != 2){addException(AssemblerException(atom.programLine, ERROR_INVALID_PSEUDOINSTRUCTION, atom.programLine->text));continue;}
							string registerName1 = tokenizedInstruction[1];
							string line1 = "sub\t$sp, $sp, 4";
							string line2 = "sw\t" + registerName1 + ", 0($sp)";
							alignedProgram[i].token = line1;
							alignedProgram[i+1].token = line2;
						}
						break;
					case 11:
						{
							//pop	$reg
							if(tokenizedInstruction.size() != 2){addException(AssemblerException(atom.programLine, ERROR_INVALID_PSEUDOINSTRUCTION, atom.programLine->text));continue;}
							string registerName1 = tokenizedInstruction[1];
							string line1 = "lw\t" + registerName1 + ", 0($sp)";
							string line2 = "addi\t$sp, $sp, 4";
							alignedProgram[i].token = line1;
							alignedProgram[i+1].token = line2;
						}
						break;
					case 12:
						{
							//peak	$reg
							if(tokenizedInstruction.size() != 2){addException(AssemblerException(atom.programLine, ERROR_INVALID_PSEUDOINSTRUCTION, atom.programLine->text));continue;}
							string registerName = tokenizedInstruction[1];
							string line = "lw\t" + registerName + ", 0($sp)";
							alignedProgram[i].token = line;
						}
						break;
					case 13:
						{
							//rem

						}
						break;
					case 14:
						{
							//sge

						}
						break;
					case 15:
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
				if(!tokenIsInLabelDB(lastToken)){
					//EXCEPTION
					string error = ERROR_UNRECOGNIZED_LABEL;
					string offendingToken = lastToken;
					addException(AssemblerException(atom.programLine, error, offendingToken));
				}
				virtualAddr labelAddr = getLabelAddress(lastToken);
				virtualAddr instructionAddr = atom.addr;
				virtualAddr immediateVal = 0;
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
					//instructionTokens.clear();
					//instructionTokens = parser.tokenizeInstruction(alignedProgram[i].token);
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
					int32_t val;
					if(parser.tokenIsInstructionName(parser.extractFirstToken(atom.token))){
						instr bin;
						try{
							bin = encoder->buildInstruction(atom.token).getBin();
						}catch(InvalidTokenException &e){
							//EXCEPTION
							string error = ERROR_INVALID_INSTRUCTION;
							string offendingToken = atom.token;
							addException(AssemblerException(atom.programLine, error, offendingToken));
						}
						val = readMemAs<int32_t>(&bin);
					}else{
						val = parser.literals.getLiteralValue(atom.token);
					}
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
					instr bin = 0;
					try{
						Instruction instruction = encoder->buildInstruction(atom.token);
						bin = instruction.getBin();
					}catch(InvalidTokenException &e){
						string error = ERROR_INVALID_INSTRUCTION;
						string offendingToken = atom.token;
						addException(AssemblerException(atom.programLine, error, offendingToken));
					}
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



void Assembler::addException(AssemblerException const &e){
	//CONDITIONS TO REJECT ADDING
	//line is pseudo instruction pad line
	if(e.programLine->text == ASSEMBLER_REPLACEMENT_PSEUDOINSTRUCTION_PAD){
		return;
	}
	//Add
	recoverableExceptions.push_back(e);
}