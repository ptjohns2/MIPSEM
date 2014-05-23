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
		static InstructionData* getInstructionDataFromBinarySearchTree(BRInstructionDataNode* head, string i);
		static void addInstructionToBinarySearchTree(BRInstructionDataNode* &head, BRInstructionDataNode* newNode);
		
		static bool lessThan(string lhs, string rhs);
		static bool equalTo(string lhs, string rhs);
		static bool greaterThan(string lhs, string rhs);

		static bool binStrIsMatch(InstructionData* id, string bitStr);

		static int compareInstructionData(string lhs, string rhs);
		static int compareBits(char lhs, char rhs);
		
		static void deleteBinarySearchTree(BRInstructionDataNode* head);

		//Members
		BRInstructionDataNode* table[INSTRUCTION_NUMBER_TABLE_SIZE];
};



#endif
