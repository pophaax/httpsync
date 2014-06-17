#ifndef __JSONDATA_H__
#define __JSONDATA_H__

#include "IEncoder.h"
#include <vector>

using namespace std;

class JSONData : public IEncoder {

	public:
		JSONData();
		~JSONData();

		void add(string name, string value);
		void add(string name, int value);
		void add(string name, float value);
		void add(string name, double value);
		string toString();

	private:
		vector<string> m_data;
};

#endif