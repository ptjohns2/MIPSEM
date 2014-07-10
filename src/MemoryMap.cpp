#include "MemoryMap.hpp"

#include <cassert>
#include <fstream>

MemorySegment::MemorySegment(){
	init();
}
MemorySegment::MemorySegment(size_t segFileSize, virtualAddr segVirtualMemoryStart, h_byte* rawData){
	this->segFileSize = segFileSize;
	this->segVirtualMemoryStart = segVirtualMemoryStart;
	this->rawData = rawData;
}
MemorySegment::MemorySegment(MemorySegment const &obj){
	init();
	deepCopy(&obj);
}
MemorySegment::~MemorySegment(){
	deinit();
}
const MemorySegment& MemorySegment::operator=(const MemorySegment &rhs){
	if(this != &rhs){
		deinit();
		deepCopy(&rhs);
	}
	return *this;
}
void MemorySegment::deepCopy(const MemorySegment* obj){
	this->segFileSize = obj->segFileSize;
	this->segVirtualMemoryStart = obj->segVirtualMemoryStart;
	this->rawData = new h_byte[this->segFileSize];
	memcpy(this->rawData, obj->rawData, this->segFileSize);
}
void MemorySegment::init(){
	segFileSize = 0x0;
	segVirtualMemoryStart = 0x0;
	rawData = NULL;
}
void MemorySegment::deinit(){
	delete rawData;
}

size_t MemorySegment::getSegFileSize()const{return segFileSize;}
virtualAddr MemorySegment::getSegVirtualMemoryStart()const{return segVirtualMemoryStart;}
h_byte* MemorySegment::getRawData()const{return rawData;}
void MemorySegment::setRawData(h_byte* rawData){this->rawData = rawData;}



//	http://courses.cs.vt.edu/cs2604/fall02/binio.html#write

MemoryMap::MemoryMap(){
	init();
}
MemoryMap::MemoryMap(string fileName){
	init();
	deserialize(fileName);
}
MemoryMap::MemoryMap(MemoryMap const &obj){
	init();
	this->numSegments = obj.numSegments;
	for(int i=0; i<obj.memorySegments.size(); i++){
		MemorySegment* tmpMemorySegment = new MemorySegment(*obj.memorySegments[i]);
		this->memorySegments.push_back(tmpMemorySegment);
	}
}
MemoryMap::~MemoryMap(){
	deinit();
}
void MemoryMap::deepCopy(const MemoryMap* obj){
	this->numSegments = obj->numSegments;
	for(int i=0; i<obj->memorySegments.size(); i++){
		MemorySegment* tmpMemorySegment = new MemorySegment(*obj->memorySegments[i]);
		this->memorySegments.push_back(tmpMemorySegment);
	}
}
const MemoryMap& MemoryMap::operator=(const MemoryMap &rhs){
	if(this != &rhs){
		deinit();
		deepCopy(&rhs);
	}
	return *this;
}
void MemoryMap::init(){
	numSegments = 0x0;
	memorySegments.clear();
}
void MemoryMap::deinit(){
	for(int i=0; i<memorySegments.size(); i++){
		delete memorySegments[i];
	}
}


void MemoryMap::serialize(string fileName){
	//data_offset 4 [| segnfstart 4 | segnfsize 4 | segnmemstart 4 |] raw_data x
	assert(numSegments == memorySegments.size());

	ofstream file = ofstream(fileName, ios::out | ios::binary);
	if(!file.is_open()){return;}

	//write data_offset 4
	file.write((const char*)&numSegments, sizeof(numSegments));

	//write segment headers [4|4|4]
	for(int i=0; i<numSegments; i++){
		size_t segFileSize = memorySegments[i]->getSegFileSize();
		virtualAddr segVirtualMemoryStart = memorySegments[i]->getSegVirtualMemoryStart();
		file.write((char*)&segVirtualMemoryStart, sizeof(segFileSize));
		file.write((char*)&segFileSize, sizeof(segVirtualMemoryStart));
	}

	//write raw data x
	for(int i=0; i<numSegments; i++){
		char* rawDataPtr = (char*)memorySegments[i]->getRawData();
		file.write(rawDataPtr, memorySegments[i]->getSegFileSize());
	}

	file.close();
}

void MemoryMap::deserialize(string fileName){
	deinit();

	//data_offset 4 [| segnfstart 4 | segnfsize 4 | segnmemstart 4 |] raw_data x
	ifstream file = ifstream(fileName, ios::in | ios::binary);
	if(!file.is_open()){return;}
	
	//read data_offset 4
	file.read((char*)&numSegments, sizeof(numSegments));
	
	//read header info except h_byte* rawData (next loop)
	for(int i=0; i<numSegments; i++){
		size_t segFileSize;
		virtualAddr segVirtualMemoryStart;
		file.read((char*)&segVirtualMemoryStart, sizeof(segVirtualMemoryStart));
		file.read((char*)&segFileSize, sizeof(segFileSize));
		MemorySegment* tmpMemorySegment = new MemorySegment(segFileSize, segVirtualMemoryStart, NULL);

		memorySegments.push_back(tmpMemorySegment);
	}
	//read raw data for each header
	for(int i=0; i<numSegments; i++){
		size_t segmentSize = memorySegments[i]->getSegFileSize();
		char* charArray = new char[segmentSize];
		file.read(charArray, segmentSize);
		memorySegments[i]->setRawData((h_byte*)charArray);
	}
	file.close();
}

void MemoryMap::addMemorySegment(MemorySegment memSeg){
	MemorySegment* newMemSegPtr = new MemorySegment(memSeg);
	numSegments++;
	memorySegments.push_back(newMemSegPtr);
}