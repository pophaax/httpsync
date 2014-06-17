#include "HTTPConnection.h"



size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}

HTTPConnection::HTTPConnection() {
	curl = curl_easy_init();
}

HTTPConnection::~HTTPConnection() {
	curl_easy_cleanup(curl);
}

void HTTPConnection::setShipID(string ID) {
	shipID = ID;
}

void HTTPConnection::setShipPWD(string PWD) {
	shipPWD = PWD;
}

void HTTPConnection::setServerURL(string URL) {
	serverURL = URL;
}

string HTTPConnection::checkUpdates() {
	return serve("/?serv=checkUpdates&id="+shipID);
}

string HTTPConnection::getConfig() {
	return serve("/?serv=getConfig&id="+shipID);
}

string HTTPConnection::getRoute() {
	return serve("/?serv=getRoute&id="+shipID);
}

string HTTPConnection::pushLogs(string logs) {
	return serve("/?serv=pushLogs&id="+shipID+"&pwd="+shipPWD+"&data="+logs);
}

string HTTPConnection::serve(string serverCall) {
	string response = "";
	string URL = serverURL + serverCall;
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
	    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		/* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl);
		/* Check for errors */ 
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
	}

	return response;
}
