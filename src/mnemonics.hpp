#ifndef __MNEMONICS_HPP__
#define __MNEMONICS_HPP__

#include "types.hpp"

#include <string>

using namespace std;


class mnemonics{
	public:
		
		//Methods
		static string getGPRegName(ufield num);
		static int getGPRegIndex(string name);

		static string getFPRegName(ufield num);
		static int getFPRegIndex(string name);

		static bitRange getBitRangeFromParameter(string fieldName);

		
		//Members
		static string const GPRegisterNames[];
		static string const FPRegisterNames[];



	private:






};








#endif