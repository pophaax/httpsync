#ifndef __IENCODER_H__
#define __IENCODER_H__

#include <string>

using namespace std;

class IEncoder {
	
	public:
		~IEncoder() {}
		virtual string toString() = 0;
};

#endif