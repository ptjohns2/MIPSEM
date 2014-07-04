#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <stdint.h>
#include <utility>

#define INSTRUCTION_DATA_HASH_TABLE_SIZE	(1009)
#define INSTRUCTION_NUMBER_TABLE_SIZE		(64)
#define INSTRUCTIONSIZE						(32)
#define OPCODESIZE							(6)
#define NUMBER_OF_PARAMETERS					(4)
#define NUMBER_OF_INSTRUCTIONS				(377)

#define DONTCAREREPLACEMENT					('0')

#define MEMORY_SECTION_RESERVED				(0x0)
#define MEMORY_SECTION_TEXT					(0x00400000)
#define MEMORY_SECTION_STATIC_DATA			(0x10000000)
#define MEMORY_SECTION_DYNAMIC_DATA			(0x10008000)
#define MEMORY_SECTION_STACK				(0x7ffffffc)

typedef uint32_t instr;
typedef unsigned char byte;
typedef byte h_byte;	//denoting pointer to heap
typedef uint32_t virtualAddr;


typedef std::pair<int,int> bitrange;



#endif