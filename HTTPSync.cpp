#include "HTTPSync.h"



size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((std::string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}

HTTPSync::HTTPSync() {
	curl = curl_easy_init();
}

HTTPSync::~HTTPSync() {
	curl_easy_cleanup(curl);
}

void HTTPSync::setShipID(std::string ID) {
	shipID = ID;
}

void HTTPSync::setShipPWD(std::string PWD) {
	shipPWD = PWD;
}

void HTTPSync::setServerURL(std::string URL) {
	serverURL = URL;
}

std::string HTTPSync::getSetup() {
	return serve("/?serv=getSetup&id="+shipID+"&pwd="+shipPWD);
}

std::string HTTPSync::getConfig() {
	return serve("/?serv=getConfig&id="+shipID+"&pwd="+shipPWD);
}

std::string HTTPSync::getRoute() {
	return serve("/?serv=getRoute&id="+shipID+"&pwd="+shipPWD);
}

std::string HTTPSync::pushLogs(std::string logs) {
	//string URL = serverURL + serverCall;
	return serve("/?serv=pushLogs&id="+shipID+"&pwd="+shipPWD+"&data="+logs);
}

std::string HTTPSync::serve(std::string serverCall) {
	std::string response = "";
	std::string url = serverURL + serverCall;
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		//curl_easy_setopt(curl, CURLOPT_POST, 1);
   		//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, serverCall.c_str());
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
	    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		/* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl);
		/* Check for errors */ 
		if(res != CURLE_OK)
			throw ( std::string("HTTPSync::serve(): ") + curl_easy_strerror(res) ).c_str();
	}

	return response;
}
