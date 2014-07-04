#ifndef __BITRESOLVER_HPP__
#define __BITRESOLVER_HPP__

#include "InstructionData.hpp"
#include "InstructionDataBank.hpp"
#include "types.hpp"

#include <string>

struct BRInstructionDataNode{
		InstructionData* val;
		BRInstructionDataNode* left;
		BRInstructionDataNode* right;
};

class BitResolver{
	public:
		//Constructors
		BitResolver(InstructionDataBank* bank);
		~BitResolver();
		
		//Methods
		void addInstructionData(InstructionData* id);
		void addInstructionDataBank(InstructionDataBank* bank);
		InstructionData* getInstructionData(instr i);
		

	private:
		//Methods
		static InstructionData* getInstructionDataFromBinarySearchTree(BRInstructionDataNode* head, instr i);
		static void addInstructionToBinarySearchTree(BRInstructionDataNode* &head, BRInstructionDataNode* newNode);
		
		static bool lessThan(instr lhs, instr rhs);
		static bool equalTo(instr lhs, instr rhs);
		static bool greaterThan(instr lhs, instr rhs);

		static bool instrIsMatch(InstructionData* id, instr i);

		static int compareInstructionData(instr lhs, instr rhs);
		
		static void deleteBinarySearchTree(BRInstructionDataNode* head);

		//Members
		BRInstructionDataNode* table[INSTRUCTION_NUMBER_TABLE_SIZE];
};



#endif
