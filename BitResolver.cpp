#include "BitResolver.hpp"
#include <cassert>
#include <bitset>
#include "stringManip.hpp"

//class OpcodeResolver
//	Constructors
BitResolver::BitResolver(){
	clearCache();
}
BitResolver::BitResolver(InstructionDataBank* bank){
	clearCache();
	addInstructionDataBank(bank);
}
BitResolver::~BitResolver(){
	for(int i=0; i<INSTRUCTION_NUMBER_TABLE_SIZE; i++){
		deleteBinarySearchTree(table[i]);
	}
}

//	public Methods
void BitResolver::addInstructionData(InstructionData* id){
	int opcode = stringManip::binStrToDecInt(id->getOpcode());
	BRInstructionDataNode* node = new BRInstructionDataNode();

	node->left = NULL;
	node->right = NULL;
	node->val = id;
	addInstructionToBinarySearchTree(table[opcode], node);
}

void BitResolver::addInstructionDataBank(InstructionDataBank* bank){
	for(int i=0; i<bank->size; i++){
		addInstructionData(bank->bank[i]);
	}
}

void BitResolver::addInstructionToBinarySearchTree(BRInstructionDataNode* &head, BRInstructionDataNode* newNode){
	//base case
	if(head == NULL){
		head = newNode;
		return;
	}else{
		//recursive case
		if(lessThan(head->val->getFull(), newNode->val->getFull())){
			addInstructionToBinarySearchTree(head->right, newNode);
			return;
		}else{
			addInstructionToBinarySearchTree(head->left, newNode);
			return;
		}
	}
}

InstructionData* BitResolver::getInstructionData(string i){
	string opcodeStr = i.substr(0,6);
	instr opcode = stringManip::binStrToDecInt(opcodeStr.c_str());

	if(cache[opcode] != NULL){
		if(cache[opcode]->bitIsMatch(i)){
			return cache[opcode];
		}
	}

	BRInstructionDataNode* binPtr = table[opcode];
	InstructionData* retPtr = getInstructionDataFromBinarySearchTree(binPtr, i);
	cache[opcode] = retPtr;	//cache the result
	return retPtr;
}

InstructionData* BitResolver::getInstructionData(instr i){
	string bitfield = bitset<INSTRUCTIONSIZE>(i).to_string();
	InstructionData* retPtr = getInstructionData(bitfield);
	return retPtr;
}

InstructionData* BitResolver::getInstructionDataFromBinarySearchTree(BRInstructionDataNode* head, string i){
	if(head != NULL){
		if(head->val->bitIsMatch(i)){
			return head->val;
		}else{
			if(greaterThan(head->val->getFull(), i)){
				return getInstructionDataFromBinarySearchTree(head->left, i);
			}else{
				return getInstructionDataFromBinarySearchTree(head->right, i);
			}
		}
	}else{
		return NULL;
	}
}


//	private Methods

bool BitResolver::lessThan(string lhs, string rhs){
	return compareInstructionData(lhs, rhs) < 0;
}
bool BitResolver::equalTo(string lhs, string rhs){
	return compareInstructionData(lhs, rhs) == 0;
}
bool BitResolver::greaterThan(string lhs, string rhs){
	return compareInstructionData(lhs, rhs) > 0;
}



int BitResolver::compareInstructionData(string lhs, string rhs){
	assert(lhs.size() == rhs.size());

	//Test funct next
	for(int i=26; i<32; i++){
		int chk = compareBits(lhs[i], rhs[i]);
		if(chk != 0){return chk;}
	}
	//Now test the rest left to right
	for(int i=6; i<26; i++){
		int chk = compareBits(lhs[i], rhs[i]);
		if(chk != 0){return chk;}
	}
	//Test opcode LAST since bins are indexed by opcode
	for(int i=0; i<6; i++){
		int chk = compareBits(lhs[i], rhs[i]);
		if(chk != 0){return chk;}
	}
	//If none of these conditions failed, return true for a match
	return true;
}

int BitResolver::compareBits(char lhs, char rhs){
	if(lhs != 'x' && rhs != 'x'){
		if(lhs < rhs){
			return -1;
		}else if(lhs == rhs){
			return 0;
		}else if(lhs > rhs){
			return 1;
		}
	}else if(lhs != 'x' && rhs == 'x'){
		return 1;
	}else if(lhs == 'x' && rhs != 'x'){
		return -1;
	}else if(lhs == 'x' && rhs == 'x'){
		return 0;
	}

	cout << "error comparing bits " << lhs << '\t' << rhs;
	return 0;
}

void BitResolver::deleteBinarySearchTree(BRInstructionDataNode* head){
	if(head == NULL){
		return;
	}

	deleteBinarySearchTree(head->left);
	deleteBinarySearchTree(head->right);

	delete head;
}

void BitResolver::clearCache(){
	for(int i=0; i<INSTRUCTION_NUMBER_TABLE_SIZE; i++){
		table[i] = NULL;
		cache[i] = NULL;
	}
}


