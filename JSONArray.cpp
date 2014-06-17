#include "JSONArray.h"
#include <sstream>



JSONArray::JSONArray() {
	m_name = "";
}

JSONArray::~JSONArray() {}

void JSONArray::setName(string name) {
	m_name = name;
}

void JSONArray::add(JSONBlock block) {
	m_array.push_back(block);

}

string JSONArray::toString() {
	if(m_array.empty()) {
		return "";
	}

	stringstream sstm;
	if(m_name.length() != 0) {
		sstm << "\"" << m_name << "\":";	
	}
	sstm << "[";
	for(unsigned int i = 0; i < m_array.size(); i++) {
		if(i>0){
			sstm << ",";
		}
		sstm << m_array.at(i).toString();
	}
	sstm << "]";

	return sstm.str();
}