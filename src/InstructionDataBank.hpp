#ifndef __INSTRUCTIONDATABANK_HPP__
#define __INSTRUCTIONDATABANK_HPP__


#include "InstructionData.hpp"


using namespace std;

class InstructionDataBank{
	public:
		//Methods
		//	Constructors
		InstructionDataBank();
		~InstructionDataBank();
		int size() const;

		InstructionData* get(int);


	private:
		//Members
		InstructionData bank[NUMBER_OF_INSTRUCTIONS];

};






#endif