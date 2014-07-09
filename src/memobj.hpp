#ifndef __MEMOBJ_HPP__
#define __MEMOBJ_HPP__

#include "VirtualMemory.hpp"


using namespace std;
	
class segmentHeader{
	public:
		segmentHeader();
		~segmentHeader();
		void init();

		uint32_t segFileSize;
		virtualAddr segVirtualMemoryStart;
		h_byte* rawData;

	private:


};

class memobj{
	public:
		memobj();
		memobj(string fileName);
		~memobj();
		void init();

		void serialize(string fileName);


		uint32_t numSegments;
		vector<segmentHeader*> segmentHeaders;

	private:

};






#endif