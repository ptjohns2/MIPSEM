#include "BitResolver.hpp"

#include "parse.hpp"

#include <bitset>
#include <cassert>
#include <iostream>

//	Constructors
BitResolver::BitResolver(InstructionDataBank* bank){
	for(int i=0; i<INSTRUCTION_NUMBER_TABLE_SIZE; i++){
		table[i] = NULL;
	}
	addInstructionDataBank(bank);
}
BitResolver::~BitResolver(){
	for(int i=0; i<INSTRUCTION_NUMBER_TABLE_SIZE; i++){
		deleteBinarySearchTree(table[i]);
	}
}


//	public Methods
void BitResolver::addInstructionData(InstructionData* id){
	int opcode = parse::binStrToUnsignedDecInt(id->getOpcode());
	BRInstructionDataNode* node = new BRInstructionDataNode();

	node->left = NULL;
	node->right = NULL;
	node->val = id;
	addInstructionToBinarySearchTree(table[opcode], node);
}

void BitResolver::addInstructionDataBank(InstructionDataBank* bank){
	for(int i=0; i<bank->size(); i++){
		addInstructionData(bank->bank[i]);
	}
}

InstructionData* BitResolver::getInstructionData(string i){
	string opcodeStr = i.substr(0,6);
	instr opcode = parse::binStrToUnsignedDecInt(opcodeStr);
	BRInstructionDataNode* binPtr = table[opcode];
	InstructionData* retPtr = getInstructionDataFromBinarySearchTree(binPtr, i);
	return retPtr;
}

InstructionData* BitResolver::getInstructionData(instr i){
	string bitfield = parse::decIntToBinStr(i);
	return getInstructionData(bitfield);
}


//	private Methods
InstructionData* BitResolver::getInstructionDataFromBinarySearchTree(BRInstructionDataNode* head, string i){
	if(head != NULL){
		if(binStrIsMatch(head->val, i)){
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


bool BitResolver::lessThan(string lhs, string rhs){
	return compareInstructionData(lhs, rhs) < 0;
}
bool BitResolver::equalTo(string lhs, string rhs){
	return compareInstructionData(lhs, rhs) == 0;
}
bool BitResolver::greaterThan(string lhs, string rhs){
	return compareInstructionData(lhs, rhs) > 0;
}


bool BitResolver::binStrIsMatch(InstructionData* id, string bitStr){
	string full = id->getFull();
	//Test funct first
	for(int i=26; i<32; i++){
		if(full[i] != 'x'){
			if(full[i] != bitStr[i]){
				return false;
			}
		}
	}
	//Now test the rest left to right
	for(int i=6; i<26; i++){
		if(full[i] != 'x'){
			if(full[i] != bitStr[i]){
				return false;
			}
		}
	}
	//Test opcode  last since binary search trees binned by opcode
	for(int i=0; i<6; i++){
		//If opcode char here is a don't care 'x', skip this test
		if(full[i] != 'x'){
			if(full[i] != bitStr[i]){
				return false;
			}
		}
	}
	//If none of these conditions failed, return true for a match
	return true;
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
	if(head == NULL){return;}
	deleteBinarySearchTree(head->left);
	deleteBinarySearchTree(head->right);
	delete head;
}


