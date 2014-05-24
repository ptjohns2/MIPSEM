#ifndef __INSTRUCTION_DATA_HPP__
#define __INSTRUCTION_DATA_HPP__

#include <string>
#include <vector>

using namespace std;

class InstructionData{
	public:
		InstructionData(string);
		~InstructionData();

		int getInstructionID() const;

		string getName() const;
		string getFormat() const;

		string getOpcode() const;
		string getFields() const;

		vector<string> getParameters() const;

		bool isEncodedNormally() const;
		bool isDecodedNormally() const;
		bool changesPC() const;

		string getFull() const;


		
	private:
		int instructionID;

		string name;
		string format;

		string opcode;	//	31,26
		string fields;	//	25,0
		
		vector<string> parameters;

		bool normalEncoding;
		bool normalDecoding;
		bool instructionChangesPC;

		string full;
};




#endif
