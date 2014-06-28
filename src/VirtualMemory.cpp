#include "VirtualMemory.hpp"

//#include "CPU.hpp"


VirtualMemory::VirtualMemory(){
	init();
}
VirtualMemory::VirtualMemory(Decoder* decoder){
	init();
	this->decoder = decoder;
	pageTable = new VirtualMemoryPageTable(this->decoder);
}
VirtualMemory::~VirtualMemory(){
	delete pageTable;
}
void VirtualMemory::init(){

}

h_byte* VirtualMemory::readVirtualMemorySpaceToHeap(virtualAddr address, size_t size){
	h_byte* retVal = new byte[size];
	VirtualMemoryPage* basePagePtr = pageTable->getPageAddr(address);
	if(basePagePtr->memSpaceIsInBounds(address, size)){
		//Standard read, no page fault
		byte* byteAddr = basePagePtr->getByteAddr(address);
		memcpy(retVal, byteAddr, size);
	}else{
		//Page fault, memory spread accross two pages
		virtualAddr baseAddress = address;
		for(int i=0; i<size; i++){
			byte* byteAddr = getByteAddr(baseAddress + i);
			//memcpy(retVal + i, byteAddr, 1);
			*(retVal + i) = *byteAddr;
		}
	}
	return retVal;
}
void VirtualMemory::writeToVirtualMemorySpace(virtualAddr address, size_t size, void* ptr){
	VirtualMemoryPage* basePagePtr = pageTable->getPageAddr(address);
	if(basePagePtr->memSpaceIsInBounds(address, size)){
		//Standard read, no page fault
		byte* byteAddr = basePagePtr->getByteAddr(address);
		memcpy(byteAddr, ptr, size);
	}else{
		//Page fault, memory spread accross two pages
		virtualAddr baseAddress = address;
		for(int i=0; i<size; i++){
			byte* byteAddr = getByteAddr(baseAddress + i);
			//memcpy(byteAddr, ptr + i, 1);
			*byteAddr = *((byte*)ptr + i);
		}
	}
}
void VirtualMemory::writeByte(virtualAddr address, byte val){
	byte* bytePtr = getByteAddr(address);
	*bytePtr = val;
}
byte VirtualMemory::readByte(virtualAddr address){
	byte* bytePtr = getByteAddr(address);
	return *bytePtr;	
}
byte* VirtualMemory::getByteAddr(virtualAddr address){
	VirtualMemoryPage* pagePtr = pageTable->getPageAddr(address);
	byte* bytePtr = pagePtr->getByteAddr(address);
	return bytePtr;
}

Instruction* VirtualMemory::readInstruction(virtualAddr address){
	VirtualMemoryPage* pagePtr = pageTable->getPageAddr(address);
	Instruction* instrPtr = pagePtr->getValidInstructionPtr(address);
	return instrPtr;
}










VirtualMemoryPageTable::VirtualMemoryPageTable(){
	init();
}
VirtualMemoryPageTable::VirtualMemoryPageTable(Decoder* decoder){
	init();
	this->decoder = decoder;
}
VirtualMemoryPageTable::~VirtualMemoryPageTable(){
	for(int i=0; i<NUM_PAGES_IN_PAGE_TABLE; i++){
		delete pageTable[i];
	}
}
void VirtualMemoryPageTable::init(){
	//memset(&pageTable[0], 0, NUM_PAGES_IN_PAGE_TABLE * sizeof(pageTable[0]));
	for(int i=0; i<NUM_PAGES_IN_PAGE_TABLE; i++){
		pageTable[i] = NULL;
	}
}

uint32_t VirtualMemoryPageTable::calculatePageNumber(virtualAddr address){
	return (address >> NUM_BITS_IN_PAGE_OFFSET);
}

VirtualMemoryPage* VirtualMemoryPageTable::getPageAddr(virtualAddr address){
	uint32_t pageNumber = calculatePageNumber(address);
	if(pageTable[pageNumber] == NULL){
		pageTable[pageNumber] = new VirtualMemoryPage(pageNumber, this->decoder);	
	}
	return pageTable[pageNumber];
}









VirtualMemoryPage::VirtualMemoryPage(){
	init();
}
VirtualMemoryPage::VirtualMemoryPage(uint32_t pageNumber, Decoder* decoder){
	init();
	this->decoder = decoder;
	this->pageNumber = pageNumber;

	lowerBound = (pageNumber << NUM_BITS_IN_PAGE_OFFSET);
	upperBound = lowerBound + MAX_PAGE_OFFSET;
}
VirtualMemoryPage::~VirtualMemoryPage(){
	for(int i=0; i<NUM_WORDS_IN_PAGE; i++){delete instructionTable[i];}
}
void VirtualMemoryPage::init(){
	pageNumber = 0;
	lowerBound = 0;
	upperBound = 0;
	for(int i=0; i<NUM_WORDS_IN_PAGE; i++){instructionTable[i] = NULL;}
	for(int i=0; i<NUM_BYTES_IN_PAGE; i++){rawMem[i] = 0x0;}
}

uint32_t VirtualMemoryPage::calculatePageOffset(virtualAddr address){
	address <<= (NUM_BITS_IN_VIRTUAL_ADDR - NUM_BITS_IN_PAGE_OFFSET);
	address >>= (NUM_BITS_IN_VIRTUAL_ADDR - NUM_BITS_IN_PAGE_OFFSET);
	return address;
}

byte* VirtualMemoryPage::getByteAddr(virtualAddr address){
	uint32_t pageOffset = calculatePageOffset(address);
	return &rawMem[pageOffset];
}
Instruction* VirtualMemoryPage::getValidInstructionPtr(virtualAddr address){
	revalidateInstruction(address);
	return getInstructionPtr(address);
}
Instruction* VirtualMemoryPage::getInstructionPtr(virtualAddr address){
	return *getInstructionPtrAddr(address);
}
Instruction** VirtualMemoryPage::getInstructionPtrAddr(virtualAddr address){
	//pageOffset >> 2	//word aligns the address for proper index
	uint32_t pageOffset = calculatePageOffset(address);
	uint32_t wordOffset = pageOffset >> 2;
	return &instructionTable[wordOffset];
}
void VirtualMemoryPage::invalidateInstruction(virtualAddr address){
	Instruction** instrPtrAddr = getInstructionPtrAddr(address);
	*instrPtrAddr = NULL;
}
void VirtualMemoryPage::revalidateInstruction(virtualAddr address){
	Instruction* instrPtr = getInstructionPtr(address);

	if(instrPtr != NULL){return;}

	instr encodedBits = 0;
	byte* byteAddr = getByteAddr(address & 0xFFFFFFFC);
	memcpy(&encodedBits, byteAddr, sizeof(instr));

	Instruction newInstr = decoder->buildInstruction(encodedBits);
	Instruction* newInstrPtr = new Instruction();
	*newInstrPtr = newInstr;

	Instruction** instrPtrAddr = getInstructionPtrAddr(address);
	*instrPtrAddr = newInstrPtr;
}

bool VirtualMemoryPage::memSpaceIsInBounds(virtualAddr address, size_t size){
	return (lowerBound <= address) && ((address + size) <= upperBound);
}






