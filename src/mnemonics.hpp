#ifndef __MNEMONICS_HPP__
#define __MNEMONICS_HPP__

#include <string>
#include "types.hpp"

using namespace std;


class mnemonics{
	public:
		
		//Methods
		static string getGPRegName(ufield num);
		static int getGPRegField(string name);

		static string getFPRegName(ufield num);
		static int getFPRegField(string name);

		static bitRange getBitRangeFromField(string fieldName);


		//Members
		static string const GPRegisterNames[];
		static string const FPRegisterNames[];



	private:






};








#endif