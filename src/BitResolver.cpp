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
	int opcode = id->getOpcode();
	BRInstructionDataNode* node = new BRInstructionDataNode();

	node->left = NULL;
	node->right = NULL;
	node->val = id;
	addInstructionToBinarySearchTree(table[opcode], node);
}

void BitResolver::addInstructionDataBank(InstructionDataBank* bank){
	for(int i=0; i<bank->size(); i++){
		addInstructionData(bank->get(i));
	}
}


InstructionData* BitResolver::getInstructionData(instr ins){
	int opcode = ins >> (INSTRUCTIONSIZE - OPCODESIZE);
	BRInstructionDataNode* binPtr = table[opcode];
	InstructionData* retPtr = getInstructionDataFromBinarySearchTree(binPtr, ins);
	return retPtr;
}


//	private Methods
InstructionData* BitResolver::getInstructionDataFromBinarySearchTree(BRInstructionDataNode* head, instr ins){
	if(head != NULL){
		if(instrIsMatch(head->val, ins)){
			return head->val;
		}else{
			instr maskedInstr = ins & head->val->getMask();
			if(lessThan(head->val->getFace(), maskedInstr)){
				return getInstructionDataFromBinarySearchTree(head->right, ins);
			}else{
				return getInstructionDataFromBinarySearchTree(head->left, ins);
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
		instr maskedInstr = newNode->val->getFace() & head->val->getMask();
		if(lessThan(head->val->getFace(), maskedInstr)){
			addInstructionToBinarySearchTree(head->right, newNode);
			return;
		}else{
			addInstructionToBinarySearchTree(head->left, newNode);
			return;
		}
	}
}


bool BitResolver::lessThan(instr lhs, instr rhs){
	return compareInstructionData(lhs, rhs) < 0;
}
bool BitResolver::equalTo(instr lhs, instr rhs){
	return compareInstructionData(lhs, rhs) == 0;
}
bool BitResolver::greaterThan(instr lhs, instr rhs){
	return compareInstructionData(lhs, rhs) > 0;
}


bool BitResolver::instrIsMatch(InstructionData* id, instr ins){
	instr maskedInstr = ins & id->getMask();
	return id->getFace() == maskedInstr;
}


int BitResolver::compareInstructionData(instr lhs, instr rhs){
	return (lhs == rhs)? 0 : (	(lhs < rhs)? -1 : 1	);
	//return lhs - rhs;
}


void BitResolver::deleteBinarySearchTree(BRInstructionDataNode* head){
	if(head == NULL){return;}
	deleteBinarySearchTree(head->left);
	deleteBinarySearchTree(head->right);
	delete head;
}


