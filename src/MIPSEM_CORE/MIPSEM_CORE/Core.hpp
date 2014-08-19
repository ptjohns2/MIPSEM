#ifndef __CORE_HPP__
#define __CORE_HPP__

#include "CPU.hpp"
#include "Assembler.hpp"

class Core : public CPU, public Assembler{
	public:
		Core();
		~Core();

};



#endif