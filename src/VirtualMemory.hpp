#ifndef __VIRTUALMEMORY_HPP__
#define __VIRTUALMEMORY_HPP__

#include <stdint.h>

#include "Decoder.hpp"
#include "Instruction.hpp"

using namespace std;

#define NUM_BITS_IN_WORD			(32)
#define NUM_BITS_IN_VIRTUAL_ADDR	(32)

#define NUM_BITS_IN_PAGE_NUM		(NUM_BITS_IN_VIRTUAL_ADDR - NUM_BITS_IN_PAGE_OFFSET)
#define NUM_BITS_IN_PAGE_OFFSET		(12)
#define WORD_ALIGN_OFFSET			(2)

#define MAX_PAGE_OFFSET				( (NUM_BITS_IN_PAGE_OFFSET == 32)? (0xFFFFFFFF) : ((1 << NUM_BITS_IN_PAGE_OFFSET) - 1) )

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
		void init();
		
		void setDecoder(Decoder* decoder);

		h_byte* readVirtualMemorySpaceToHeap(virtualAddr address, size_t size);
		void writeToVirtualMemorySpace(virtualAddr address, size_t size, void* ptr);
		byte* getByteAddr(virtualAddr address);
		
		static virtualAddr wordAlignAddr(virtualAddr address);

		//InstructionCache functions
		Instruction* readInstruction(virtualAddr address);

	private:
		VirtualMemoryPageTable* pageTable;

};

class VirtualMemoryPageTable{
	public:
		VirtualMemoryPageTable();
		VirtualMemoryPageTable(Decoder* decoder);
		~VirtualMemoryPageTable();
		void init();
		
		static uint32_t calculatePageNumber(virtualAddr address);
		VirtualMemoryPage* getPageAddr(virtualAddr address);
		
	private:
		VirtualMemoryPage* pageTable[NUM_PAGES_IN_PAGE_TABLE];

};

class VirtualMemoryPage{
	public:
		VirtualMemoryPage();
		VirtualMemoryPage(uint32_t pageNumber);
		~VirtualMemoryPage();
		void init();

		static uint32_t calculatePageOffset(virtualAddr address);
		byte* getByteAddr(virtualAddr address);
		bool memSpaceIsInBounds(virtualAddr address, size_t size);

		//InstructionCache functions
		static void setDecoder(Decoder* newDecoder);
		bool instructionCacheIsAllocated();
		void allocInstructionCache();
		void deallocInstructionCache();

		bool isValidInstruction(virtualAddr address);
		void invalidateInstruction(virtualAddr address);
		void revalidateInstruction(virtualAddr address);
		Instruction* readInstruction(virtualAddr address);

	private:
		uint32_t pageNumber;
		virtualAddr lowerBound;
		virtualAddr upperBound;

		byte rawMem[NUM_BYTES_IN_PAGE];

		//InstructionCache members
		Instruction** instructionCache;
		static Decoder* decoder;
};







#endif




