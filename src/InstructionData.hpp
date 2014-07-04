#ifndef __INSTRUCTION_DATA_HPP__
#define __INSTRUCTION_DATA_HPP__

#include "types.hpp"

#include <string>
#include <tuple>
#include <vector>

using namespace std;

class InstructionData{
	public:
		InstructionData();
		InstructionData(int id, string name, int opcode, instr face, instr mask, char at1, bool ap1, int asb1, int aeb1, char at2, bool ap2, int asb2, int aeb2, char at3, bool ap3, int asb3, int aeb3, char at4, bool ap4, int asb4, int aeb4, bool normalEncoding, bool normalDecoding, bool instructionChangesPC);
		~InstructionData();
		
		int getID() const;
		string getName() const;

		int getOpcode() const;
		instr getFace() const;
		instr getMask() const;

		char getParameterType(int) const;

		bool parameterIsLiteral(int) const;
		bool parameterIsSignedLiteral(int) const;
		bool parameterIsUnsignedLiteral(int) const;

		bool parameterIsRegister(int) const;
		bool parameterIsGPRegister(int) const;
		bool parameterIsFPRegister(int) const;
		
		bool paramHasParenthises(int) const;

		int getParameterStartBit(int) const;
		int getParameterEndBit(int) const;
		
		int getNumParameters() const;

		bool isEncodedNormally() const;
		bool isDecodedNormally() const;
		bool changesPC() const;

		
	private:		
		int id;
		string name;

		int opcode;
		instr face;
		instr mask;

		char parameterTypes[NUMBER_OF_PARAMETERS];
		bool parameterParenthises[NUMBER_OF_PARAMETERS];
		int parameterStartBits[NUMBER_OF_PARAMETERS];
		int parameterEndBits[NUMBER_OF_PARAMETERS];
		int numParameters;

		bool normalEncoding;
		bool normalDecoding;
		bool instructionChangesPC;
};




#endif
