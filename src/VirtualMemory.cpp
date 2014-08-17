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
void VirtualMemory::deinit(){
	delete this->pageTable;
	this->pageTable = NULL;
}
void VirtualMemory::reset(){
	delete this->pageTable;
	this->pageTable = new VirtualMemoryPageTable();
}


void VirtualMemory::serialize(string fileName){
	exportMemoryMap().serialize(fileName);
}
void VirtualMemory::deserialize(string fileName){
	MemoryMap map;
	map.deserialize(fileName);
	importMemoryMap(&map);
}

void VirtualMemory::importMemoryMap(MemoryMap* memoryMap){
	uint32_t numSegments = memoryMap->getNumSegments();
	vector<MemorySegment*> memorySegments = memoryMap->getMemorySegments();
	assert(numSegments == memorySegments.size());

	for(int i=0; i<numSegments; i++){
		size_t segFileSize = memorySegments[i]->getSegFileSize();
		virtualAddr segVirtualMemoryStart = memorySegments[i]->getSegVirtualMemoryStart();
		h_byte* rawData = memorySegments[i]->getRawData();
		writeToVirtualMemorySpace(segVirtualMemoryStart, segFileSize, rawData);
	}
}
MemoryMap VirtualMemory::exportMemoryMap() const{
	MemoryMap memoryMap = MemoryMap();
	for(int i=0; i<NUM_PAGES_IN_PAGE_TABLE; i++){
		if(pageTable->pageIsAllocated(i)){
			MemorySegment memorySegment = pageTable->pageTable[i]->readMemorySegment();
			memoryMap.addMemorySegment(&memorySegment);
		}
	}
	return memoryMap;
}

void VirtualMemory::writeToVirtualMemorySpace(virtualAddr address, size_t size, void* ptr){
	invalidateInstructionCacheOfVirtualMemorySpace(address, size);

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
void VirtualMemory::invalidateInstructionCacheOfVirtualMemorySpace(virtualAddr address, size_t size){
	for(virtualAddr wordAddr = address; wordAddr < address + size; wordAddr+=4){
		VirtualMemoryPage* basePagePtr = pageTable->getPageAddr(wordAddr);
		basePagePtr->invalidateInstruction(wordAddr);
	}
}
h_byte* VirtualMemory::readVirtualMemorySpaceToHeap(virtualAddr address, size_t size) const{
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
byte* VirtualMemory::getByteAddr(virtualAddr address) const{
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
		pageTable[i] = NULL;
	}
}
void VirtualMemoryPageTable::init(){
	//memset(&pageTable[0], 0, NUM_PAGES_IN_PAGE_TABLE * sizeof(pageTable[0]));
	for(int i=0; i<NUM_PAGES_IN_PAGE_TABLE; i++){
		pageTable[i] = NULL;
	}
	pageDataStart = getPageAddr(MEMSEG_BASE_DATA);
	pageTextStart = getPageAddr(MEMSEG_BASE_TEXT);
}

uint32_t VirtualMemoryPageTable::calculatePageNumber(virtualAddr address){
	return (address >> SIZE_BITS_PAGE_OFFSET);
}

VirtualMemoryPage* VirtualMemoryPageTable::getPageAddr(virtualAddr address){
	uint32_t pageNumber = calculatePageNumber(address);
	if(pageTable[pageNumber] == NULL){
		pageTable[pageNumber] = new VirtualMemoryPage(pageNumber);	
	}
	return pageTable[pageNumber];
}
bool VirtualMemoryPageTable::pageIsAllocated(uint32_t pageNumber){
	return pageTable[pageNumber] != NULL;
}







VirtualMemoryPage::VirtualMemoryPage(){
	init();
}
VirtualMemoryPage::VirtualMemoryPage(uint32_t pageNumber){
	init();
	this->pageNumber = pageNumber;

	lowerBound = (pageNumber << SIZE_BITS_PAGE_OFFSET);
	upperBound = lowerBound + MAX_PAGE_OFFSET;
}
Decoder VirtualMemoryPage::decoder;
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
void VirtualMemoryPage::deinit(){
	deallocInstructionCache();
}


MemorySegment VirtualMemoryPage::readMemorySegment(){
	virtualAddr segVirtualMemoryStart = lowerBound;
	size_t segFileSize = upperBound - lowerBound + 1;
	char* rawData = new char[segFileSize];
	memcpy(rawData, &rawMem[0], segFileSize);
	return MemorySegment(segFileSize, segVirtualMemoryStart, (h_byte*)rawData);
}
uint32_t VirtualMemoryPage::calculatePageOffset(virtualAddr address){
	address <<= (SIZE_BITS_VIRTUAL_ADDR - SIZE_BITS_PAGE_OFFSET);
	address >>= (SIZE_BITS_VIRTUAL_ADDR - SIZE_BITS_PAGE_OFFSET);
	return address;
}

byte* VirtualMemoryPage::getByteAddr(virtualAddr address){
	uint32_t pageOffset = calculatePageOffset(address);
	return &rawMem[pageOffset];
}
bool VirtualMemoryPage::memSpaceIsInBounds(virtualAddr address, size_t size){
	return (lowerBound <= address) && ((address + size) <= upperBound);
}


bool VirtualMemoryPage::instructionCacheIsAllocated(){
	return instructionCache != NULL;
}
void VirtualMemoryPage::allocInstructionCache(){
	if(!instructionCacheIsAllocated()){
		instructionCache = new pair<bool, Instruction>[NUM_WORDS_IN_PAGE];
		for(int i=0; i<NUM_WORDS_IN_PAGE; i++){
			instructionCache[i].first = false;
		}
	}
}
void VirtualMemoryPage::deallocInstructionCache(){
	delete[] instructionCache;
	instructionCache = NULL;
}


bool VirtualMemoryPage::isValidInstruction(virtualAddr address){
	if(instructionCache == NULL){
		return false;
	}else{
		uint32_t pageOffset = calculatePageOffset(address);
		pair<bool, Instruction>* insPtr = &instructionCache[pageOffset >> WORD_ALIGN_OFFSET];
		return insPtr->first;
	}
}
void VirtualMemoryPage::invalidateInstruction(virtualAddr address){
	if(instructionCache == NULL){
		return;
	}else{
		uint32_t pageOffset = calculatePageOffset(address);
		pair<bool, Instruction>* insPtr = &instructionCache[pageOffset >> WORD_ALIGN_OFFSET];
		insPtr->first = false;
	}
}
void VirtualMemoryPage::revalidateInstruction(virtualAddr address){
	if(!instructionCacheIsAllocated()){
		allocInstructionCache();
	}
	virtualAddr virtualWordAddr = VirtualMemory::wordAlignAddr(address);
	uint32_t pageOffset = calculatePageOffset(virtualWordAddr);
	uint32_t readWord = readMemAs<uint32_t>(&rawMem[pageOffset]);
	
	instructionCache[pageOffset >> 2] = make_pair<bool, Instruction>(true, decoder.buildInstruction(readWord));
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
	return &instructionCache[pageOffset >> 2].second;
}





