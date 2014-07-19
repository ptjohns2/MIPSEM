#ifndef __VIRTUALMEMORY_HPP__
#define __VIRTUALMEMORY_HPP__

#include <stdint.h>

#include "Decoder.hpp"
#include "Instruction.hpp"
#include "MemoryMap.hpp"

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

#define POWER_OF_TWO(power)			((power == 0)? 0 : (1 << power))

#define NUMBER_OF_MEMORY_SEGMENTS	(4)
#define MEMSEG_LIMIT_KSPACE			(0xFFFFFFFF)
#define MEMSEG_LIMIT_KDATA			(0xFFFEFFFF)
#define MEMSEG_BASE_KDATA			(0x90000000)
#define MEMSEG_LIMIT_KTEXT			(0x8FFFFFFC)	
#define MEMSEG_BASE_KTEXT			(0x80000000)
#define MEMSEG_BASE_KSPACE			(0x80000000)
#define MEMSEG_LIMIT_USPACE			(0x7FFFFFFF)
#define MEMSEG_LIMIT_DATA			(0x7FFFFFFF)
#define MEMSEG_BASE_STACK			(0x7FFFFFFF)
#define MEMSEG_LIMIT_STACK			(0x10040000)
#define MEMSEG_BASE_HEAP			(0x10040000)
#define MEMSEG_BASE_DATA			(0x10010000)
#define MEMSEG_BASE_EXTERN			(0x10000000)
#define MEMSEG_LIMIT_TEXT			(0x0FFFFFFC)
#define MEMSEG_BASE_TEXT			(0x00400000)
#define MEMSEG_BASE_RESERVED		(0x00000000)

#define MEMPTR_SP					(MEMSEG_BASE_STACK)
#define MEMPTR_GP					(0x10080000)
#define MEMPTR_PC					(MEMSEG_BASE_TEXT)


class VirtualMemory;
class VirtualMemoryPageTable;
class VirtualMemoryPage;

class VirtualMemory{
	public:
		VirtualMemory();
		~VirtualMemory();
		void init();
		void deinit();
		void reset();
		
		void setDecoder(Decoder* decoder);

		void serialize(string fileName);
		void writeMemoryMap(MemoryMap* memoryMap);
		MemoryMap readMemoryMap() const;


		void writeToVirtualMemorySpace(virtualAddr address, size_t size, void* ptr);
		h_byte* readVirtualMemorySpaceToHeap(virtualAddr address, size_t size) const;
		byte* getByteAddr(virtualAddr address) const;
		
		static virtualAddr wordAlignAddr(virtualAddr address);

		//InstructionCache functions
		Instruction* readInstruction(virtualAddr address);

		//Template functions
		
		template<typename datatype> 
		datatype readPOD(virtualAddr addr){
			h_byte* bytePtr = readVirtualMemorySpaceToHeap(addr, sizeof(datatype));
			datatype val = readMemAs<datatype>(bytePtr);
			delete bytePtr;
			return val;
		}

		template<typename datatype>
		void writePOD(virtualAddr addr, datatype val){
			writeToVirtualMemorySpace(addr, sizeof(val), &val);
		}



	private:
		VirtualMemoryPageTable* pageTable;

};

class VirtualMemoryPageTable{
	friend class VirtualMemory;
	public:
		VirtualMemoryPageTable();
		VirtualMemoryPageTable(Decoder* decoder);
		~VirtualMemoryPageTable();
		void init();
		
		static uint32_t calculatePageNumber(virtualAddr address);
		VirtualMemoryPage* getPageAddr(virtualAddr address);
		bool pageIsAllocated(uint32_t pageNumber);
		
	private:
		VirtualMemoryPage* pageDataStart;
		VirtualMemoryPage* pageTextStart;
		VirtualMemoryPage* pageTable[NUM_PAGES_IN_PAGE_TABLE];

};

class VirtualMemoryPage{
	public:
		VirtualMemoryPage();
		VirtualMemoryPage(uint32_t pageNumber);
		~VirtualMemoryPage();
		void init();
		void deinit();

		MemorySegment readMemorySegment();
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




