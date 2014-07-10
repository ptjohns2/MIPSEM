#ifndef __MemoryMap_HPP__
#define __MemoryMap_HPP__

#include "VirtualMemory.hpp"


using namespace std;
	
class MemorySegment{
	public:
		MemorySegment();
		MemorySegment(size_t, virtualAddr, h_byte*);
		MemorySegment(MemorySegment const &obj);
		~MemorySegment();
		const MemorySegment& operator=(const MemorySegment &rhs);
		void deepCopy(const MemorySegment* obj);
		void init();
		void deinit();

		size_t getSegFileSize() const;
		virtualAddr getSegVirtualMemoryStart() const;
		h_byte* getRawData() const;
		void setRawData(h_byte*);

	private:
		size_t segFileSize;
		virtualAddr segVirtualMemoryStart;
		h_byte* rawData;

};

class MemoryMap{
	public:
		MemoryMap();
		MemoryMap(string fileName);
		MemoryMap(MemoryMap const & obj);
		~MemoryMap();
		const MemoryMap& operator=(const MemoryMap &rhs);
		void deepCopy(const MemoryMap* obj);
		void init();
		void deinit();

		void serialize(string fileName);
		void deserialize(string fileName);

		void addMemorySegment(MemorySegment memSeg);

	private:
		uint32_t numSegments;
		vector<MemorySegment*> memorySegments;

};






#endif