#include "VirtualMemory.hpp"

#include "BitManip.hpp"


VirtualMemory::VirtualMemory(){
	init();
}
VirtualMemory::~VirtualMemory(){
	delete this->pageTable;
}
void VirtualMemory::init(){
	this->pageTable = new VirtualMemoryPageTable();
}

void VirtualMemory::setDecoder(Decoder* decoder){
	VirtualMemoryPage::setDecoder(decoder);
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
byte* VirtualMemory::getByteAddr(virtualAddr address){
	VirtualMemoryPage* pagePtr = pageTable->getPageAddr(address);
	byte* bytePtr = pagePtr->getByteAddr(address);
	return bytePtr;
}
virtualAddr VirtualMemory::wordAlignAddr(virtualAddr address){
	return (address & 0xFFFFFFFC);
}


Instruction* VirtualMemory::readInstruction(virtualAddr address){
	address = wordAlignAddr(address);
	VirtualMemoryPage* wordPage = pageTable->getPageAddr(address);
	return wordPage->readInstruction(address);
}














VirtualMemoryPageTable::VirtualMemoryPageTable(){
	init();
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
		pageTable[pageNumber] = new VirtualMemoryPage(pageNumber);	
	}
	return pageTable[pageNumber];
}








VirtualMemoryPage::VirtualMemoryPage(){
	init();
}
VirtualMemoryPage::VirtualMemoryPage(uint32_t pageNumber){
	init();
	this->pageNumber = pageNumber;

	lowerBound = (pageNumber << NUM_BITS_IN_PAGE_OFFSET);
	upperBound = lowerBound + MAX_PAGE_OFFSET;
}
VirtualMemoryPage::~VirtualMemoryPage(){
	deallocInstructionCache();
}
void VirtualMemoryPage::init(){
	pageNumber = 0;
	lowerBound = 0;
	upperBound = 0;
	for(int i=0; i<NUM_BYTES_IN_PAGE; i++){
		rawMem[i] = 0x0;
	}
	instructionCache = NULL;
}

Decoder* VirtualMemoryPage::decoder = NULL;

uint32_t VirtualMemoryPage::calculatePageOffset(virtualAddr address){
	address <<= (NUM_BITS_IN_VIRTUAL_ADDR - NUM_BITS_IN_PAGE_OFFSET);
	address >>= (NUM_BITS_IN_VIRTUAL_ADDR - NUM_BITS_IN_PAGE_OFFSET);
	return address;
}

byte* VirtualMemoryPage::getByteAddr(virtualAddr address){
	uint32_t pageOffset = calculatePageOffset(address);
	return &rawMem[pageOffset];
}
bool VirtualMemoryPage::memSpaceIsInBounds(virtualAddr address, size_t size){
	return (lowerBound <= address) && ((address + size) <= upperBound);
}


void VirtualMemoryPage::setDecoder(Decoder* newDecoder){
	decoder = newDecoder;
}
bool VirtualMemoryPage::instructionCacheIsAllocated(){
	return instructionCache != NULL;
}
void VirtualMemoryPage::allocInstructionCache(){
	instructionCache = new Instruction*[NUM_WORDS_IN_PAGE];
	for(int i=0; i<NUM_WORDS_IN_PAGE; i++){
		instructionCache[i] = NULL;
	}
}
void VirtualMemoryPage::deallocInstructionCache(){
	if(!instructionCache == NULL){
		for(int i=0; i<NUM_WORDS_IN_PAGE; i++){
			delete instructionCache[i];
		}
	}
	delete[] instructionCache;
	instructionCache = NULL;
}


bool VirtualMemoryPage::isValidInstruction(virtualAddr address){
	if(instructionCache == NULL){
		return false;
	}else{
		uint32_t pageOffset = calculatePageOffset(address);
		Instruction* insPtr = instructionCache[pageOffset >> WORD_ALIGN_OFFSET];
		if(insPtr == NULL){
			return false;
		}

		instr bin = insPtr->getBin();
		byte* byteAddr = getByteAddr(VirtualMemory::wordAlignAddr(address));
		instr readBin = readMemAs<instr>(byteAddr);
		return readBin == bin;
	}
}
void VirtualMemoryPage::invalidateInstruction(virtualAddr address){
	if(instructionCache == NULL){
		return;
	}else{
		uint32_t pageOffset = calculatePageOffset(address);
		delete instructionCache[pageOffset >> WORD_ALIGN_OFFSET];
		instructionCache[pageOffset >> WORD_ALIGN_OFFSET] = NULL;
	}
}
void VirtualMemoryPage::revalidateInstruction(virtualAddr address){
	if(!instructionCacheIsAllocated()){
		allocInstructionCache();
	}
	invalidateInstruction(address);

	virtualAddr virtualWordAddr = VirtualMemory::wordAlignAddr(address);
	uint32_t pageOffset = calculatePageOffset(virtualWordAddr);
	uint32_t encodedInstruction = readMemAs<uint32_t>(&rawMem[pageOffset]);

	Instruction decodedInstruction = decoder->buildInstruction(encodedInstruction);
	Instruction* heapInstructionPtr = new Instruction();
	*heapInstructionPtr = decodedInstruction;

	instructionCache[pageOffset >> 2] = heapInstructionPtr;
}

Instruction* VirtualMemoryPage::readInstruction(virtualAddr address){
	if(!instructionCacheIsAllocated()){
		allocInstructionCache();
	}
	if(!isValidInstruction(address)){
		revalidateInstruction(address);
	}
	virtualAddr virtualWordAddr = VirtualMemory::wordAlignAddr(address);
	uint32_t pageOffset = calculatePageOffset(virtualWordAddr);
	return instructionCache[pageOffset >> 2];
}





