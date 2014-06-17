#ifndef __JSONBLOCK_H__
#define __JSONBLOCK_H__

#include "IEncoder.h"
#include <vector>

using namespace std;

class JSONBlock : public IEncoder {

	public:
		JSONBlock();
		~JSONBlock();

		void setName(string name);
		void add(IEncoder *component);
		string toString();

	private:
		string m_name;
		vector<IEncoder*> m_block;
};

#endif