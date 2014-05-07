#ifndef __BITRESOLVER_HPP__
#define __BITRESOLVER_HPP__

#include "types.hpp"
#include "InstructionData.hpp"
#include "InstructionDataBank.hpp"
#include "Instruction.hpp"

#include <string>
#include <vector>

class BRInstructionDataNode{
	public:
		InstructionData* val;
		BRInstructionDataNode* left;
		BRInstructionDataNode* right;
};


class BitResolver{
	public:
		//Methods
		BitResolver();
		BitResolver(InstructionDataBank* bank);
		~BitResolver();

		void addInstructionData(InstructionData* id);
		void addInstructionDataBank(InstructionDataBank* bank);
		InstructionData* getInstructionData(string i);
		InstructionData* getInstructionData(instr i);
		
		string toString();

		//Members
		int num;
		InstructionData* cache[INSTRUCTION_NUMBER_TABLE_SIZE];
		BRInstructionDataNode* table[INSTRUCTION_NUMBER_TABLE_SIZE];

	private:
		string branchToString(BRInstructionDataNode* head);

		bool lessThan(string lhs, string rhs);
		bool equalTo(string lhs, string rhs);
		bool greaterThan(string lhs, string rhs);

		int compareInstructionData(string lhs, string rhs);
		int compareBits(char lhs, char rhs);
		InstructionData* getInstructionDataFromBinarySearchTree(BRInstructionDataNode* head, string i);
		void addInstructionToBinarySearchTree(BRInstructionDataNode* &head, BRInstructionDataNode* newNode);

		void deleteBinarySearchTree(BRInstructionDataNode* head);
		void clearCache();
};



#endif
