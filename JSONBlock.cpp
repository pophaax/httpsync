#include "JSONBlock.h"
#include <sstream>



JSONBlock::JSONBlock() {
	m_name = "";
}

JSONBlock::~JSONBlock() {}

void JSONBlock::setName(string name) {
	m_name = name;
}

void JSONBlock::add(IEncoder *component) {
	m_block.push_back(component);
}

string JSONBlock::toString() {
	if(m_block.empty()) {
		return "";
	}

	stringstream sstm;
	sstm << "{";
	if(m_name.length() != 0) {
		sstm << "\"" << m_name << "\":";	
	}
	for(unsigned int i = 0; i < m_block.size(); i++) {
		if(i>0){
			sstm << ",";
		}
		sstm << m_block.at(i)->toString();
	}
	sstm << "}";

	return sstm.str();
}