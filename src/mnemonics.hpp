#ifndef __MNEMONICS_HPP__
#define __MNEMONICS_HPP__

#include "types.hpp"

#include <string>

using namespace std;


class mnemonics{
	public:
		
		//Methods


		static bitrange getParameterBitrange(string parameter);

		static bool parameterIsRegister(string parameter);
		
		static bool parameterIsGPRegister(string parameter);
		static string getGPRegisterName(int index);
		static int getGPRegisterIndex(string parameter);

		static bool parameterIsFPRegister(string parameter);
		static string getFPRegisterName(int index);
		static int getFPRegisterIndex(string parameter);

		static bool parameterIsImmediate(string parameter);
		static bool parameterIsSignedImmediate(string parameter);
		static bool parameterIsUnsignedImmediate(string parameter);
		
		int getArgumentValue(string argument);


		//Members
		static string const GPRegisterNames[];
		static string const FPRegisterNames[];



	private:






};








#endif