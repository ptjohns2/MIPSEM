#ifndef __MEMOBJ_HPP__
#define __MEMOBJ_HPP__

#include "VirtualMemory.hpp"


using namespace std;
	
class segmentHeader{
	public:
		segmentHeader();
		segmentHeader(segmentHeader const &obj);
		~segmentHeader();
		const segmentHeader& operator=(const segmentHeader &rhs);
		void deepCopy(const segmentHeader* obj);
		void init();
		void deinit();

		size_t segFileSize;
		virtualAddr segVirtualMemoryStart;
		h_byte* rawData;

	private:


};

class memobj{
	public:
		memobj();
		memobj(string fileName);
		memobj(memobj const & obj);
		~memobj();
		const memobj& operator=(const memobj &rhs);
		void deepCopy(const memobj* obj);
		void init();
		void deinit();

		void serialize(string fileName);
		void deserialize(string fileName);


		uint32_t numSegments;
		vector<segmentHeader*> segmentHeaders;

	private:

};






#endif