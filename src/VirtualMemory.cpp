#include "VirtualMemory.hpp"

//#include "CPU.hpp"

VirtualMemory::VirtualMemory(){

}

VirtualMemory::~VirtualMemory(){

}



void VirtualMemory::writeUpperHWord(uint32_t address, uint16_t hword){


}
void VirtualMemory::writeLowerHWord(uint32_t address, uint16_t hword){


}
void VirtualMemory::writeWord(uint32_t address, uint32_t word){


}
void VirtualMemory::writeDWord(uint32_t address, uint64_t dword){


}


uint16_t VirtualMemory::readUpperHWord(uint32_t address){

	
	return NULL;
}
uint16_t VirtualMemory::readLowerHWord(uint32_t address){

	
	return NULL;
}
uint32_t VirtualMemory::readWord(uint32_t address){

	return NULL;
}
uint64_t VirtualMemory::readDWord(uint32_t address){

	
	return NULL;
}

Instruction* VirtualMemory::readInstruction(uint32_t address){

	
	return NULL;
}

uint32_t VirtualMemory::wordAlignAddr(uint32_t virtualAddr){
	return virtualAddr & 0xFFFFFFFC;
}











VirtualMemoryPageTable::VirtualMemoryPageTable(){
	for(int i=0; i<NUM_PAGES_IN_PAGE_TABLE; i++){
		pageTable[i] = NULL;
	}
}
VirtualMemoryPageTable::~VirtualMemoryPageTable(){
	for(int i=0; i<NUM_PAGES_IN_PAGE_TABLE; i++){
		delete pageTable[i];
	}
}

uint32_t VirtualMemoryPageTable::calculatePageNumber(uint32_t virtualAddr){
	return virtualAddr >> NUM_BITS_IN_PAGE_OFFSET;
}

VirtualMemoryPage* VirtualMemoryPageTable::getPageAddr(uint32_t virtualAddr){
	uint32_t pageNumber = calculatePageNumber(virtualAddr);
	if(pageTable[pageNumber] == NULL){
		pageTable[pageNumber] = new VirtualMemoryPage();	
	}
	return pageTable[pageNumber];
}










VirtualMemoryPage::VirtualMemoryPage(){
	for(int i=0; i<NUM_WORDS_IN_PAGE; i++){instructionTable[i] = NULL;}
	for(int i=0; i<NUM_BYTES_IN_PAGE; i++){rawMem[i] = 0x0;}
}
VirtualMemoryPage::~VirtualMemoryPage(){
	for(int i=0; i<NUM_WORDS_IN_PAGE; i++){delete instructionTable[i];}
}


uint32_t VirtualMemoryPage::calculatePageOffset(uint32_t virtualAddr){
	return virtualAddr & 0x0000FFFF;
}

unsigned char* VirtualMemoryPage::getByteAddr(uint32_t pageOffset){
	return &rawMem[pageOffset];
}
Instruction** VirtualMemoryPage::getInstructionPtrAddr(uint32_t pageOffset){
	//pageOffset >> 2	//word aligns the address for proper index
	return &instructionTable[pageOffset >> 2];
}







