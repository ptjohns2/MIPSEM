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
		InstructionData
			(
				int id,
				string name, 
				string format, 
				string opcode,
				string fields,
				string pos1,
				string pos2, 
				string pos3,
				string pos4
			);
		InstructionData(string);
		~InstructionData();

		int getId();

		string getName();
		string getFormat();

		string getOpcode();
		string getFields();
		
		string getPos1();
		string getPos2();
		string getPos3();
		string getPos4();

		
		string getFull();
		string getHashableName();

		bool bitIsMatch(string);
		bool stringIsMatch(string);

		static string generateHashableName(string name, string pos1, string pos2, string pos3, string pos4);
		vector<string> tokenizeString(string str);
		string toString();

	private:
		int id;

		string name;
		string format;

		string opcode;	//	31,26
		string fields;	//	25,0
		
		string pos1;
		string pos2;
		string pos3;
		string pos4;
	/*	//	Position syntax: (msb = 31, lsb = 0)
		//	$ptr	.val
		$[%msb%,%lsb%]			//
		$%register_mnemonic%	//
		.[%msb%,%lsb%]			//
		.imm					//
		offset(base)			//	.offset, $base
		%1% %2%					//	space seperated tokens shows that the value in that argument goes to BOTH %1% and %2%
		_						//	'_' means no argument		*/
		//non-config info
		string full;
		string hashableName;



};




#endif
