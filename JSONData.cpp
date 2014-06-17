#include "JSONData.h"
#include <sstream>



JSONData::JSONData() {}
JSONData::~JSONData() {}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void JSONData::add(string name, string value) {;
	stringstream sstm;
	sstm << "\"" << name << "\":" << "\"" << value << "\"";
	string result = sstm.str();
	while(replace(result, " ", "%26"));
	m_data.push_back(result);
}

void JSONData::add(string name, int value) {
	stringstream sstm;
	sstm << "\"" << name << "\":" << value;
	m_data.push_back(sstm.str());
}

void JSONData::add(string name, float value) {
	stringstream sstm;
	sstm << "\"" << name << "\":" << value;
	m_data.push_back(sstm.str());
}

void JSONData::add(string name, double value) {
	stringstream sstm;
	sstm << "\"" << name << "\":" << value;
	m_data.push_back(sstm.str());
}

string JSONData::toString() {
	if(m_data.empty()) {
		return "";
	}

	stringstream sstm;
	for(unsigned int i = 0; i < m_data.size(); i++) {
		if(i>0){
			sstm << ",";
		}
		sstm << m_data.at(i);
	}

	return sstm.str();
}