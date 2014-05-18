#ifndef __INSTRUCTION_DATA_HPP__
#define __INSTRUCTION_DATA_HPP__

#include <string>
#include <vector>

using namespace std;

class InstructionData{
	public:
		InstructionData(string);
		~InstructionData();

		int getId();

		string getName();
		string getFormat();

		string getOpcode();
		string getFields();

		vector<string> getArguments();

		bool isEncodedNormally();
		bool isDecodedNormally();
		
		string getFull();


		
	private:
		int id;

		string name;
		string format;

		string opcode;	//	31,26
		string fields;	//	25,0
		
		vector<string> arguments;

		bool normalEncoding;
		bool normalDecoding;
	/*	//	Position syntax: (msb = 31, lsb = 0)
		//	$ptr	.val
		$[%msb%,%lsb%]			//
		$%register_mnemonic%	//
		.[%msb%,%lsb%]			//
		.imm					//
		offset (base)			//	left paired with (right) always
		_						//	'_' means no argument		*/
		//non-config info

		string full;
};




#endif
