#ifndef __JSONARRAY_H__
#define __JSONARRAY_H__

#include "IEncoder.h"
#include "JSONBlock.h"
#include <vector>

using namespace std;

class JSONArray : public IEncoder {

	public:
		JSONArray();
		~JSONArray();

		void setName(string name);
		void add(JSONBlock block);
		string toString();

	private:
		string m_name;
		vector<JSONBlock> m_array;
};

#endif