#ifndef __INSTRUCTION_DATA_HPP__
#define __INSTRUCTION_DATA_HPP__

#include <string>
#include "types.hpp"
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class InstructionData{
	public:
		InstructionData();
		InstructionData(string);
		~InstructionData();

		int getId();

		string getName();
		string getFormat();

		string getOpcode();
		string getFields();

		vector<string> getArguments();
		
		string getFull();
		string getHashableName();

		bool bitIsMatch(string);
		bool stringIsMatch(string);

		static string generateHashableName(string name, vector<string> arguments);

	private:
		int id;

		string name;
		string format;

		string opcode;	//	31,26
		string fields;	//	25,0
		
		vector<string> arguments;
		bool abnormalEncoding;
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
		string hashableName;
};




#endif
