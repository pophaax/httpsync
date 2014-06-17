#ifndef __JSON_H__
#define __JSON_H__

#include <string>
#include <vector>


using namespace std;

/******************************************
 *
 *	IEncoder interface
 *
 ******************************************/

class IEncoder {
	
	public:
		~IEncoder() {}
		virtual string toString() = 0;
};

/******************************************
 *
 *	JSONBLOCK
 *
 ******************************************/

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

/******************************************
 *
 *	JSONARRAY
 *
 ******************************************/

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

/******************************************
 *
 *	JSONDATA
 *
 ******************************************/

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