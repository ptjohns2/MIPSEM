#ifndef __VIRTUALMEMORY_HPP__
#define __VIRTUALMEMORY_HPP__

#include <stdint.h>

#include "Decoder.hpp"
#include "Instruction.hpp"

using namespace std;

#define NUM_BITS_IN_WORD			(32)
#define NUM_BITS_IN_VIRTUAL_ADDR	(32)

#define NUM_BITS_IN_PAGE_NUM		(20)
#define NUM_BITS_IN_PAGE_OFFSET		(12)
#define WORD_ALIGN_OFFSET			(2)

#define NUM_PAGES_IN_PAGE_TABLE		(POWER_OF_TWO(NUM_BITS_IN_PAGE_NUM))

#define NUM_BYTES_IN_PAGE			(POWER_OF_TWO(NUM_BITS_IN_PAGE_OFFSET))
#define NUM_WORDS_IN_PAGE			(POWER_OF_TWO((NUM_BITS_IN_PAGE_OFFSET - WORD_ALIGN_OFFSET)))


#define POWER_OF_TWO(power)			(1 << power)

class VirtualMemory;
class VirtualMemoryPageTable;
class VirtualMemoryPage;

class VirtualMemory{
	public:
		VirtualMemory();
		~VirtualMemory();

		
		void writeUpperHWord(uint32_t address, uint16_t hword);
		void writeLowerHWord(uint32_t address, uint16_t hword);
		void writeWord(uint32_t address, uint32_t word);
		void writeDWord(uint32_t address, uint64_t dword);
		
		uint16_t readUpperHWord(uint32_t address);
		uint16_t readLowerHWord(uint32_t address);
		uint32_t readWord(uint32_t address);
		uint64_t readDWord(uint32_t address);

		Instruction* readInstruction(uint32_t address);
		static uint32_t wordAlignAddr(uint32_t virtualAddr);

	private:
		//VirtualMemoryPageTable pageTable;
		Decoder* decoder;

};

class VirtualMemoryPageTable{
	public:
		VirtualMemoryPageTable();
		~VirtualMemoryPageTable();
		
		static uint32_t calculatePageNumber(uint32_t virtualAddr);
		VirtualMemoryPage* getPageAddr(uint32_t virtualAddr);
		
	private:
		VirtualMemoryPage* pageTable[NUM_PAGES_IN_PAGE_TABLE];
};

class VirtualMemoryPage{
	public:
		VirtualMemoryPage();
		~VirtualMemoryPage();

		static uint32_t calculatePageOffset(uint32_t virtualAddr);
		
		unsigned char* getByteAddr(uint32_t pageOffset);
		Instruction** getInstructionPtrAddr(uint32_t pageOffset);

	private:
		unsigned char rawMem[NUM_BYTES_IN_PAGE];
		Instruction* instructionTable[NUM_WORDS_IN_PAGE];	//PC always word aligned
};







#endif




