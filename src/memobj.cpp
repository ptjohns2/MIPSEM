#include "memobj.hpp"

#include <cassert>
#include <fstream>

segmentHeader::segmentHeader(){
	init();
}
segmentHeader::segmentHeader(segmentHeader const &obj){
	init();
	deepCopy(&obj);
}
segmentHeader::~segmentHeader(){
	deinit();
}
const segmentHeader& segmentHeader::operator=(const segmentHeader &rhs){
	if(this != &rhs){
		deinit();
		deepCopy(&rhs);
	}
	return *this;
}
void segmentHeader::deepCopy(const segmentHeader* obj){
	this->segFileSize = obj->segFileSize;
	this->segVirtualMemoryStart = obj->segVirtualMemoryStart;
	this->rawData = new h_byte[this->segFileSize];
	memcpy(this->rawData, obj->rawData, this->segFileSize);
}
void segmentHeader::init(){
	segFileSize = 0x0;
	segVirtualMemoryStart = 0x0;
	rawData = NULL;
}
void segmentHeader::deinit(){
	delete rawData;
}



//	http://courses.cs.vt.edu/cs2604/fall02/binio.html#write

memobj::memobj(){
	init();
}
memobj::memobj(string fileName){
	init();
	deserialize(fileName);
}
memobj::memobj(memobj const &obj){
	init();
	this->numSegments = obj.numSegments;
	for(int i=0; i<obj.segmentHeaders.size(); i++){
		segmentHeader* tmpSegmentHeader = new segmentHeader(*obj.segmentHeaders[i]);
		this->segmentHeaders.push_back(tmpSegmentHeader);
	}
}
memobj::~memobj(){
	deinit();
}
void memobj::deepCopy(const memobj* obj){
	this->numSegments = obj->numSegments;
	for(int i=0; i<obj->segmentHeaders.size(); i++){
		segmentHeader* tmpSegmentHeader = new segmentHeader(*obj->segmentHeaders[i]);
		this->segmentHeaders.push_back(tmpSegmentHeader);
	}
}
const memobj& memobj::operator=(const memobj &rhs){
	if(this != &rhs){
		deinit();
		deepCopy(&rhs);
	}
	return *this;
}
void memobj::init(){
	numSegments = 0x0;
	segmentHeaders.clear();
}
void memobj::deinit(){
	for(int i=0; i<segmentHeaders.size(); i++){
		delete segmentHeaders[i];
	}
}


void memobj::serialize(string fileName){
	//data_offset 4 [| segnfstart 4 | segnfsize 4 | segnmemstart 4 |] raw_data x
	assert(numSegments == segmentHeaders.size());

	ofstream file = ofstream(fileName, ios::out | ios::binary);
	if(!file.is_open()){return;}

	//write data_offset 4
	file.write((const char*)&numSegments, sizeof(numSegments));

	//write segment headers [4|4|4]
	for(int i=0; i<numSegments; i++){
		char* segFileSizePtr = (char*)&segmentHeaders[i]->segFileSize;
		char* segVirtualMemoryStartPtr = (char*)&segmentHeaders[i]->segVirtualMemoryStart;

		file.write(segFileSizePtr, sizeof(segmentHeaders[i]->segFileSize));
		file.write(segVirtualMemoryStartPtr, sizeof(segmentHeaders[i]->segVirtualMemoryStart));
	}

	//write raw data x
	for(int i=0; i<numSegments; i++){
		char* rawDataPtr = (char*)segmentHeaders[i]->rawData;
		file.write(rawDataPtr, segmentHeaders[i]->segFileSize);
	}

	file.close();
}

void memobj::deserialize(string fileName){
	deinit();

	//data_offset 4 [| segnfstart 4 | segnfsize 4 | segnmemstart 4 |] raw_data x
	ifstream file = ifstream(fileName, ios::in | ios::binary);
	if(!file.is_open()){return;}
	
	//read data_offset 4
	file.read((char*)&numSegments, sizeof(numSegments));

	//read header info except h_byte* rawData (next loop)
	for(int i=0; i<numSegments; i++){
		segmentHeader* tmpSegmentHeader = new segmentHeader();
		file.read((char*)&tmpSegmentHeader->segFileSize, sizeof(tmpSegmentHeader->segFileSize));
		file.read((char*)&tmpSegmentHeader->segVirtualMemoryStart, sizeof(tmpSegmentHeader->segVirtualMemoryStart));
		segmentHeaders.push_back(tmpSegmentHeader);
	}
	//read raw data for each header
	for(int i=0; i<numSegments; i++){
		size_t segmentSize = segmentHeaders[i]->segFileSize;
		char* charArray = new char[segmentSize];
		file.read(charArray, segmentSize);
		segmentHeaders[i]->rawData = (h_byte*)charArray;
	}
	file.close();
}