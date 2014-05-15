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
		void add(string);

		InstructionData* operator[](const int index);

		//Members
		vector<InstructionData*> bank;
		int size;


	private:

};






#endif