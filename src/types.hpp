#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <stdint.h>
#include <utility>

#define INSTRUCTION_DATA_HASH_TABLE_SIZE	(1009)
#define INSTRUCTION_NUMBER_TABLE_SIZE		(64)
#define INSTRUCTIONSIZE						(32)
#define OPCODESIZE							(6)
#define NUMBER_OF_ARGUMENTS					(4)

#define DONTCAREREPLACEMENT					('0')

#define MEMORY_SECTION_RESERVED				(0x0)
#define MEMORY_SECTION_TEXT					(0x00400000)
#define MEMORY_SECTION_STATIC_DATA			(0x10000000)
#define MEMORY_SECTION_DYNAMIC_DATA			(0x10008000)
#define MEMORY_SECTION_STACK				(0x7ffffffc)

typedef uint32_t instr;



typedef std::pair<int,int> bitrange;

typedef struct {
	float msb, lsb;
} s64__floatPair;

typedef union {
	float _float;
	uint32_t _uint32_t; 
} u32__float_and_uint32_t;

typedef union {
	double _double;
	uint64_t _uint64_t;
} u64__double_and_uint64_t;

typedef union {
	s64__floatPair _floatPair;
    double _double;
} u64__floatPair_and_double;





#endif