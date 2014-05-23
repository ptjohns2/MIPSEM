
#include "types.hpp"


class RegisterFile{
	public:
		/*
		RegisterFile();
		~RegisterFile();

		GPreg getGPreg(unsigned int index);
		void setGPreg(unsigned int index, GPreg value);
		FPreg getFPreg(unsigned int index);
		void setFPreg(unsigned int index, FPreg value);
		*/

	private:
		GPreg GPregs[32];
		FPreg FPregs[32];
		uint32_t PC;
		int32_t HI;
		int32_t LO;



};