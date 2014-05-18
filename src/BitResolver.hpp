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
		InstructionData* getInstructionData(string i);
		InstructionData* getInstructionData(instr i);
		

	private:
		//Methods
		InstructionData* getInstructionDataFromBinarySearchTree(BRInstructionDataNode* head, string i);
		void addInstructionToBinarySearchTree(BRInstructionDataNode* &head, BRInstructionDataNode* newNode);
		
		bool lessThan(string lhs, string rhs);
		bool equalTo(string lhs, string rhs);
		bool greaterThan(string lhs, string rhs);

		bool bitIsMatch(InstructionData* id, string bitStr);

		int compareInstructionData(string lhs, string rhs);
		int compareBits(char lhs, char rhs);
		
		void deleteBinarySearchTree(BRInstructionDataNode* head);
		void clearCache();

		//Members
		InstructionData* cache[INSTRUCTION_NUMBER_TABLE_SIZE];
		BRInstructionDataNode* table[INSTRUCTION_NUMBER_TABLE_SIZE];
};



#endif
