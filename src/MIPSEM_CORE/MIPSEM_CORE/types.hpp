#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <stdint.h>
#include <utility>

#define NUMBER_OF_OPCODES					(64)
#define NUMBER_OF_INSTRUCTION_PARAMETERS	(4)
#define NUMBER_OF_INSTRUCTIONS				(377)
#define NUMBER_OF_GP_REGISTERS				(32)
#define NUMBER_OF_FP_REGISTERS				(32)

#define SIZE_BYTES_BYTE						(1)
#define SIZE_BYTES_WORD						(4)
#define SIZE_BYTES_HWORD					(SIZE_BYTES_WORD / 2)
#define SIZE_BYTES_FLOAT					(SIZE_BYTES_WORD)
#define SIZE_BYTES_DOUBLE					(2 * SIZE_BYTES_FLOAT)

#define SIZE_BYTES_VIRTUAL_ADDR				(SIZE_BYTES_WORD)
#define SIZE_BYTES_INSTRUCTION_FIELD_IMM	(SIZE_BYTES_HWORD)

#define SIZE_BITS_BYTE						(8 * SIZE_BYTES_BYTE)
#define SIZE_BITS_WORD						(SIZE_BITS_BYTE * SIZE_BYTES_WORD)
#define SIZE_BITS_HWORD						(SIZE_BITS_WORD / 2)
#define SIZE_BITS_FLOAT						(SIZE_BITS_WORD)
#define SIZE_BITS_DOUBLE					(2 * SIZE_BITS_FLOAT)

#define SIZE_BITS_OPCODE					(6)
#define SIZE_BITS_VIRTUAL_ADDR				(SIZE_BITS_BYTE * SIZE_BYTES_VIRTUAL_ADDR)
#define SIZE_BITS_INSTRUCTION_FIELD_IMM		(SIZE_BITS_BYTE * SIZE_BYTES_INSTRUCTION_FIELD_IMM)



typedef uint32_t		instr;
typedef unsigned char	byte;
typedef byte			h_byte;	//denoting pointer to heap
typedef uint32_t		virtualAddr;


typedef std::pair<int,int> bitrange;
typedef std::pair<float, float> pairedSingle;

#endif