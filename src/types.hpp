#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <stdint.h>
#include <utility>

#define INSTRUCTION_DATA_HASH_TABLE_SIZE	(1009)
#define INSTRUCTION_NUMBER_TABLE_SIZE		(64)
#define INSTRUCTIONSIZE						(32)
#define OPCODESIZE							(6)

#define DONTCAREREPLACEMENT					('0')

typedef uint32_t instr;

typedef int32_t field;

typedef uint32_t ufield;
typedef int32_t GPreg;
typedef float FPreg;



typedef std::pair<int,int> bitRange;










#endif